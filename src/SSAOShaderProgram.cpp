#include "SSAOShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

SSAOShaderProgram::~SSAOShaderProgram() {
    glDeleteBuffers(3, vbo);
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
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, fbo->tex);
    glUniform1i(getUniformLoc("tex"), 0);
}

// Init buffers for rendering. 
void SSAOShaderProgram::initBuffers(std::vector<Model*> *vec) {

    glBindVertexArray(vao);

    // Initialize vbo
    glGenBuffers(3, vbo);   
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    float vertices[] = {
        -1.0f,  1.0f, 0.0,
        -1.0f, -1.0f, 0.0,
         1.0f, -1.0f, 0.0,
         1.0f, 1.0f, 0.0
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(POSITION_LOC);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    
    float texCoords[]  = {
    	0.0f, 1.0f,
    	0.0f, 0.0f,
    	1.0f, 0.0f,
    	1.0f, 1.0f,
    };
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);

    glVertexAttribPointer(TEXCOORD_LOC, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(TEXCOORD_LOC);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[2]);

    GLuint elements[] = {
        0, 1, 3, 3, 1, 2
    };

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
}