#include "Revolution.h"

#include "glsupport.h"


#include "GLRender.h"

#include "Vector3.h"

#include "GLTool.h"


using namespace std;
using namespace p3d;

Revolution::Revolution() {
  // default profile
  _profile.push_back(Vector3(-0.8,0.6,0.0));
  _profile.push_back(Vector3(-0.3,0.2,0.0));
  _profile.push_back(Vector3(-0.9,-0.8,0.0));

}


void Revolution::initSphere() {
    vector<float> p;
    vector<float> n;
    vector<float> t;
    vector<unsigned int> index;

    int nbSlice=20;
    // include last slice that closes sphere
    int nbStack=20;

    double theta = (2 * M_PI) / nbSlice;
    double phi = M_PI / nbStack;

    double s = theta / (2 * M_PI);
    double ta = phi / M_PI;


    // ******* // TODO
    for(int i=0; i<=nbSlice; i++) {
        for(int j=1; j<=nbStack; j++) {
            double x = cos(theta * (double)j) * sin(phi * (double)i);
            double y = cos(phi * (double)i);
            double z = sin(theta * (double)j) * sin(phi * (double)i);

            p.push_back(x);
            p.push_back(y);
            p.push_back(z);

        }
    }

    for(int i=0; i<=nbSlice; i++) {
        for(int j=1; j<=nbStack; j++) {

            int hg=0;
            int hd=0;
            int bg=0;
            int bd=0;

            if(i==19){
                hg = j * nbStack + i ;
                hd = j * nbStack + i + 1 -20;
                bg = (j-1) * nbStack + i ;
                bd = (j-1) * nbStack + i + 1 - 20;

                t.push_back(s*nbSlice - s*j);
                t.push_back(0);

            }else{
                hg = j * nbStack + i;
                hd = j * nbStack + i + 1;
                bg = (j-1) * nbStack + i;
                bd = (j-1) * nbStack + i + 1;

                t.push_back(s*nbSlice - s*j);
                t.push_back(ta*nbStack - ta*i);
            }

            cout << " hg = " << hg;
            cout << " hd = " << hd;
            cout << " bg = " << bg;
            cout << " bd = " << bd << endl;


            index.push_back(hg);
            index.push_back(bg);
            index.push_back(bd);
            index.push_back(bd);
            index.push_back(hd);
            index.push_back(hg);

            float x=cos(theta*j)*sin(phi*i);
            float y=cos(phi*i);
            float z=sin(theta*j)*sin(phi*i);

            n.push_back(sqrt(x*x+y*y+z*z));
            n.push_back(sqrt(x*x+y*y+z*z));
            n.push_back(sqrt(x*x+y*y+z*z));

        }
    }
    // *******

    initVAO(index,p,n,t);
    _texture=&_earth;
}


