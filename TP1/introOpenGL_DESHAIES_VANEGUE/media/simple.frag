#version 130

out vec4 fragColor;
in vec4 fColor;

/* q23 */
in vec2 fTexCoord;

uniform sampler2D texture;
uniform float coeff;

void main() {
  //  fragColor=fColor;
   // fragColor=texture2D(texture,fTexCoord);

    //q29
    // rouge de la texture multiplié par le rouge de fColor, idem pour green, et blue.
    fragColor=texture2D(texture,fTexCoord)*fColor;
    // fColor est la couleur interpolée aux sommets(questions précédentes)

    //q30
    fragColor=texture2D(texture,fTexCoord)*fColor.b;
    // coeff = uniform passée par l'application (questions précédentes.
    fragColor.g*=(1.0-coeff);

}
