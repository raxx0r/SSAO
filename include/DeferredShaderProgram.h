#ifndef DEFERRED_SHADER_PROGRAM_H
#define DEFERRED_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class DeferredShaderProgram : public BaseShaderProgram {

  public:
    DeferredShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~DeferredShaderProgram();
    
    void update(glm::mat4 modelMat, glm::mat4 viewMat);
    void use();
    void initUniforms();
    void initBuffers(std::vector<Model*> *models = nullptr);
  private:
    enum vboIndices {
        POSITION_VBO,
        NORMAL_VBO
    };
    
    GLuint vbo[2];
    
    // Buffer offset
    long offset;
    
    // Perspective matrix
    glm::mat4 P;

    // View matrix
    glm::mat4 V;

    // Model matrix
    glm::mat4 M;

    // Normal matrix
    glm::mat3 N;
};

#endif // DEFERRED_SHADER_PROGRAM_H