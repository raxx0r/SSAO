#ifndef BASE_SHADER_PROGRAM_H
#define BASE_SHADER_PROGRAM_H

#include "Shader.h"
#include "Model.h"
#include "Utils.h"
#include "LightSource.h"

#include <iostream>
#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class BaseShaderProgram {
  public:
    BaseShaderProgram(Shader* vert, Shader* frag);
    virtual ~BaseShaderProgram();
    
    virtual void initUniforms() = 0;
    virtual void initBuffers(std::vector<Model*> *vec) = 0;
    virtual void initLightSource(const LightSource* lightSource) {};
    virtual void use();
    
    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void attachShader(Shader* shader);
    void link();
    
    GLuint getProgramID();
    GLint getUniformLoc(std::string name);
  protected:
    enum attribLocations {
        POSITION_LOC,
        NORMAL_LOC,
        TEXCOORD_LOC
    };

    GLuint programID;
    GLuint vao;
};


#endif // BASE_SHADER_PROGRAM_H