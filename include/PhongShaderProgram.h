#ifndef PHONG_SHADER_PROGRAM_H
#define PHONG_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class PhongShaderProgram : public BaseShaderProgram {

  public:
    PhongShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~PhongShaderProgram();
    
    void update(glm::mat4 viewMat);
    void use();
    void initUniforms();
    void initBuffers(std::vector<Model*> *models = nullptr);
    void initLightSource(const LightSource* lightSource);  
    void setSSAO(int ssao);   

  private:
    
    GLuint vbo[3];
    
    // Inverted view matrix, used for specular highlights.
    glm::mat4 vInv;
    
    glm::mat4 V;

    glm::vec4 lightDirection;
    GLuint ssao_;

};

#endif // PHONG_SHADER_PROGRAM_H