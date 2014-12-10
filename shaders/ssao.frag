#version 330 core

in vec2 tex_coords;

uniform vec3 kernel[15];
uniform mat4 P;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;
uniform sampler2D rnd_normal_tex;

layout (location = 0) out float ssao_component;

void main() {
	vec2 pixel_size = 1.0 / vec2(800.0, 600.0);

	// TODO: Should be an user controlled uniform.
	float uRadius = 1;

	vec4 pos = texture(position_tex, tex_coords);
	vec3 n = texture(normal_tex, tex_coords).rgb;
	// vec2 rnd_n = normalize(texture(rnd_normal_tex, tex_coords * (800.0 / 64.0)).rg);

	float occlusion = 0.0;
	for (int i = 0; i < kernel.length(); i++) {
		vec3 sample = kernel[i];
		sample = sample * uRadius + pos.xyz;
		vec4 offset = vec4(sample, 1.0);
		offset = P * offset;
		offset.xy /= offset.w;
		offset.xy = (offset.xy * 0.5) + 0.5;

		float sampleDepth = texture(position_tex, offset.xy).z;

		float rangeCheck = abs(pos.z - sampleDepth) < uRadius ? 1.0 : 0.0;
		occlusion += (sampleDepth <= sample.z ? 1.0 : 0.0) * rangeCheck;
	}

	ssao_component = occlusion / kernel.length();
}
