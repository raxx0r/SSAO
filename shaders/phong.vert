#version 330 core

in vec3 position;
in vec3 normal;

out vec3 t_normal;
out vec4 m_position;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;
uniform mat3 N;

void main() {
	t_normal =  N * normal;

	// Position in model-space;
	m_position = M * vec4(position, 1.0);
	
	gl_Position = P * V * M * vec4(position, 1.0);
}