#version 330 core

in vec2 tex_coords;

uniform sampler2D position_tex;
uniform sampler2D normal_tex;

layout (location = 0) out vec4 ssao_component;

void main() {
	vec4 mv_position = texture(position_tex, tex_coords);
	vec3 mv_normal = texture(normal_tex, tex_coords).xyz;

	ssao_component = vec4(mv_normal.xyz, 1.0);
}
