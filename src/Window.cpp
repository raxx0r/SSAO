#include "Window.h"
#include <iostream>




Window::Window(GLint width, GLint height, std::string s){

    // Initialize the library. 
    if (!glfwInit()){
    	std::cout << "Could not initialize GLFW" << std::endl;
    }

    // Use GLSL 3.2 or higher.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context.
    window = glfwCreateWindow(width, height, s.c_str(), NULL, NULL);
    if (!window) {
    	std::cout << "Could not glfwCreateWindow" << std::endl;
        glfwTerminate();
    }

    // Make the window's context current.
    glfwMakeContextCurrent(window);

}

Window::~Window(){

    glfwDestroyWindow(window);

}

void Window::swapBuffers(){

    glfwSwapBuffers(window);

}

bool Window::isClosed(){
    return glfwWindowShouldClose(window);
}



GLint Window::getFrameBufferWidth(){
    GLint width;
    glfwGetFramebufferSize(window, &width, NULL);
    return width;
}

GLint Window::getFrameBufferHeight(){
    GLint height;
    glfwGetFramebufferSize(window, NULL, &height);
    return height;
}

GLFWwindow* Window::getWindow(){
    return window;
}