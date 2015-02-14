#version 130
        
in vec3 position;
/* color */
in vec4 fcolor;
out vec4 fColor;
/* coef */
uniform float coeff;

/* q22 */
in vec2 texCoord;
out vec2 fTexCoord;

void main() {
    fTexCoord=texCoord;
    vec3 newPosition = position*coeff;
    gl_Position=vec4(newPosition,1.0);

    fColor = fcolor;
}
