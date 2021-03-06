#include <math.h>
#include "Car.h"
#include "GLTool.h"
#include "GLRender.h"

using namespace p3d;
using namespace std;


// ************************************************************
Car::~Car() {
}

Car::Car() {
  _orientation.setIdentity();
  _position.set(0,0,0);
  _steering=0;
  _rotateWheel=0;
  _acceleration=0;
  _velocity=0;
  _gyrophare=true;
}

// ******************************************************************
// méthodes à compléter lors du TP
void Car::drawRim() {
    p3d::diffuseColor=Vector3(1,1,1);

    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.scale(0.1,0.1,2.0);
    drawCylinder();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(0.05,0.05,1.0);
    p3d::modelviewMatrix.rotate(45,1,0,0);
    p3d::modelviewMatrix.translate(-0.05,-0.05,-1.0);
    p3d::modelviewMatrix.scale(0.1,0.1,2.0);
    drawCylinder();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(0.05,0.05,1.0);
    p3d::modelviewMatrix.rotate(90,1,0,0);
    p3d::modelviewMatrix.translate(-0.05,-0.05,-1.0);
    p3d::modelviewMatrix.scale(0.1,0.1,2.0);
    drawCylinder();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(0.05,0.05,1.0);
    p3d::modelviewMatrix.rotate(135,1,0,0);
    p3d::modelviewMatrix.translate(-0.05,-0.05,-1.0);
    p3d::modelviewMatrix.scale(0.1,0.1,2.0);
    drawCylinder();

    p3d::modelviewMatrix.pop();

}

void Car::drawWheel() {

    drawRim();

    p3d::modelviewMatrix.push();

    p3d::diffuseColor=Vector3(0,0,0);

    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.translate(-0.95,0.0,0.0);
    p3d::modelviewMatrix.scale(1.12,1.12,1.1);
    drawTorus();

    p3d::modelviewMatrix.pop();
}

void Car::drawAxle() {

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(0,0,1.0);
    p3d::modelviewMatrix.rotate(_rotateWheel,1,0,0);
    p3d::modelviewMatrix.translate(0,0,-1.0);
    drawWheel();
    p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.push();
    p3d::modelviewMatrix.translate(3.0,0.0,0.0);
        p3d::modelviewMatrix.push();
            p3d::modelviewMatrix.translate(0,0,1.0);
            p3d::modelviewMatrix.rotate(_rotateWheel,1,0,0);
            p3d::modelviewMatrix.translate(-0,-0,-1.0);
            drawWheel();
        p3d::modelviewMatrix.pop();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.rotate(90,0,1,0);
    p3d::modelviewMatrix.translate(-1.0,0.0,0.0);
    p3d::modelviewMatrix.scale(0.2,0.2,3.0);
    p3d::diffuseColor=Vector3(0,0,0);
    drawCylinder();


    p3d::modelviewMatrix.pop();
}

void Car::drawBody() {
    p3d::modelviewMatrix.push();

    p3d::diffuseColor=Vector3(1,1,1);

    p3d::modelviewMatrix.translate(0,3,0);
    drawCube();

    p3d::diffuseColor=Vector3(0,0,1);
    p3d::modelviewMatrix.translate(2,-2,0);
    p3d::modelviewMatrix.scale(3.0,1.0,1.0);
    drawCube();

    p3d::modelviewMatrix.pop();
    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(0,4,0);
    p3d::modelviewMatrix.scale(0.2,0.6,0.2);
    if(_gyrophare){
      p3d::diffuseColor=Vector3(0,0,1);
    }else{
      p3d::diffuseColor=Vector3(0,0,0);
    }
    drawCube();

    p3d::modelviewMatrix.pop();
}

void Car::draw() {
  p3d::modelviewMatrix.push();


  p3d::modelviewMatrix.translate(0,-2,0);
  drawBody();

  p3d::modelviewMatrix.translate(-0.5,0,1.5);
  p3d::modelviewMatrix.rotate(90,0,1,0);
  drawAxle();


  p3d::modelviewMatrix.translate(0,0,3);

    p3d::modelviewMatrix.push();

    p3d::modelviewMatrix.translate(1.5,0,0);
    p3d::modelviewMatrix.rotate(_steering,0,1,0);
    p3d::modelviewMatrix.translate(-1.5,0,0);
    drawAxle();

    p3d::modelviewMatrix.pop();
  p3d::modelviewMatrix.pop();



}


void Car::drawWorld() {

  p3d::modelviewMatrix.push();

  p3d::modelviewMatrix.translate(_position);
  p3d::modelviewMatrix.rotate(_orientation);

  draw(); // tracé de la voiture dans son repère local
  p3d::modelviewMatrix.pop();
}

void Car::move() {
  _acceleration+=-_velocity/100000;
  _velocity+=_acceleration;
  _rotateWheel+=_velocity*20;
  _steering-=_steering/10*fabs(_velocity);


  Vector3 uneDirection = _orientation * Vector3(1.0,0.0,0.0);
  _position = _position + uneDirection;

  _orientation.rotate(_steering*_velocity/(1.0+fabs(_velocity)),Vector3(0,1,0)); // le /100 est déterminé par essai/erreur

}


void Car::accelerate() {
  _acceleration=0.05;

}

void Car::decelerate() {
  _acceleration=0;
}

void Car::brake() {
  _acceleration=-0.02;

}

void Car::turnLeft() {
  _steering+=0.5;
  if (_steering>35) _steering=35;
}

void Car::turnRight() {
  _steering-=0.5;
  if (_steering<-35) _steering=-35;
}

void Car::gyrophareOn(){
    if(_gyrophare){
        _gyrophare=false;
    }else{
        _gyrophare=true;
    }
}




