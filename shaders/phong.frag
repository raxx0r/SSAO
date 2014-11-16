#version 330 core

in vec3 t_normal;
in vec4 m_position;

out vec4 out_color;

// Lightning position in Model coordinates.
uniform vec3 light_pos;

uniform vec3 light_col;
uniform mat4 V;
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
	vec3 mv_normal = normalize(t_normal);
	vec4 mv_position = V * m_position;

	// Light direction in view coordinates.
	vec4 v_light_position = V * vec4(light_pos, 1.0);

	// Camera position in model coordinates.
	vec4 camera_position = V_inv * vec4(0.0, 0.0, 0.0, 1.0);

	// Direction from frag to camera.
	vec3 view_direction = normalize(vec3(camera_position - m_position));

	// Gets the light direction 
	vec3 pos_to_light = vec3(v_light_position - mv_position);
	float distance = length(pos_to_light);
	vec3 v_light_direction = normalize(pos_to_light);

	// Calculates attenuation which makes frags far
	float attenuation = 1.0 / (att.constant + att.linear * distance +
						att.quadratic * distance * distance);
	// Diffuse part
	diffuse = attenuation * light_col * max(0.0, dot(mv_normal, v_light_direction));

	// Specular == 0 if light comes from wrong direction.
	if (dot(mv_normal, v_light_direction) < 0.0) {
		specular = vec3(0.0);
	} else {
		vec3 v_view_direction = normalize(vec3(V * vec4(view_direction, 0.0)));
		specular = attenuation * light_col * pow(max(0.0, dot(normalize(reflect(-v_light_direction, mv_normal)), v_view_direction)), 20.0f);
	}

	out_color = vec4(diffuse + specular, 1.0);
}