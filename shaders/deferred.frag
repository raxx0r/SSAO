#version 330 core

in vec3 t_normal;
in vec4 mv_position;

uniform mat4 V;

layout (location = 0) out vec3 out_normal;
layout (location = 1) out vec4 out_position;

void main() {
	out_normal = normalize(t_normal);
	out_position = mv_position;
}