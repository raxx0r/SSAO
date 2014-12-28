#version 330 core

in vec2 tex_coords;

uniform vec3 kernel[60];
uniform mat4 P;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;
uniform sampler2D rnd_normal_tex;

layout (location = 0) out float ssao_component;

#if 0 // Set to 1 and blur_size@blur.frag to 0 if we want the "presentable" rendering.
	float u_radius = 2.5;
	float amplitude = 5.0;
#else
	float u_radius = 3.0;
	float amplitude = 5.0;
#endif

void main() {
	vec2 u_noise_scale = vec2(800.0, 600.0) / 64.0;

	// Get position
	vec4 pos = texture(position_tex, tex_coords);

	// Get normal
	vec3 n = texture(normal_tex, tex_coords).xyz;

	// Get random vector from noise texture.
	vec3 rvec = vec3(texture(rnd_normal_tex, tex_coords * u_noise_scale).xy, 0.0) * 2.0 - 1.0;
	
	// Gram schmidt
	vec3 u1 = normalize(rvec - n * dot(rvec, n));
	vec3 u2 = cross(n, u1);
	mat3 cob = mat3(u1, u2, n);

	float occlusion = 0.0;
	for (int i = 0; i < kernel.length(); i++) {
		// Transform kernel to be inside hemisphere
		vec3 sample = cob * kernel[i];
		sample = sample * u_radius + pos.xyz;
		
		// Project the sample point to texture coordinates
		vec4 offset = vec4(sample, 1.0);
		offset = P * offset;
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;
		
		// Calculate the sample depth and the distance between orogin to sample point
		float sample_depth = texture(position_tex, offset.xy).z;
		float len = length(sample - pos.xyz);
		
		// Make a range check with a specific radius to prevent AO on objects far behind
		float range_check = abs(pos.z - sample_depth) < u_radius ? 1.0 : 0.0; 
		
		// Calculate the occlusion
		occlusion += (len / (1 + len * len)) * (sample_depth >= sample.z ? 1.0 : 0.0) * range_check;
	}
	
	occlusion = max(1.0 - (amplitude * occlusion / kernel.length()), 0.0);
	ssao_component = occlusion;
}
