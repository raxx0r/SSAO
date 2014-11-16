#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glm/glm.hpp>

// TODO: Refactor to struct?
class LightSource {

  private:
  	glm::vec3 position_;
  	glm::vec3 color_;

  public:
	LightSource(glm::vec3 pos, glm::vec3 col);

    glm::vec3 position() { return position_; }
    glm::vec3 color() { return color_; }

    virtual ~LightSource();
};

#endif