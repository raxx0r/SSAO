#include "PassThroughShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PassThroughShaderProgram::~PassThroughShaderProgram() {
    BaseShaderProgram::~BaseShaderProgram();
    glDeleteBuffers(1, &vbo);
}

void PassThroughShaderProgram::update() { 
    // TODO
}

void PassThroughShaderProgram::initUniforms() {

}

// Init buffers for rendering. 
void PassThroughShaderProgram::initBuffers(Model* m[], const int AMOUNT_MODELS) {

    // Initialize vbo
    glGenBuffers(1, &vbo);
    
    GLuint posLoc = getAttribLoc("position");   
    
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

    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(posLoc);
}