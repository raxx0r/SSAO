#version 330 core

in vec2 texture;

out vec4 out_color;

void main() {
	out_color = vec4(texture.st, 0.0, 1.0);
}
