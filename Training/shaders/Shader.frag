
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_tex_coord;
in vec4 vert_color;

uniform vec4 u_color;
uniform vec2 u_resolution;
uniform mat4 u_mvp;

void main()
{
	color = vert_color;
};