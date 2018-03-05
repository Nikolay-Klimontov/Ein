#version 330 core

in vec4 position;
in vec4 normal;
in vec2 tex_coord;

uniform sampler2D diffuse_map;
uniform sampler2D specular_map;

uniform vec3 camera_position;

//Light source
struct Light
{
    vec3 color;
    vec3 position;
};

uniform Light light;
uniform vec4 ambient;

void main()
{
// diffuse lighting
    vec4  norm = normalize(normal);
    vec4 light_dir = normalize(vec4(light.position, 1.0f) - position);
    float diff = max(dot(light_dir, norm), 0);
    vec4  diffuse = diff * vec4(light.color, 1.0) * texture(diffuse_map, tex_coord);
// specular lighting
    vec4 cam_dir = normalize(vec4(camera_position, 1.0f) - position);
    vec4 reflect_dir = reflect(-light_dir, norm);
    float spec = pow(max(dot(cam_dir, reflect_dir), 0.0), 64.0);
    vec4 specular = diff * spec * texture(specular_map, tex_coord);

    vec4 light_color = diffuse + specular + ambient * texture(diffuse_map, tex_coord);

	gl_FragColor = light_color;
}