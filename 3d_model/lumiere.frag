// Cours de Réalité Virtuelle
// leo.donati@univ-cotedazur.fr
//
// EPU 2018-19

varying vec3 frag_pos;
varying vec3 out_normal;
varying mediump vec2 tex_coord;

uniform sampler2D texture0;
uniform vec4 light_ambient_color;
uniform vec4 light_diffuse_color;
uniform vec4 light_specular_color;
uniform float light_specular_strength;
uniform vec3 light_position;
uniform vec3 view_position;
uniform float opacity;

void main(void)
{
    // texture color
    vec4 texColor = texture2D(texture0, tex_coord);

    // ambient component
    vec4 ambient = texColor * light_ambient_color;

    // diffuse component
    vec3 norm = normalize(out_normal);
    vec3 lightdir = normalize(light_position - frag_pos);
    float coeff_diffusion = max(dot(lightdir, norm), 0.0);
    vec4 diffuse = (coeff_diffusion * light_diffuse_color) * texColor;

    // specular component
    vec3 viewdir = normalize(frag_pos - view_position);
    vec3 reflectdir = reflect(lightdir, norm);
    float coeff_specular = pow(max(dot(viewdir, reflectdir), 0.0), light_specular_strength);
    vec4 specular = (coeff_specular * light_specular_color) * texColor;

    // final color
    gl_FragColor = (ambient + diffuse + specular);
    gl_FragColor.a = opacity;
}
