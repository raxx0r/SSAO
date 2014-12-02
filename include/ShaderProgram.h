#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include "Shader.h"
#include "Model.h"
#include "Utils.h"

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
private:
    GLuint programID;
    
    enum vboIndices {
	POSITION_VBO,
	NORMAL_VBO
    };
    
    GLuint vao;
    GLuint vbo[2];
    
    // Buffer offset
    long offset;
    
    // Perspective matrix
    glm::mat4 P;

    // View matrix
    glm::mat4 V;

    // Inverted view matrix, used for specular highlights.
    glm::mat4 vInv;

    // Model matrix
    glm::mat4 M;

    // Normal matrix
    glm::mat3 N;
public:
    ShaderProgram(Shader* vert, Shader* frag);
    virtual ~ShaderProgram();
    
    void update(glm::mat4 modelMat, glm::mat4 viewMat);
    void initUniforms();
    void initBuffers(Model* m[], const int AMOUNT_MODELS);
    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void attachShader(Shader* shader);
    void link();
    void use();
    
    GLuint getProgramID();
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);


    
};

#endif