#ifndef PASS_SHADER_PROGRAM_H
#define PASS_SHADER_PROGRAM_H

#include "BaseShaderProgram.h"
#include "FboHandler.h"

class PassShaderProgram : public BaseShaderProgram {
  public:
    PassShaderProgram(Shader* vert, Shader* frag) : BaseShaderProgram(vert, frag) { };
    ~PassShaderProgram();
    
    void update();
    void use();
    void initUniforms();
    void initBuffers(std::vector<Model*> *models = nullptr); 
    void generateRandomKernel(GLfloat* kernel, const int kSamples);


  private:
    GLuint vbo[3];
    float getRnd();
    float lerp(float start, float end, float weight);
};

#endif // PASS_SHADER_PROGRAM_H