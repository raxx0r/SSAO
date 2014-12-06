#version 330 core

in vec2 tex_coords;
uniform sampler2D tex;
out vec4 out_color;

void main() {
	vec4 tex_color = texture(tex, tex_coords);
	out_color = tex_color;
}
