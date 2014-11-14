#version 330 core

in vec3 position;
in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
	mat4 MVP = P * V * M;
	gl_Position = MVP * vec4(position, 1.0);
}