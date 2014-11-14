#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>
#include "Window.h"

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
