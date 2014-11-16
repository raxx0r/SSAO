#ifndef CAMERA_H
#define CAMERA_H

#include "Window.h"

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#define GLM_FORCE_RADIANS

class Camera {
	public:
	  Camera();
	  void setPosition(glm::vec3 position);
	  void setRotation(glm::vec3 rotation);
	  void setMoveSpeed(GLfloat moveSpeed);
	  void setRotateSpeed(GLfloat rotateSpeed);
	  void update(Window* window);
	  glm::mat4 getMatrix();
	private:
	  glm::vec3 _position;
	  glm::vec3 _rotation;
	  GLfloat _moveSpeed;
	  GLfloat _rotateSpeed;
};

#endif 