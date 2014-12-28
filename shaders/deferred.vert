#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

out vec3 t_normal;
out vec4 mv_position;

void main() {
	t_normal = N * normal;
	
	// Position in view-space;
	mv_position = V * M * vec4(position, 1.0);

	gl_Position = P * V * M * vec4(position, 1.0);
}
