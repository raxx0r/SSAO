#include "PhongShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PhongShaderProgram::~PhongShaderProgram() {
    BaseShaderProgram::~BaseShaderProgram();
    glDeleteBuffers(2, vbo);
}

void PhongShaderProgram::update(glm::mat4 modelMat, glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint nLoc = getUniformLoc("N");
    GLuint vInvLoc = getUniformLoc("V_inv");

    N = glm::transpose(glm::inverse(glm::mat3(viewMat * modelMat)));
    vInv = glm::inverse(viewMat);

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}

void PhongShaderProgram::initLightSource(const LightSource* lightSource) {
    GLuint lightPosLoc = getUniformLoc("light_pos");
    GLuint lightColLoc = getUniformLoc("light_col");

    glUniform4fv(lightPosLoc, 1, glm::value_ptr(lightSource->position()));
    glUniform3fv(lightColLoc, 1, glm::value_ptr(lightSource->color()));
}

void PhongShaderProgram::initUniforms() {

    float aspect = (float) 800 / 600;

    // Init matrices
    M = glm::mat4();
    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    P = glm::perspective(Utils::degToRad(60.0f), aspect, 0.1f, 200.0f);
    N = glm::transpose(glm::inverse(glm::mat3(V * M)));
    vInv = glm::inverse(V);

    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint pLoc = getUniformLoc("P");
    GLuint nLoc = getUniformLoc("N");
    GLuint vInvLoc = getUniformLoc("V_inv");

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}

// Init buffers for rendering. 
void PhongShaderProgram::initBuffers(Model* m[], const int AMOUNT_MODELS) {

    // Initialize vbo
    glGenBuffers(2, vbo);
    offset = 0;
    
    long bufferSize = 0; 

    // Calculate the buffer size
    for(int i = 0; i < AMOUNT_MODELS; i++) {
        bufferSize += 3.0 * sizeof(float) * m[i]->numVertices;
    }
    
    // Give specified size to position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    // Give specified size to normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    for(int i = 0; i < AMOUNT_MODELS; i++) {
        long size = 3.0 * sizeof(float) * m[i]->numVertices;
      
        // Position buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m[i]->vertices);
      
        glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(POSITION_LOC);
      
        // Normal buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m[i]->normals);
      
        glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(NORMAL_LOC);
      
        m[i]->setOffset(offset / (3.0 * sizeof(float)));
      
        offset += 3.0 * sizeof(float) * m[i]->numVertices;
    }
      
    // Set attribute pointer to first object
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(POSITION_LOC);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(NORMAL_LOC);
}