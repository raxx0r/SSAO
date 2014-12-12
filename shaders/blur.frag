#version 330 core

in vec2 tex_coords;

uniform sampler2D normal_tex;

layout (location = 0) out vec4 color;

void main() {
	vec4 phong_color = texture(normal_tex, tex_coords);
	float texel_size = 1.0 / 800.0;
	vec4 result = vec4(0.0);
	int count = 0;

	// Change this for blur effect. Set blur_size = 0 for no blur.
	int blur_size = 1;

	for(int i = -blur_size; i < blur_size + 1; i++) {
		for(int j = -blur_size; j < blur_size + 1; j++) {
			result += texture(normal_tex, tex_coords + vec2(i, j) * texel_size);
			count++;
		}
	}
	vec4 color_out = count == 0 ? phong_color : vec4(result.xyz / count, 1.0);
	color = color_out;
}