#include "Camera.h"



Camera::Camera(){

    _position = glm::vec3(0.0, 0.0, 0.0);
    _rotation = glm::vec3(0.0, 0.0, 0.0);
    _moveSpeed = 20.0;
    _rotateSpeed = 5.0;
}
void Camera::setPosition(glm::vec3 position){
    _position = position;
}

void Camera::setRotation(glm::vec3 rotation){
    _rotation = rotation;
}

void Camera::setMoveSpeed(GLfloat moveSpeed){
    _moveSpeed = moveSpeed;
}

void Camera::setRotateSpeed(GLfloat rotateSpeed){
    _rotateSpeed = rotateSpeed;
}

glm::mat4 Camera::getMatrix(){
    glm::mat4 matrix = glm::mat4();

    matrix = glm::rotate(matrix, -_rotation.x, glm::vec3(1,0,0));
    matrix = glm::rotate(matrix, -_rotation.y, glm::vec3(0,1,0));
    matrix = glm::rotate(matrix, -_rotation.z, glm::vec3(0,0,1));
    
    matrix = glm::translate(matrix, -_position);
    
    return matrix;
}


void Camera::getUserInput(Window* window){
    GLFWwindow* glfwWindow = window->getWindow();
    GLfloat deltaTime = window->getDeltaTime();
    
    /*
    if(window->isGrabbed()){
        glm::vec2 deltaMousePosition = window->getDeltaMousePosition();
        _rotation.y += deltaMousePosition.x * _rotateSpeed*deltaTime;
        _rotation.x += deltaMousePosition.y * _rotateSpeed*deltaTime;

    }
    */
            
    if(glfwGetKey(glfwWindow, GLFW_KEY_W)){
        _position.x -= _moveSpeed * sinf((_rotation.y)*(M_PI /180.0)) * deltaTime;
        _position.z -= _moveSpeed * cosf((_rotation.y)*(M_PI /180.0)) * deltaTime;
    }
    
    if(glfwGetKey(glfwWindow, GLFW_KEY_S)){
        _position.x -= _moveSpeed * sinf((_rotation.y + 180.0)*(M_PI /180.0)) * deltaTime;
        _position.z -= _moveSpeed * cosf((_rotation.y + 180.0)*(M_PI /180.0)) * deltaTime;
    }

    if(glfwGetKey(glfwWindow, GLFW_KEY_A)){
        _position.x -= _moveSpeed * sinf((_rotation.y + 90.0)*(M_PI /180.0)) * deltaTime;
        _position.z -= _moveSpeed * cosf((_rotation.y + 90.0)*(M_PI /180.0)) * deltaTime;
    }

    if(glfwGetKey(glfwWindow, GLFW_KEY_D)){
        _position.x -= _moveSpeed * sinf((_rotation.y + 270.0)*(M_PI /180.0)) * deltaTime;
        _position.z -= _moveSpeed * cosf((_rotation.y + 270.0)*(M_PI /180.0)) * deltaTime;
    }
    
    if(glfwGetKey(glfwWindow, GLFW_KEY_SPACE)){
        _position.y += _moveSpeed * deltaTime;
    }
    
    if(glfwGetKey(glfwWindow, GLFW_KEY_LEFT_SHIFT)){
        _position.y -= _moveSpeed * deltaTime;
    }
}

