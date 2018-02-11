#version 330 core

in vec4 position;
in vec3 normal;
in vec2 tex_coord;

uniform sampler2D diffuse_map;

void main()
{
	gl_FragColor = texture(diffuse_map, tex_coord);
}