#version 330 core

layout(location = 0) out vec4 out_frag_color;

in VS_OUT 
{
    vec3 frag_pos;
    vec3 normal;
    vec2 text_coord;
    vec4 frag_pos_light_space;
} fs_in;

uniform vec3 u_eye_loc;
uniform vec3 u_light_loc; 
uniform vec4 u_light_color; 

uniform float u_near_plane;
uniform float u_far_plane;

uniform vec4 u_ambient; 
uniform vec4 u_diffuse; 
uniform vec4 u_specular; 
uniform float u_shininess;
uniform mat4 u_model; 

uniform sampler2D u_texture;
uniform sampler2DShadow u_shadow_map;

uniform int u_ambient_enabled;
uniform int u_diffuse_enabled;
uniform int u_specular_enabled;
uniform int u_shadow_enabled;
uniform int u_texture_enabled;

float compute_shadow(vec4 frag_light_space)
{
    if(u_shadow_enabled == 0)
        return 0.0f;
    
    vec3 proj_coord = frag_light_space.xyz / frag_light_space.w;
    proj_coord = proj_coord * 0.5 + 0.5;
    float current_dept = proj_coord.z;
    float shadow = 0.0;
    vec2 texel_size = 1.0 / textureSize(u_shadow_map, 0);
    for(int x = -1; x <= 1; ++x)
    {   
        for(int y = -1; y <= 1; ++y)
        {
            
            shadow += 1 - texture(u_shadow_map, vec3(proj_coord.xy + vec2(x, y) * texel_size, current_dept));      
        }  
    }
    shadow /= 9.0;
    return shadow;
}

vec4 compute_light()
{
    vec3 normal = normalize(fs_in.normal);
    vec3 light_dir = normalize(u_light_loc - fs_in.frag_pos);

    //ambient
    vec4 ambient = vec4(0.0f, 0.0f, 0.0f, 1.0f);;
    if (u_ambient_enabled != 0)
        ambient = u_ambient * u_light_color;
     
    // diffuse
    vec4 diffuse = vec4(0.0f, 0.0f, 0.0f, 1.0f);;
    if (u_diffuse_enabled != 0)
    {
        float dot_p = dot(light_dir, normal);
        diffuse = u_diffuse * u_light_color * max(dot_p, 0.0);
    }
   
    // specular
    vec4 specular = vec4(0.0f, 0.0f, 0.0f, 1.0f);
    if (u_specular_enabled != 0)
    {
        vec3 view_dir = normalize(u_eye_loc - fs_in.frag_pos);
        vec3 half_dir = normalize (light_dir + view_dir) ; 
        float dot_p = dot(normal, half_dir) ; 
        specular = u_specular * u_light_color * pow (max(dot_p, 0.0f), u_shininess); 
    }

    //shadow
    float shadow = compute_shadow(fs_in.frag_pos_light_space);
    
    return ambient + (1.0 - shadow) * (diffuse + specular);   
}

void main() 
{     
    vec4 texture_color = vec4(0.6f, 0.6f, 0.6f, 1.0f);

    if (u_texture_enabled != 0)
        texture_color = texture(u_texture, fs_in.text_coord);

    vec4 lighting = compute_light();

    out_frag_color = lighting * texture_color;
}
