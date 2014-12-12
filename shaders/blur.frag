#version 330 core

in vec2 tex_coords;

uniform sampler2D position_tex;

layout (location = 0) out vec4 color;

void main() {
	color = texture(position_tex, tex_coords).bgra;
}
