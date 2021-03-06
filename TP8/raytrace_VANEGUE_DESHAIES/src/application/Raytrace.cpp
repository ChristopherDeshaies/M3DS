#include "Material.h"
#include "CsgTree.h"
#include "Primitive.h"
#include "Raytrace.h"
#include <cmath>
#include "Line.h"
#include <iostream>
#include "Ray.h"
#include "GLTool.h"
#include <ctime>
#include <cmath>


/**
@file
@author Fabrice Aubert
*/


using namespace p3d;
using namespace std;


/**
Calcul de la couleur pour un rayon donné : la fonction sera récursive lors de l'ajout des rayons réfléchis
 - level détermine la profondeur de récursivité (pour limiter la profondeur de récursivité);
 - contribution donne le pourcentage (contrib \in [0,1]) de la contribution à l'éclairage total (cumul par appels récursif) : si la contribution devient trop faible, on arrête la récursivité
*/
Vector3 Raytrace::computeRayColor(const Ray &ray, int level, double contribution) {

  /**
  * Remarques :
  - inter->material().reflexionCoefficient() donnera le coefficient de contribution à la réflexion (i.e. 1=réflexion totale, 0=réflexion nulle)
  - inter->computeReflectRay() : permet de calculer le rayon réfléchi
  */


  Vector3 color=Vector3(0,0,0);

  if (level>0 && contribution>0.001) {

    // Intersection de la scène avec le rayon (donne uniquement l'intersection la "plus proche").
    Intersection *inter=_scene->intersection(ray,0.1); // 0.1 pour prendre une intersection qui se trouve un peu devant le "point de départ" (origine) du rayon

    if (inter!=NULL) { // existe-t-il une intersection avec la scène ?
      color=computeLocalColor(*inter); // calcul de la couleur par Phong

      // on récupère le coefficient
      double coeffReflexion = inter->material().reflectionCoefficient();
      double coeffRefract = inter->material().refractionCoefficient();

      if (coeffReflexion > 0.0 && level > 0 && contribution > 0.001) {

          Ray reflectedRay = inter->computeReflectRay();
          Ray refractRay = inter->computeRefractRay();

          Vector3 reflectedRayColor = computeRayColor(reflectedRay,level,contribution*coeffReflexion);
          Vector3 refractRayColor = computeRayColor(refractRay,level,contribution*coeffReflexion);

          color = (1.0-coeffReflexion)*color + coeffReflexion*reflectedRayColor;
          color = (1.0-coeffRefract)*color + coeffRefract*refractRayColor;

      }



      // libération mémoire de inter
      delete inter;
    }

  }


  return color;
}


/**
  Calcul de l'éclairement local d'un point d'intersection => Phong avec ombres portées.
  - toutes les données nécessaires au point d'intersection sont dans le paramêtre intersection (point, normale, noeud CSG intersecté)
  - les données de la scène (sources lumineuses) sont accessibles par scene()->...
*/
Vector3 Raytrace::computeLocalColor(const Intersection &intersection) {
  /**
  * P est le point d'intersection (Vector3)
  * L est le vecteur d'éclairement (Vector3)
  * N est la normale au point d'intersection (Vector3)
  * V est le vecteur d'observation
  * m contient le materiel au point : m.diffuse() donne le matériel diffus (de type Vector3 : on peut utiliser les opérateurs *, +, etc), de même m.specular(), m.shininess()
  * intersection.incident() donne le rayon qui a provoqué l'intersection
  * Pour les sources :
  *   - _scene->nbLight() donne le nombre de source lumineuses
  *   - _scene->lightPosition(i) donne la position de la source i (uniquement des sources ponctuelles).
  * Remarque : il faut faire la somme des couleurs obtenues pour chacune des sources (risque de saturation si plusieurs sources lumineuses).
  */

  Vector3 P;
  Vector3 L;
  Vector3 N;
  Vector3 V;
  N=intersection.normal();
  P=intersection.point();
  N = intersection.normal();
  N.normalize();

  P = intersection.point();

  V = -intersection.incident().direction();
  V.normalize();

  Material m=intersection.node()->primitive()->material();

  Vector3 result; // = m.ambient();
  m.ambient();

  int nbLight = _scene->nbLight();

  for (int i = 0; i< nbLight; i++) {
    L = _scene->lightPosition(i) - P;
    L.normalize();

    if (V.dot(N) < 0) N = -N;

    float diffus = max(N.dot(L),0.0);

    Ray shadow(P,_scene->lightPosition(i) - P);
    Intersection* inter = _scene->intersection(shadow,0.1);

    double S = m.shininess();
    Vector3 R = 2*N.dot(L)*N - L;
    R.normalize();

    double coef = max(V.dot(R),0.0);
    double spec = pow(coef,S);
    spec = spec;

    if (inter!=NULL) {
        double lambda = inter->lambda();
        if (lambda > 1)
            result += diffus*m.diffuse() + spec*m.specular();

    delete inter;

    } else {
        result += diffus*m.diffuse() + spec*m.specular();
    }

 }

  return result;
}


/** *************************************************************** **/
/** *************************************************************** **/
/** *************************************************************** **/
/** *************************************************************** **/
/** *************************************************************** **/
/** *************************************************************** **/
/** *************************************************************** **/
void Raytrace::run() {
  _stopRequest=false;
  computeImage();
}


/**
Boucle principale du lancer de rayon

*/
void Raytrace::computeImage() {
  _camera=_scene->camera();
  _camera.viewport(0,0,_width,_height);
  Vector3 eye(0.0,0.0,0.0);
  Vector3 pixel_eye; // pixel dans le repère observateur
  _image->fill(Qt::black);

  clock_t clockStart=clock();

  Matrix4 csg2Camera=_scene->localWorld();
  csg2Camera.mul(_camera.worldCamera());


  for(unsigned int y=0; y<_height; ++y) {
    for(unsigned int x=0; x<_width; ++x) {
      if (_stopRequest) goto fin;
      pixel_eye=_camera.windowToCamera(x,y); // exprime le rayon dans le repère de l'observateur.

      Ray rayon=Ray(eye,pixel_eye);  // rayon primaire
      rayon.transform(csg2Camera);
      Vector3 c=computeRayColor(rayon,4,1.0); // calcule la couleur du pixel; 10=profondeur max de récursion, 1.0=contribution; tous les calculs sont entendus dans le repère G
      // mise à jour de la couleur du pixel dans l'image résultante
      c.clamp(0,1);
      QColor color=QColor::fromRgbF(c.r(),c.g(),c.b());

      _image->setPixel(x,y,color.rgba()); // affecte à l'image la couleur calculée
    }
  }
fin:
  clock_t clockElapsed=clock()-clockStart;
  cout << "Raytracing finished in " << double(clockElapsed)/CLOCKS_PER_SEC << " seconds" << endl;
}



/** *********************************************************************************************************** */
/** *********************************************************************************************************** */
/** *********************************************************************************************************** */

Raytrace::Raytrace(unsigned int width,unsigned int height) {
    _image=new QImage(width,height,QImage::Format_ARGB32);
    _width=width;
    _height=height;
}

Raytrace::Raytrace() : Raytrace(512,512) {
}


Raytrace::~Raytrace() {
    close();
    delete _image;
}



void Raytrace::close() {
  if (isRunning()) {
    _stopRequest=true;
    while (isRunning()) {
      cout << "Im waiting" << endl;
      usleep(100);
    }
  }
}








