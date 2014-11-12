#include "Renderer.h"

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Renderer::Renderer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

// Attach two shaders and links them together, returns a pointer to the program.
ShaderProgram* Renderer::buildShaderProgram(Shader* vert, Shader* frag) {
	shaderProgram = new ShaderProgram();
	shaderProgram->attachShader(vert);
    shaderProgram->attachShader(frag);
    shaderProgram->bindFragDataLocation(0, "outColor");
    shaderProgram->link();

    return shaderProgram;
}

// Init buffers for rendering, it also creates and binds a VAO.
void Renderer::initBuffers() {

	float vertices[] = {
         0.0f,  0.5f,
         0.5f, -0.5f, 
        -0.5f, -0.5f 
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // TODO: should be moved to another function.
    GLint posAttrib = shaderProgram->getAttribLoc("position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);
}

void Renderer::useProgram(ShaderProgram* program) {
    program->use();
}

void Renderer::initUniforms() {

	float aspect = (float) 640 / 480;

    glm::mat4 projectionMat = glm::perspective(60.0f, aspect, 0.1f, 100.0f);
    glm::mat4 viewMat = glm::mat4();
    glm::mat4 modelMat = glm::mat4();
    modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 MVP = projectionMat * viewMat * modelMat;

    GLuint mvpLoc = shaderProgram->getUniformLoc("MVP");
    glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(MVP));
}
   
Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    delete shaderProgram;
}