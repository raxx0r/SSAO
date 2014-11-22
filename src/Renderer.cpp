#include "Renderer.h"
#include "Utils.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glEnable(GL_DEPTH_TEST);

    // Don't draw triangles with faces away from camera.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glGenBuffers(2, vbo);
    offset = 0;
}

void Renderer::update(glm::mat4 modelMat, glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint mLoc = shaderProgram->getUniformLoc("M");
    GLuint vLoc = shaderProgram->getUniformLoc("V");
    GLuint nLoc = shaderProgram->getUniformLoc("N");
    GLuint vInvLoc = shaderProgram->getUniformLoc("V_inv");

    N = glm::transpose(glm::inverse(glm::mat3(viewMat * modelMat)));
    vInv = glm::inverse(viewMat);

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));

}

void Renderer::initLightSource(const LightSource& lightSource) {
    GLuint lightPosLoc = shaderProgram->getUniformLoc("light_pos");
    GLuint lightColLoc = shaderProgram->getUniformLoc("light_col");

    glUniform4fv(lightPosLoc, 1, glm::value_ptr(lightSource.position()));
    glUniform3fv(lightColLoc, 1, glm::value_ptr(lightSource.color()));
}


// Attach two shaders and links them together, returns a pointer to the program.
ShaderProgram* Renderer::buildShaderProgram(Shader* vert, Shader* frag) {
    shaderProgram = new ShaderProgram();
    shaderProgram->attachShader(vert);
    shaderProgram->attachShader(frag);
    shaderProgram->bindFragDataLocation(0, "out_color");
    shaderProgram->link();

    return shaderProgram;
}

// Init buffers for rendering. 
void Renderer::initBuffers(Model* m[], const int AMOUNT_MODELS) {
    
    long bufferSize = 0;
    GLuint posLoc = shaderProgram->getAttribLoc("position");
    GLuint normLoc = shaderProgram->getAttribLoc("normal");    
    // Calculate the buffer size
    for(int i = 0; i < AMOUNT_MODELS; i++) {
      bufferSize += 3.0 * sizeof(float) * m[i]->numVertices;
    }
    
    // Give specified size to position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    // Give specified size to normal budder
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    for(int i = 0; i < AMOUNT_MODELS; i++) {
      long size = 3.0 * sizeof(float) * m[i]->numVertices;
      
      // Position buffer
      glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
      glBufferSubData(GL_ARRAY_BUFFER, offset, size, m[i]->vertices);
      
      glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
      glEnableVertexAttribArray(posLoc);
      
      // Normal buffer
      glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
      glBufferSubData(GL_ARRAY_BUFFER, offset ,size ,m[i]->normals);
      
      glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
      glEnableVertexAttribArray(normLoc);
      
      m[i]->setOffset(offset/(3.0 * sizeof(float)));
      
      offset += 3.0 * sizeof(float) * m[i]->numVertices;
    }
      
    // Set attribute pointer to first object
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posLoc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normLoc);
}

void Renderer::useProgram(ShaderProgram* program) {
    program->use();
}

void Renderer::initUniforms() {

	float aspect = (float) 800 / 600;

    // Init matrices
    M = glm::mat4();
    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    P = glm::perspective(Utils::degToRad(60.0f), aspect, 0.1f, 200.0f);
    N = glm::transpose(glm::inverse(glm::mat3(V * M)));
    vInv = glm::inverse(V);

    // Find GPU locations
    GLuint mLoc = shaderProgram->getUniformLoc("M");
    GLuint vLoc = shaderProgram->getUniformLoc("V");
    GLuint pLoc = shaderProgram->getUniformLoc("P");
    GLuint nLoc = shaderProgram->getUniformLoc("N");
    GLuint vInvLoc = shaderProgram->getUniformLoc("V_inv");

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}

   
Renderer::~Renderer() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
    delete shaderProgram;
}