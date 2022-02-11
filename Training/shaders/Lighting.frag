#version 330 core

in VS_OUT 
{
    vec4 frag_pos;
    vec3 normal;
    vec2 text_coord;
    vec4 frag_pos_light_space;
} fs_in;

uniform vec3 u_light_dir; 
uniform vec4 u_light_color;  

uniform vec4 u_ambient; 
uniform vec4 u_diffuse; 
uniform vec4 u_specular; 
uniform float u_shininess;
uniform mat4 u_model; 

uniform int u_uses_texture = 0;
uniform sampler2D u_texture;
uniform sampler2D u_shadow_map;

out vec4 out_frag_color;

float compute_shadow(vec4 frag_light_space)
{
    vec3 proj_coord = frag_light_space.xyz / frag_light_space.w;
    proj_coord = proj_coord * 0.5 + 0.5;
    float closest_depth = texture(u_shadow_map, proj_coord.xy).r; 
    float current_dept = proj_coord.z;
    return current_dept > closest_depth  ? 1.0 : 0.0;
}

vec4 compute_light()
{
    //ambient
    vec4 ambient = u_ambient * u_light_color;

     //shadow
    float shadow = compute_shadow(fs_in.frag_pos_light_space); 

    if(shadow > 0.0f)
        return ambient;

     else
     {
        vec3 normal = normalize(fs_in.normal);

        // diffuse
        float dot_p = dot(u_light_dir, normal);
        vec4 diffuse = u_diffuse * u_light_color * max(dot_p, 0.0);

        // specular
        const vec3 eye_pos = vec3(0,0,0) ;
        vec3 frag_pos = fs_in.frag_pos.xyz / fs_in.frag_pos.w;
        vec3 eye_dir = normalize(eye_pos - frag_pos); 
        vec3 light_dir = normalize (u_light_dir) ; 
        vec3 half_dir = normalize (light_dir + eye_dir) ; 
        dot_p = dot(normal, half_dir) ; 
        vec4 specular = u_specular * u_light_color * pow (max(dot_p, 0.0f), u_shininess); 

        return ambient + diffuse + specular;   
     }
  
}

void main() 
{     
    vec4 texture_color = texture(u_texture, fs_in.text_coord);
    vec4 lighting = compute_light();
    out_frag_color = lighting * texture_color;
}
