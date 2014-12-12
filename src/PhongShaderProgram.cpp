#include "PhongShaderProgram.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

PhongShaderProgram::~PhongShaderProgram() {
    glDeleteBuffers(2, vbo);
}

void PhongShaderProgram::setSSAO(int ssao) {
    ssao_ = ssao;
}

void PhongShaderProgram::use() {
    BaseShaderProgram::use();

    // Texture shader, no need for these tests
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    
    glUniform1i(getUniformLoc("normal_tex"), 1);
    glUniform1i(getUniformLoc("position_tex"), 2);
    glUniform1i(getUniformLoc("ssao_tex"), 3);
}

void PhongShaderProgram::update(glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint vInvLoc = getUniformLoc("V_inv");
    GLuint vLoc = getUniformLoc("V");
    GLuint lightPosLoc = getUniformLoc("light_pos");
    GLuint ssaoLoc = getUniformLoc("ssao_onoff");

    vInv = glm::inverse(viewMat);
    V = viewMat;

    glm::vec4 Vlight = viewMat * lightDirection;

    // Send data to GPU
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniform1i(ssaoLoc, ssao_);

    glUniform4fv(lightPosLoc, 1, glm::value_ptr(Vlight));

}

void PhongShaderProgram::initLightSource(const LightSource* lightSource) {

    glBindVertexArray(vao);

    GLuint lightPosLoc = getUniformLoc("light_pos");
    GLuint lightColLoc = getUniformLoc("light_col");

    // Transform light coords from view to coordinates
    lightDirection = lightSource->position();
    glm::vec4 Vlight = V * lightDirection;


    glUniform4fv(lightPosLoc, 1, glm::value_ptr(Vlight));
    glUniform3fv(lightColLoc, 1, glm::value_ptr(lightSource->color()));

    glBindVertexArray(0);
}

void PhongShaderProgram::initUniforms() {

    glBindVertexArray(vao);

    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    
    vInv = glm::inverse(V);

    // Find GPU locations
    GLuint vInvLoc = getUniformLoc("V_inv");

    // Send data to GPU
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    // glBindVertexArray(0);
}

// Init buffers for rendering. 
void PhongShaderProgram::initBuffers(std::vector<Model*> *models) {
    
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