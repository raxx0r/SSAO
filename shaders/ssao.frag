#version 330 core

in vec2 tex_coords;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;

layout (location = 0) out float ssao_component;

float calculateAO(vec4 P, vec2 Po, vec3 n) {
	vec4 Pocc = texture(position_tex, Po);
	vec4 PC = normalize(Pocc - P);
	return max(dot(n, PC.xyz), 0);
}

void main() {
	vec2 pixel_size = 1.0 / vec2(800.0, 600.0);
	float occlusion = 0.0;
	vec4 P = texture(position_tex, tex_coords);
	vec3 n = texture(normal_tex, tex_coords).xyz;

	occlusion += calculateAO(P, tex_coords + pixel_size * vec2(-1.0, 0.0), n);
	occlusion += calculateAO(P, tex_coords + pixel_size * vec2(1.0, 0.0), n);
	occlusion += calculateAO(P, tex_coords + pixel_size * vec2(0.0, 1.0), n);
	occlusion += calculateAO(P, tex_coords + pixel_size * vec2(0.0, -1.0), n);

	ssao_component = occlusion / 1.0;
}
