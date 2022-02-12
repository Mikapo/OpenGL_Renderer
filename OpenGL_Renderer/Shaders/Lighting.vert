#version 330 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec3 l_normal; 
layout (location = 2) in vec2 l_texture_coordinates;

out VS_OUT 
{
    vec3 frag_pos;
    vec3 normal;
    vec2 text_coord;
    vec4 frag_pos_light_space;
} vs_out;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform mat4 u_light_space_matrix;

void main() 
{
    vs_out.frag_pos = vec3(u_model * vec4(l_position, 1));
    vs_out.normal = transpose(inverse(mat3(u_model))) * l_normal;
    vs_out.text_coord = l_texture_coordinates;
    vs_out.frag_pos_light_space = u_light_space_matrix * vec4(vs_out.frag_pos, 1);
    gl_Position = u_projection * u_view * vec4(vs_out.frag_pos, 1);
}