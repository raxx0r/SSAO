#version 330 core

in vec3 t_normal;
in vec4 m_position;

uniform vec4 light_pos;

uniform vec3 light_col;
uniform mat4 V;
uniform mat4 V_inv;

layout (location = 0) out vec4 out_color;
layout (location = 1) out vec3 out_normal;
layout (location = 2) out vec4 out_position;

struct Attenuation {
	float constant;
	float linear;
	float quadratic;
};

void main() {

	vec3 v_light_direction;
	vec3 specular;
	vec3 diffuse;

	// Gradual loss of intensity.
	float attenuation; 

	// These values might need to be tweaked but I'll leave
	// them like this for now.
	Attenuation att = Attenuation(0.7, 0.05, 0.01);
	vec3 mv_normal = normalize(t_normal);
	vec4 mv_position = V * m_position;

	// Light direction in view coordinates.
	vec4 v_light_position = V * light_pos;

	// Camera position in model coordinates.
	vec4 camera_position = V_inv * vec4(0.0, 0.0, 0.0, 1.0);

	// Direction from frag to camera.
	vec3 view_direction = normalize(vec3(camera_position - m_position));

	// w == 0 means directional light.
	if (light_pos.w == 0) { 
		v_light_direction = normalize(vec3(v_light_position));
		attenuation = 1.0;
	} else { 
		// Calculate distance from source.
		vec3 pos_to_light = vec3(v_light_position - mv_position);
		float distance = length(pos_to_light);
		v_light_direction = normalize(pos_to_light);

		// Calculates attenuation which makes frags far away from light source appear darker.
		attenuation = 1.0 / (att.constant + att.linear * distance +
					   att.quadratic * distance * distance);
	}

	diffuse = attenuation * light_col * max(0.0, dot(mv_normal, v_light_direction));

	// Specular == 0 if light comes from wrong direction.
	if (dot(mv_normal, v_light_direction) < 0.0) {
		specular = vec3(0.0);
	} else {
		vec3 v_view_direction = normalize(vec3(V * vec4(view_direction, 0.0)));
		specular = attenuation * light_col * pow(max(0.0, dot(normalize(reflect(-v_light_direction, mv_normal)), v_view_direction)), 20.0f);
	}

	out_color = vec4(diffuse + specular, 1.0);
	out_normal = mv_normal;
	out_position = mv_position;
}