#ifndef SSAO_SHADER_PROGRAM_H
#define SSAO_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class SSAOShaderProgram : public BaseShaderProgram {
  public:
    SSAOShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~SSAOShaderProgram();
    
    void update();
    void initUniforms();
    void initBuffers(Model* m[], const int AMOUNT_MODELS); 

  private:
    GLuint vbo;
};

#endif // SSAO_SHADER_PROGRAM_H