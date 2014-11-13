#version 330 core

in vec2 position;
uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

void main() {
	mat4 MVP = P * V * M;
	gl_Position = MVP * vec4(position, 0.0, 1.0);
}