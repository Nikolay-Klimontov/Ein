#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 position;
out vec4 normal;
out vec2 tex_coord;

void main()
{
	position  = model* vec4(v_position, 1.0);
	normal    = transpose(inverse(model)) * vec4(v_normal, 0.0f); //TODO: MOVE MATRIX COMPUTATION OUT TO CPU
    tex_coord = v_tex_coord;

	gl_Position = projection*view*position;
}
