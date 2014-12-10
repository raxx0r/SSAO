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

    const int kSamples = 15;
    GLfloat kernel[3 * kSamples];
    generateRandomKernel(kernel, kSamples);

    glUniform3fv(getUniformLoc("kernel"), kSamples, kernel);

    for (int i = 0; i < kSamples * 3; ++i) {
        printf("%f\n", kernel[i]);
    }

    // TODO: Put P in BaseShaderProgram.h so we won't have to do this here AND in DeferredShaderProgram.cpp
    float aspect = (float) 800 / 600;
    glm::mat4 P = glm::perspective(Utils::degToRad(60.0f), aspect, 0.1f, 200.0f);
    GLuint pLoc = getUniformLoc("P");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));

    glBindVertexArray(0);
}

void SSAOShaderProgram::generateRandomKernel(GLfloat* kernel, const int kSamples) {
    
    for (int i = 0; i < 3 * kSamples; i += 3) {
        glm::vec3 vec(getRnd(), getRnd(), (getRnd() + 1) / 2.0);
        vec = glm::normalize(vec);
        vec *= (getRnd() + 1) / 2.0;
        
        kernel[i] = vec.x;
        kernel[i + 1] = vec.y;
        kernel[i + 2] = vec.z;
    }

    // TODO: Put more samples closer to the origin of the sphere. They should
    // not be uniformly distributed in the sphere.
}

float SSAOShaderProgram::getRnd() {
    return (2.0 * (float)rand() / RAND_MAX) - 1.0;
}

void SSAOShaderProgram::use() {
    BaseShaderProgram::use();
    glDisable(GL_DEPTH_TEST);
    
    // Don't draw triangles with faces away from camera.
    glDisable(GL_CULL_FACE);
    
    glUniform1i(getUniformLoc("normal_tex"), 1);
    glUniform1i(getUniformLoc("position_tex"), 2);
    glUniform1i(getUniformLoc("rnd_normal_tex"), 3);
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