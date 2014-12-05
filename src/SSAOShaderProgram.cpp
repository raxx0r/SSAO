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

    glBindVertexArray(vao);
    glBindVertexArray(0);
}

void SSAOShaderProgram::use() {
    BaseShaderProgram::use();
    glDisable(GL_DEPTH_TEST);

    // Don't draw triangles with faces away from camera.
    glDisable(GL_CULL_FACE);
}

// Init buffers for rendering. 
void SSAOShaderProgram::initBuffers(Model* m[], const int AMOUNT_MODELS) {

    glBindVertexArray(vao);

    // Initialize vbo
    glGenBuffers(1, &vbo);   
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[] = {
        -0.5f,  0.5f, 0.0,
        -0.5f, -0.5f, 0.0,
         0.5f, -0.5f, 0.0,
         0.5f, 0.5f, 0.0
    };
  
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(POSITION_LOC);

    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    GLuint elements[] = {
        0, 1, 3, 3, 1, 2
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
    glBindVertexArray(0);
}