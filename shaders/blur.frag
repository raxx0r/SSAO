#version 330 core

in vec2 tex_coords;

uniform sampler2D normal_tex;

layout (location = 0) out float blurred_ssao_component;

void main() {
	float ssao_color = texture(normal_tex, tex_coords).r;
	vec2 texel_size = 1.0 / vec2(800.0, 600);
	float result = 0.0;
	int count = 0;

	// Change this for blur effect. Set blur_size = 0 for no blur.
	int blur_size = 2;

	for(int i = -blur_size; i < blur_size + 1; i++) {
		for(int j = -blur_size; j < blur_size + 1; j++) {
			vec2 coords = tex_coords + vec2(i, j) * texel_size;
			if (coords.x > 0.0 && coords.y > 0.0) {
				result += texture(normal_tex, abs(coords)).r;
				count++;
			}
		}
	}
	float color_out = count == 0 ? ssao_color : result / count;
	blurred_ssao_component = color_out;
}
