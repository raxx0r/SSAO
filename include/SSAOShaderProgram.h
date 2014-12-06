#ifndef SSAO_SHADER_PROGRAM_H
#define SSAO_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"
#include "FboHandler.h"

class SSAOShaderProgram : public BaseShaderProgram {
  public:
    SSAOShaderProgram(Shader* vert, Shader* frag,  FBOstruct* fbo1) : BaseShaderProgram(vert, frag), fbo(fbo1) { };
    ~SSAOShaderProgram();
    
    void update();
    void use();
    void initUniforms();
    void initBuffers(std::vector<Model*> *models = nullptr); 

  private:
    GLuint vbo[3];
    FBOstruct* fbo;
};

#endif // SSAO_SHADER_PROGRAM_H