#ifndef BASE_SHADER_PROGRAM_H
#define BASE_SHADER_PROGRAM_H

#include "Shader.h"
#include "Model.h"
#include "Utils.h"

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class BaseShaderProgram {
  protected:

    GLuint programID;
    GLuint vao;
    
  public:
    BaseShaderProgram(Shader* vert, Shader* frag);
    virtual ~BaseShaderProgram();
    
    void update(glm::mat4 modelMat, glm::mat4 viewMat);
    void initUniforms() {};
    void initBuffers(Model* m[] = NULL, const int AMOUNT_MODELS = 0);
    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void attachShader(Shader* shader);
    void link();
    void use();
    
    GLuint getProgramID();
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);
};


#endif // BASE_SHADER_PROGRAM_H