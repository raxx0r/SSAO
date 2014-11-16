#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Utils.h"

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
void Camera::update(Window* window){
    // Calculate delaTime
    GLFWwindow* glfwWindow = window->getWindow();
    GLfloat deltaTime = window->getDeltaTime();
    
    // Calculate the rotation while moving the mouse
    if(window->isGrabbed()){
        glm::vec2 deltaMousePosition = window->getDeltaMousePosition();
        _rotation.y += deltaMousePosition.x * _rotateSpeed*deltaTime;
        _rotation.x += deltaMousePosition.y * _rotateSpeed*deltaTime;
    }          
    
    // Calculate the new position if specified key is pressed
    if(glfwGetKey(glfwWindow, GLFW_KEY_A)){
        _position.x -= _moveSpeed * sinf(Utils::degToRad(_rotation.y + 90.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(Utils::degToRad(_rotation.y + 90.0f)) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_W)){
        _position.y += _moveSpeed * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_S)){
        _position.y -= _moveSpeed * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_D)){
        _position.x -= _moveSpeed * sinf(Utils::degToRad(_rotation.y + 270.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(Utils::degToRad(_rotation.y + 270.0f)) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT)){
        _position.x -= _moveSpeed * sinf(Utils::degToRad(_rotation.y)) * deltaTime;
        _position.z -= _moveSpeed * cosf(Utils::degToRad(_rotation.y)) * deltaTime;
    }
    if(glfwGetKey(glfwWindow, GLFW_KEY_SPACE)){
        _position.x -= _moveSpeed * sinf(Utils::degToRad(_rotation.y + 180.0f)) * deltaTime;
        _position.z -= _moveSpeed * cosf(Utils::degToRad(_rotation.y + 180.0f)) * deltaTime;
    }
}
