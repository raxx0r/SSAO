#include "SSAOShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SSAOShaderProgram::~SSAOShaderProgram() {
    BaseShaderProgram::~BaseShaderProgram();
    glDeleteBuffers(1, &vbo);
}

void SSAOShaderProgram::update() { 
    // TODO
}

void SSAOShaderProgram::initUniforms() {

}

// Init buffers for rendering. 
void SSAOShaderProgram::initBuffers(Model* m[], const int AMOUNT_MODELS) {

    // Initialize vbo
    glGenBuffers(1, &vbo);   
    
    // Give specified size to position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float quad[] = {
        -1.0, -1.0, 0.0,
         1.0, -1.0, 0.0,
         1.0, 1.0, 0.0,
        -1.0, 1.0, 0.0,
    };
  
    // Position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * 4, quad, GL_STATIC_DRAW);

    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(POSITION_LOC);
}