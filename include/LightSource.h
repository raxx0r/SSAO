#ifndef LIGHT_SOURCE_H
#define LIGHT_SOURCE_H

#include <glm/glm.hpp>

/// Represents the lightsource to be rendered to the scene.
/// It is possible to create both point- and directional lights by using
/// the factory methods provided. The position parameter for a directional light
/// is simply the direction of the light.
class LightSource {

  private:
  	glm::vec4 position_;
  	glm::vec3 color_;
    LightSource(glm::vec4 pos, glm::vec3 col);

  public:
    static LightSource PointLightSource(glm::vec3 dir, glm::vec3 col);
    static LightSource DirectionalLightSource(glm::vec3 dir, glm::vec3 col);
    glm::vec4 position() const { return position_; }
    glm::vec3 color() const { return color_; }

    virtual ~LightSource();
};

#endif // LIGHT_SOURCE_H