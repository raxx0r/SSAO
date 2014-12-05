#ifndef PASS_THROUGH_SHADER_PROGRAM_H
#define PASS_THROUGH_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"

class PassThroughShaderProgram : public BaseShaderProgram {
private:
    
    GLuint vbo;

public:
    PassThroughShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) {};
    ~PassThroughShaderProgram();
    
    void update();
    void initUniforms();
    void initBuffers(Model* m[], const int AMOUNT_MODELS);    
};

#endif // PASS_THROUGH_SHADER_PROGRAM_H