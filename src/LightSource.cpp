#include "LightSource.h"

#include <algorithm> 

LightSource::LightSource(glm::vec3 pos, glm::vec3 col) {

	position_ = pos;

	// Light values shouldn't be > 1.0.
	float max = std::max(col.x, std::max(col.y, col.z));
	color_ = (max > 1.0) ? col / max : col;
}

LightSource::~LightSource() {

}