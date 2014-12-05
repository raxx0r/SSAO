#ifndef PHONG_SHADER_PROGRAM_H
#define PHONG_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class PhongShaderProgram : public BaseShaderProgram {

  public:
    PhongShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~PhongShaderProgram();
    
    void update(glm::mat4 modelMat, glm::mat4 viewMat);
    void initUniforms();
    void initBuffers(Model* m[] = NULL, const int AMOUNT_MODELS = 0);
    void initLightSource(const LightSource* lightSource);     

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

    // Inverted view matrix, used for specular highlights.
    glm::mat4 vInv;

    // Model matrix
    glm::mat4 M;

    // Normal matrix
    glm::mat3 N;
};

#endif // PHONG_SHADER_PROGRAM_H