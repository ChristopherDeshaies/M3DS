#version 130

in vec3 fN,fL,fV;

out vec4 fragColor;

uniform vec3 materialDiffuse,materialSpecular;
uniform vec4 materialAmbient;

void main() {

  vec3 N,L,V,R;
  vec4 color=vec4(0,0,0,0);
  float diffuseIntensity=0.0;

  N=normalize(fN);
  L=normalize(fL);
  V=normalize(fV);
  R=normalize(2.0*dot(fL,fN)*fN-fL);

  // notez le max pour ne pas éclairer lorsque le produit scalaire est négatif (il faudra faire la même chose lors du calcul du spéculaire)
  diffuseIntensity=max(dot(N,L),0.0);

  // rouge, vert,bleu de l'éclairement :
  color.rgb= diffuseIntensity*materialDiffuse+materialAmbient.xyz + materialSpecular * pow(dot(V,R),50);
  // le alpha est porté uniquement par materialAmbient.a.:
  color.a=materialAmbient.a;

  fragColor=color;
}