void Revolution::initCube() {
  vector<float> p;
  vector<float> n;
  vector<float> t;

  vector<unsigned int> index;

  // *******
  //  TODO

  /* // q1

      for(int x=-1; x<=1; x+=2) {
          for(int y=-1; y<=1; y+=2) {
              for(int z=-1; z<=1; z+=2) {
                    p.push_back(x);
                    p.push_back(y);
                    p.push_back(z);
                }
            }
        }


    //face 1
    index.push_back(2);
    index.push_back(0);
    index.push_back(6);
    index.push_back(6);
    index.push_back(0);
    index.push_back(4);

    //face 2
    index.push_back(2);
    index.push_back(0);
    index.push_back(3);
    index.push_back(3);
    index.push_back(0);
    index.push_back(1);

    //face 3
    index.push_back(3);
    index.push_back(7);
    index.push_back(1);
    index.push_back(1);
    index.push_back(7);
    index.push_back(5);

    //face 4
    index.push_back(1);
    index.push_back(0);
    index.push_back(5);
    index.push_back(5);
    index.push_back(0);
    index.push_back(4);

    //face 5
    index.push_back(5);
    index.push_back(4);
    index.push_back(7);
    index.push_back(7);
    index.push_back(4);
    index.push_back(6);

    //face 6
    index.push_back(6);
    index.push_back(7);
    index.push_back(2);
    index.push_back(2);
    index.push_back(7);
    index.push_back(3);

    */

  // q2 et q3


  //Face

  //Triangle 1

  //1
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(0);
  t.push_back(0.33);
  t.push_back(1);

  //2
  p.push_back(-1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(1);
  t.push_back(0);
  t.push_back(1);

  //3
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(2);
  t.push_back(0);
  t.push_back(0.5);


  //Triangle 2
  //3
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(3);
  t.push_back(0);
  t.push_back(0.5);

  //2
  p.push_back(1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(4);
  t.push_back(0.33);
  t.push_back(0.5);

  //1
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(1);
  index.push_back(5);
  t.push_back(0.33);
  t.push_back(1);

  //Face Droit

  //Triangle 1

  //1
  p.push_back(1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(6);
  t.push_back(0.66);
  t.push_back(0.5);

  //2
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(7);
  t.push_back(0.33);
  t.push_back(0.5);

  //3
  p.push_back(1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(8);
  t.push_back(0.66);
  t.push_back(0);

  //Triangle 2

  //3
  p.push_back(1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(9);
  t.push_back(0.66);
  t.push_back(0);

  //2
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(10);
  t.push_back(0.33);
  t.push_back(0.5);

  //1
  p.push_back(1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(11);
  t.push_back(0.33);
  t.push_back(0);




  //Face Dessus

  //Triangle 1

  //1
  p.push_back(1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(12);
  t.push_back(1);
  t.push_back(1);

  //2
  p.push_back(-1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(13);
  t.push_back(0.66);
  t.push_back(1);

  //3
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(14);
  t.push_back(1);
  t.push_back(0.5);

  //Triangle 2

  //3
  p.push_back(1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(15);
  t.push_back(1);
  t.push_back(0.5);

  //2
  p.push_back(-1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(16);
  t.push_back(0.66);
  t.push_back(1);

  //1
  p.push_back(-1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(1);
  n.push_back(0);
  index.push_back(17);
  t.push_back(0.66);
  t.push_back(0.5);


  //Arriere Fond

  //Triangle 1

  //1
  p.push_back(-1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(18);
  t.push_back(0.66);
  t.push_back(0.5);

  //2
  p.push_back(1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(19);
  t.push_back(1);
  t.push_back(0.5);

  //3
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(20);
  t.push_back(0.66);
  t.push_back(0);

  //Triangle 2

  //3
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(21);
  t.push_back(0.66);
  t.push_back(0);

  //2
  p.push_back(1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(22);
  t.push_back(1);
  t.push_back(0.5);

  //1
  p.push_back(1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  n.push_back(-1);
  index.push_back(23);
  t.push_back(1);
  t.push_back(0);




  //Arriere Gauche

  //Triangle 1

  //1
  p.push_back(-1);
  p.push_back(1);
  p.push_back(-1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(24);
  t.push_back(0.33);
  t.push_back(1);

  //2
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(25);
  t.push_back(0.33);
  t.push_back(0.5);

  //3
  p.push_back(-1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(26);
  t.push_back(0.66);
  t.push_back(1);

  //Triangle 2

  //3
  p.push_back(-1);
  p.push_back(1);
  p.push_back(1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(27);
  t.push_back(0.66);
  t.push_back(1);

  //2
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(28);
  t.push_back(0.33);
  t.push_back(0.5);

  //1
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(-1);
  n.push_back(0);
  n.push_back(0);
  index.push_back(29);
  t.push_back(0.66);
  t.push_back(0.5);


  //Arriere Base

  //Triangle 1

  //1
  p.push_back(1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(30);
  t.push_back(0.33);
  t.push_back(0.5);

  //2
  p.push_back(1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(31);
  t.push_back(0.33);
  t.push_back(0);

  //3
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(32);
  t.push_back(0);
  t.push_back(0.5);


  //Triangle 2

  //3
  p.push_back(1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(33);
  t.push_back(0.33);
  t.push_back(0);

  //2
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(34);
  t.push_back(0);
  t.push_back(0);

  //1
  p.push_back(-1);
  p.push_back(-1);
  p.push_back(-1);
  n.push_back(0);
  n.push_back(-1);
  n.push_back(0);
  index.push_back(35);
  t.push_back(0);
  t.push_back(0.5);


  // *******




  initVAO(index,p,n,t);

  _texture=&_dice;
}


void Revolution::initRevolution() {
  if (_profile.size()<2) return; // more than 2 vertices in the profile

  vector<float> p;
  vector<float> n;
  vector<float> t;

  vector<unsigned int> index;

  int nbSlice=40; // include last slice that closes the object
  int nbStack=_profile.size();

  std::vector<Vector3> normalProfile; // to compute normal profile

  // *******
  //  TODO




  // *******





  initVAO(index,p,n,t);
  _texture=&_ul1;
}


void Revolution::init() {
  glGenBuffers(1,&_vbo);
  glGenBuffers(1,&_elementBuffer);
  glGenVertexArrays(1,&_vao);

  _earth.readMipmap("EarthDay512.jpg");
  _dice.readMipmap("dice.png");
  _ul1.readMipmap("UL1-IEEA.jpg");

}


void Revolution::draw(EShader mode) {
//  return;
  glBindVertexArray(_vao);


  p3d::material(Vector4(0,0,0,1),Vector3(0,0.8,0.2),Vector3(0,0.2,0.8),100);
  p3d::diffuseBackColor=Vector3(0.8,0,0);
  if (mode==Shader_Ambient) {
    p3d::ambientColor=Vector4(0.0,0.8,0,1);
    p3d::ambientBackColor=Vector4(0.8,0.0,0,1);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  }
  else {
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  }

  _texture->bind(0);

  switch(mode) {
  case Shader_Ambient:p3d::shaderVertexAmbient();break;
  case Shader_Light:p3d::shaderLightPhong();break;
  case Shader_Texture:p3d::shaderTextureLight();break;
  }

  glDrawElements(GL_TRIANGLES,_nbElement,GL_UNSIGNED_INT,0);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBindVertexArray(0);

}


// Caution : position should be a (x,y,z) array, normal (x,y,z) array, texCoord (x,y) array. lengths should be coherent
void Revolution::initVAO(const std::vector<unsigned int> &index,const std::vector<float> &position,const std::vector<float> &normal,const std::vector<float> &texCoord) {

  vector<float> attrib;
  attrib.resize(position.size()*8);
  for(unsigned int i=0;i<position.size()/3;++i) {
    attrib[i*8+0]=position[i*3+0];
    attrib[i*8+1]=position[i*3+1];
    attrib[i*8+2]=position[i*3+2];

    if (!normal.empty()) {
      attrib[i*8+3]=normal[i*3+0];
      attrib[i*8+4]=normal[i*3+1];
      attrib[i*8+5]=normal[i*3+2];
    }

    if (!texCoord.empty()) {
      attrib[i*8+6]=texCoord[i*2+0];
      attrib[i*8+7]=texCoord[i*2+1];
    }
  }



  glBindBuffer(GL_ARRAY_BUFFER,_vbo);
  glBufferData(GL_ARRAY_BUFFER,attrib.size()*sizeof(float),attrib.data(),GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,index.size()*sizeof(unsigned int),index.data(),GL_STATIC_DRAW);
  _nbElement=index.size();

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER,_vbo);

  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,8*sizeof(float),0);                                   // position
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,8*sizeof(float),(const GLvoid *)(3*sizeof(float)));   // normal
  glVertexAttribPointer(2,2,GL_FLOAT,GL_FALSE,8*sizeof(float),(const GLvoid *)(6*sizeof(float)));   // texCoord

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,_elementBuffer);

  glBindVertexArray(0);

}

void Revolution::drawProfile() {
  p3d::ambientColor=Vector4(1,0,0,1);
  p3d::shaderVertexAmbient();
  p3d::drawLineStrip(_profile);
  p3d::drawPoints(_profile);

  vector<Vector3> mirror;
  for(auto &p:_profile) {
    mirror.push_back(Vector3(-p.x(),p.y(),p.z()));
  }

  p3d::uniformAmbient(Vector4(0,0,0,1));
  p3d::drawLineStrip(mirror);
  p3d::drawPoints(mirror);

  p3d::uniformAmbient(Vector4(0,1,0,1));
  p3d::drawLines({Vector3(0,-1,0),Vector3(0,1,0)});



}



