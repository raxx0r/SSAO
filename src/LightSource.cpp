#include "LightSource.h"

#include <algorithm> 

LightSource::LightSource(glm::vec4 pos, glm::vec3 col) {

	position_ = pos;

	// Light values shouldn't be > 1.0.
	float max = std::max(col.x, std::max(col.y, col.z));
	color_ = (max > 1.0) ? col / max : col;
}

LightSource LightSource::PointLightSource(glm::vec3 dir, glm::vec3 col) {
	return LightSource(glm::vec4(dir, 1.0), col);
}

LightSource LightSource::DirectionalLightSource(glm::vec3 dir, glm::vec3 col) {
	return LightSource(glm::vec4(dir, 0.0), col);
}

LightSource::~LightSource() {

}