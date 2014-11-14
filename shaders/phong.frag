#version 330 core

in vec3 t_normal;
out vec4 outColor;

void main() {
	const vec3 light = vec3(0.58, 0.58, 0.58);

	float diffuse = dot(normalize(t_normal), light);
	diffuse = max(0.0, diffuse); 

	outColor = vec4(vec3(diffuse), 1.0);
}