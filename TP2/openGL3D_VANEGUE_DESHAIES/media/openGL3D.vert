#version 130

in vec3 position; // Eyes Coordinates

//in vec3 color;
//q23
in vec3 normal;

out vec3 fColor;

uniform mat4 projection;
uniform mat4 transform;
uniform vec3 lightPosition; // position de la source lumineuse
uniform vec3 diffuseColor; // parametre la couleur de l'objet

void main() {
 //q11
 vec4 eyePosition=vec4(position,1.0); // passage en coordonnées homogènes
 vec4 clipPosition = projection*eyePosition; // transformation par la matrice de projection

 //q15
 eyePosition=transform*eyePosition;
 clipPosition=projection*eyePosition; // transformation par la matrice de projection
 // ou bien plus directement clipPosition = projection*transform*eyePosition;


 //norme
 vec3 N=normal;
 N=normalize(N);
 vec3 L=lightPosition;
 L=normalize(L);

 float intensity = max(dot(N,L),0.0);

 //fColor=color;
 //fColor=normal;
 fColor = vec3(intensity,intensity,intensity); //q24
 fColor = intensity*diffuseColor;


 gl_Position=clipPosition; // gl_Position doit être donné en clip coordinates
}
