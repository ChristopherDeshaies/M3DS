#include "GLApplication.h"

#include <iostream>

using namespace std;
using namespace p3d;

GLApplication::~GLApplication() {
}

GLApplication::GLApplication() {

  _lightPosition.set(0,0,0);

  _basicMesh.initTetrahedron();

  _angle=0.0;

  //q11
 // _projection de classe Matrix4 (déclaré dans GLApplication.h)
  _projection.setOrtho(-20,20,-20,20,-5,100); // cf calcul de la matrice dans le cours

  //q13.1
  //_projection.setOrtho(-18,22,-10,30,5,100);
  //q13.2
  //_projection.setOrtho(-5,2,-10,10,5,100);

  //q14
  //_projection.setOrtho(-20,20,-20,20,5,1e8);

  //q16
  // _obj déjà déclaré en ObjLoader
  //_obj.readInit("cube.obj",Vector3(-10,-10,-30),Vector3(10,10,-10)); // reporte l'objet dans la boite d'extémités (-10,-10,-30) et (10,10,-10)

  //q19
  _obj.readInit("cow.obj",Vector3(-10,-10,-30),Vector3(10,10,-10)); // reporte l'objet dans la boite d'extémités (-10,-10,-30) et (10,10,-10)

  _basicMesh.initObj(_obj); // pour remplacer l'initialisation du tétraèdre

}




/** ********************************************************************** **/
void GLApplication::initialize() {
  // appelée 1 seule fois à l'initialisation du contexte
  // => initialisations OpenGL
  glClearColor(1,1,1,1);

//  glLineWidth(2.0);
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  //q8
  glEnable(GL_DEPTH_TEST); // activation Depth Buffer (opérations écriture/tests)
  glDepthFunc(GL_LESS);  // le test passe si depth(src) < depth(dst)
  glClearDepth(1.0); // valeur d'initialisation du depth destination de tous les pixels lors d'un glClear


  //q9
  glEnable(GL_DEPTH_TEST); // activation Depth Buffer (opérations écriture/tests)
//  glDepthFunc(GL_GREATER);  // le test passe si depth(src) < depth(dst)
//  glClearDepth(0.5); // valeur d'initialisation du depth destination de tous les pixels lors d'un glClear

  _shader.attribute("position",0);
  //_shader.attribute("color",1);
  _shader.attribute("normal",1); //q23

  _shader.read("openGL3D");



  _basicMesh.initDraw();
}

void GLApplication::resize(int width,int height) {
  // appelée à chaque dimensionnement du widget OpenGL
  // (inclus l'ouverture de la fenêtre)
  // => réglages liés à la taille de la fenêtre
  glViewport(0,0,width,height);
  // ...
}

void GLApplication::update() {
  // appelée toutes les 20ms (60Hz)
  // => mettre à jour les données de l'application
  // avant l'affichage de la prochaine image (animation)
  // ...

  //_angle+=0.2;
  //_angle=0.0; //q21
  _angle+=2;

  _transform.setTranslation(0,0,-15);
  _transform.rotate(_angle,Vector3(1,0.2,0));
  _transform.translate(0,0,15);
}

void GLApplication::draw() {
  // appelée après chaque update
  // => tracer toute l'image

  //glClear(GL_COLOR_BUFFER_BIT);

  //q8
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // affecte le color buffer et le depth buffer avec les valeurs d'initialisation


  glUseProgram(_shader.id());

  _basicMesh.draw();


  _shader.uniform("projection",_projection); // utilisation de la classe shader // pour alléger la syntaxe OpenGL  //q11
  _shader.uniform("transform", _transform);  //q15

  //position de la source lumineuse
  _lightPosition=Vector3(1,1,1); //q24
  _lightPosition=Vector3(-1,0,1); //q25

  _shader.uniform("lightPosition",_lightPosition); //q24
  _shader.uniform("diffuseColor",Vector3(0.2,0.8,0.2));

  glUseProgram(0);

  snapshot(); // capture opengl window if requested
}

/** ********************************************************************** **/
/** i = button number, s = button text
 */
void GLApplication::leftPanel(int i,const std::string &s) {
  cout << "GLApplication : button clicked " << i << " " << s << endl;
  /*
  switch (i) {
    case 0:menu0();break;
    case 1:menu1();break;
  }
  */
}

/** *********************************************************** **/




