#version 330 core

in vec3 t_normal;
in vec4 m_position;

out vec4 out_color;

uniform vec3 light_pos;
uniform vec3 light_col;
uniform mat4 V_inv;

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

// Diffuse lightning part
vec3 diffuse;

// Specular lightning part
vec3 specular;

void main() {

	// These values might need to be tweaked but I'll leave
	// them like this for now.
	Attenuation att = Attenuation(0.7, 0.05, 0.01);

	vec3 normal = normalize(t_normal);

	// Gets the direction from camera to frag position in model coordinates.
	vec3 view_direction = normalize(vec3((V_inv * vec4(0.0, 0.0, 0.0, 1.0)) - m_position));

	// Gets the light direction 
	vec3 pos_to_light = light_pos - m_position.xyz;
	float distance = length(pos_to_light);
	vec3 light_direction = normalize(pos_to_light);

	// Calculates attenuation which make lights far away lighten fragments with less intensity.
	float attenuation = 1.0 / (att.constant + att.linear * distance +
						att.quadratic * distance * distance);
	attenuation = 1.0;
	// Diffuse part
	diffuse = attenuation * light_col * max(0.0, dot(normal, light_direction));

	// Specular == 0 if light comes from wrong direction.
	if (dot(normal, light_direction) < 0.0) {
		specular = vec3(0.0);
	} else {
		specular = attenuation * vec3(1.0) * pow(max(0.0, dot(reflect(-light_direction, normal), view_direction)), 25.0f);
	}

	out_color = vec4(diffuse + specular, 1.0);
}