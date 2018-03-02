#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec3 v_normal;
layout (location = 2) in vec2 v_tex_coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 position;
out vec3 normal;
out vec2 tex_coord;

void main()
{
	position  = vec3(model* vec4(v_position, 1.0));
	normal    = mat3(transpose(inverse(model))) * v_normal; //TODO: MOVE THIS OUT TO CPU
    tex_coord = v_tex_coord;

	gl_Position = projection*view*vec4(position, 1.0);
}
