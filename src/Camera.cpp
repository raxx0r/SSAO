#include "Camera.h"
#include "Utils.h"
#include <stdio.h>

#include <glm/gtc/matrix_transform.hpp>

// Camera Constructor
// Intializing position, rotation, movement speed and rotation speed of camera
Camera::Camera(){
    _position = glm::vec3(0.0f, 20.0f, 50.0f);
    _rotation = glm::vec3(Utils::degToRad(-10.0f), 0.0f, 0.0f);
    _moveSpeed = 20.0f;
    _rotateSpeed = Utils::degToRad(5.0f);
}

// Set camera position
void Camera::setPosition(glm::vec3 position){
    _position = position;
}

void Camera::attachPhongProgram(PhongShaderProgram* phongProgram) {
    _phongProgram= phongProgram;
}

// Set camera roation
void Camera::setRotation(glm::vec3 rotation){
    _rotation = rotation;
}

// Set camera movement speed
void Camera::setMoveSpeed(GLfloat moveSpeed){
    _moveSpeed = moveSpeed;
}

// Set camera roation speed
void Camera::setRotateSpeed(GLfloat rotateSpeed){
    _rotateSpeed = rotateSpeed;
}

// Get the new position of the camera after it has been moved
glm::mat4 Camera::getMatrix(){
    glm::mat4 matrix = glm::mat4();

    matrix = glm::rotate(matrix, -_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
    matrix = glm::rotate(matrix, -_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
    matrix = glm::rotate(matrix, -_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
    
    matrix = glm::translate(matrix, -_position);
    
    return matrix;
}


// Camera update function
void Camera::update(Window& window){
    glfwPollEvents();
    
    GLFWwindow* glfwWindow = window.getWindow();
    GLfloat deltaTime = window.getDeltaTime();
    
    // Calculate the rotation while moving the mouse
    if(window.isGrabbed()){
        glm::vec2 deltaMousePosition = window.getDeltaMousePosition();
        _rotation.y += deltaMousePosition.x * _rotateSpeed*deltaTime;
        _rotation.x += deltaMousePosition.y * _rotateSpeed*deltaTime;
    }          

    // Calculate the new position if specified key is pressed
    if(glfwGetKey(window.getWindow(), GLFW_KEY_I)){
	   _phongProgram->setSSAO(1);
    }
    if(glfwGetKey(window.getWindow(), GLFW_KEY_O)){
	   _phongProgram->setSSAO(0);
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_A)){
        _position.x -= _moveSpeed * sinf(_rotation.y + Utils::degToRad(90.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(_rotation.y + Utils::degToRad(90.0f)) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_W)){
        _position.y += _moveSpeed * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_S)){
        _position.y -= _moveSpeed * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_D)){
        _position.x -= _moveSpeed * sinf(_rotation.y + Utils::degToRad(270.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(_rotation.y + Utils::degToRad(270.0f)) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT)){
        _position.x -= _moveSpeed * sinf(_rotation.y) * deltaTime;
        _position.z -= _moveSpeed * cosf(_rotation.y) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_SPACE)){
        _position.x -= _moveSpeed * sinf(_rotation.y + Utils::degToRad(180.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(_rotation.y + Utils::degToRad(180.0f)) * deltaTime;
    }
}
