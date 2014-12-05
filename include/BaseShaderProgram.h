#ifndef BASE_SHADER_PROGRAM_H
#define BASE_SHADER_PROGRAM_H

#include "Shader.h"
#include "Model.h"
#include "Utils.h"
#include "LightSource.h"

#include <iostream>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class BaseShaderProgram {

  public:
    BaseShaderProgram(Shader* vert, Shader* frag);
    virtual ~BaseShaderProgram();
    
    virtual void initUniforms() = 0;
    virtual void initBuffers(Model* m[], const int AMOUNT_MODELS) = 0;
    virtual void initLightSource(const LightSource* lightSource) {};

    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void attachShader(Shader* shader);
    void link();
    void use();
    
    GLuint getProgramID();
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);

  protected:
    enum attribLocations {
        POSITION_LOC,
        NORMAL_LOC
    };

    GLuint programID;
    GLuint vao;
};


#endif // BASE_SHADER_PROGRAM_H