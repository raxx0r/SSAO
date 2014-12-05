#ifndef SSAO_SHADER_PROGRAM_H
#define SSAO_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class SSAOShaderProgram : public BaseShaderProgram {
  public:
    SSAOShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~SSAOShaderProgram();
    
    void update();
    void use();
    void initUniforms();
    void initBuffers(Model* m[] = NULL, const int AMOUNT_MODELS = 0); 

  private:
    GLuint vbo;
    GLuint ebo;
};

#endif // SSAO_SHADER_PROGRAM_H