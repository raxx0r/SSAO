#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <string>
#include <glm/glm.hpp>

class Window {
	public:
		Window(GLint width, GLint height, std::string s);
		virtual ~Window();
		GLint getFrameBufferWidth();
    	GLint getFrameBufferHeight();
    	GLFWwindow* getWindow();
    	GLfloat getDeltaTime();
		bool isGrabbed();
   	    bool isClosed();
	    void update();
	    glm::vec2 getDeltaMousePosition();
	
	private:
		bool _grabbed;
		GLFWwindow* window;
		GLdouble _deltaTime;    
    	GLdouble _lastBufferSwapTime;
	    glm::vec2 _lastMousePos;
	    glm::vec2 _deltaMousePos;
};

#endif