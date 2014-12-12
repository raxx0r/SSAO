#version 330 core

in vec2 tex_coords;

uniform vec3 kernel[60];
uniform mat4 P;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;
uniform sampler2D rnd_normal_tex;

layout (location = 0) out float ssao_component;

void main() {
	vec2 u_noise_scale = vec2(800.0, 600.0) / 8.0;

	// TODO: Should be an user controlled uniform.
	float u_radius = 2.0;

	// Get position
	vec4 pos = texture(position_tex, tex_coords);

	// Get normal
	vec3 n = texture(normal_tex, tex_coords).xyz;

	// Get random vector from noise texture.
	vec3 rvec = vec3(texture(rnd_normal_tex, tex_coords * u_noise_scale).xy, 0.0) * 2.0 - 1.0;
	

   vec3 tangent = normalize(rvec - n * dot(rvec, n));
   vec3 bitangent = cross(n, tangent);
   mat3 tbn = mat3(tangent, bitangent, n);
	// Gram schm			idt - not used right now	
	/* 
	vec3 u1 = n;
	vec3 u2 = rvec - u1 * (dot(rvec, u1) / dot(u1, u1));
	vec3 u3 = cross(u1, u2);

	u1 = normalize(u1);
	u2 = normalize(u2);
	u3 = normalize(u3);

	mat3 cob = mat3(u1, u2, u3);
	*/

	float occlusion = 0.0;
	for (int i = 0; i < kernel.length(); i++) {

		// Reflecting sample on normal to locate it in hemisphere.
		// NOTE: We don't use any noise right now. The results could 
		// probably be improved if we used noise to rotate the kernel.
		vec3 sample = tbn * kernel[i];
		sample = sample * u_radius + pos.xyz;
		
		vec4 offset = vec4(sample, 1.0);
		offset = P * offset;
		offset.xy /= offset.w;
		offset.xy = offset.xy * 0.5 + 0.5;

		float sample_depth = texture(position_tex, offset.xy).z;
		//float len = length(sample - pos.xyz);

		float range_check = abs(pos.z - sample_depth) < u_radius ? 1.0 : 0.0; 
		//vec3 v = normalize(sample - pos.xyz);
		//float angle = dot(n, v) > 0 ? 1.0 : 0.0;
		occlusion += (sample_depth >= sample.z ? 1.0 : 0.0) * range_check;
	}
	
	occlusion = 1.0 - (occlusion / kernel.length());

	// Increase exponent to exaggerate AO effect.
	ssao_component = occlusion;
}
