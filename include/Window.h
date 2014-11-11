#include <GLFW/glfw3.h>
#include <string>

class Window {
	private:
		GLFWwindow* window;
	public:
		Window(GLint width, GLint height, std::string s);
		virtual ~Window();

		GLint getFrameBufferWidth();
    	GLint getFrameBufferHeight();
    	GLFWwindow* getWindow();
   	    bool shouldClose();
	    void swapBuffers();
};