#ifndef CAMERA_H
#define CAMERA_H

#include "Shader.h"

#include "Window.h"
#include <GLFW/glfw3.h>
#include "PhongShaderProgram.h"


class Camera {
	public:
	  Camera();
	  void setPosition(glm::vec3 position);
	  void setRotation(glm::vec3 rotation);
	  void setMoveSpeed(GLfloat moveSpeed);
	  void setRotateSpeed(GLfloat rotateSpeed);
	  void attachPhongProgram(PhongShaderProgram* phongProgram);
	  void update(Window &window);
	  static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	  glm::mat4 getMatrix();
	  static bool ssao;

	private:
	  glm::vec3 _position;
	  glm::vec3 _rotation;
	  GLfloat _moveSpeed;
	  GLfloat _rotateSpeed;
	  
	  PhongShaderProgram* _phongProgram;
};

#endif // CAMERA_H