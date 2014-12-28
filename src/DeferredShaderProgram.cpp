#include "DeferredShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

DeferredShaderProgram::~DeferredShaderProgram() {
    glDeleteBuffers(2, vbo);
}

void DeferredShaderProgram::use() {
    BaseShaderProgram::use();
    glEnable(GL_DEPTH_TEST);

    // Don't draw triangles with faces away from camera.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void DeferredShaderProgram::update(glm::mat4 modelMat, glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint nLoc = getUniformLoc("N");

    N = glm::transpose(glm::inverse(glm::mat3(viewMat * modelMat)));

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}


void DeferredShaderProgram::initUniforms() {

    glBindVertexArray(vao);
    float aspect = (float) 800 / 600;

    // Init matrices
    M = glm::mat4();
    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    P = glm::perspective(Utils::degToRad(60.0f), aspect, 0.1f, 200.0f);
    N = glm::transpose(glm::inverse(glm::mat3(V * M)));


    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint pLoc = getUniformLoc("P");
    GLuint nLoc = getUniformLoc("N");


    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));

    // glBindVertexArray(0);
}

// Init buffers for rendering. 
void DeferredShaderProgram::initBuffers(std::vector<Model*> *models) {

    if (models == nullptr) {
        std::cerr << "ERROR: No model used in initBuffers for Phong shader." << std::endl;
        return;
    }

    glBindVertexArray(vao);

    // Initialize vbo
    glGenBuffers(2, vbo);
    offset = 0;
    
    long bufferSize = 0; 

    for (auto &m : *models) {
        bufferSize += 3.0 * sizeof(float) * m->numVertices;
    }
    
    // Give specified size to position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, nullptr, GL_STATIC_DRAW);
    
    // Give specified size to normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, nullptr, GL_STATIC_DRAW);
    
     for (auto &m : *models) {
        long size = 3.0 * sizeof(float) * m->numVertices;
      
        // Position buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m->vertices);
      
        glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(POSITION_LOC);
      
        // Normal buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m->normals);
      
        glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(NORMAL_LOC);
      
        m->setOffset(offset / (3.0 * sizeof(float)));
      
        offset += 3.0 * sizeof(float) * m->numVertices;
    }
      
    // Set attribute pointer to first object
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glVertexAttribPointer(POSITION_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(POSITION_LOC);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glVertexAttribPointer(NORMAL_LOC, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(NORMAL_LOC);
}
