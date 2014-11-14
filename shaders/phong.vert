#version 330 core

in vec3 position;
in vec3 normal;

out vec3 t_normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

void main() {
	mat4 MVP = P * V * M;
	t_normal = normal * N;
	gl_Position = MVP * vec4(position, 1.0);
}