// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19
//

in vec3 pos;
in vec3 col;
out vec4 out_color;

uniform mat4 u_ModelViewProjectionMatrix;

void main(void)
{
   gl_Position = u_ModelViewProjectionMatrix * vec4(pos, 1);
   out_color = vec4(col, 1.0);
}
