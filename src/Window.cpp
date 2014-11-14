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

GLfloat Window::getDeltaTime(){
    return _deltaTime;
}

void Window::update(){

    // Get user input and swap buffers
    glfwPollEvents();
    glfwSwapBuffers(window);
    
    // Calculate _deltaTime
    GLdouble currentTime = glfwGetTime();
    _deltaTime = currentTime - _lastBufferSwapTime;
    _lastBufferSwapTime = currentTime;

    // Mouse update
    if(!_grabbed &&glfwGetMouseButton(window, 0)){
        _grabbed = true;
        GLdouble x, y;
        glfwGetCursorPos(window, &x, &y);
        _lastMousePos = glm::vec2(-x,-y);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    if(_grabbed && glfwGetKey(window, GLFW_KEY_ESCAPE)){
        _grabbed = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    GLdouble x,y;
    glfwGetCursorPos(window, &x, &y);
    glm::vec2 currentMosPos = glm::vec2(-x,-y);
    _deltaMousePos = currentMosPos - _lastMousePos;
    _lastMousePos= currentMosPos;

}

bool Window::isClosed(){
    return glfwWindowShouldClose(window);
}

bool Window::isGrabbed(){
    return _grabbed;
}

glm::vec2 Window::getDeltaMousePosition(){
    return _deltaMousePos;
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