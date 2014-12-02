#include "Renderer.h"

Renderer::Renderer() {
    glEnable(GL_DEPTH_TEST);

    // Don't draw triangles with faces away from camera.
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Renderer::initLightSource(const LightSource& lightSource) {
    GLuint lightPosLoc = shaderProgram->getUniformLoc("light_pos");
    GLuint lightColLoc = shaderProgram->getUniformLoc("light_col");

    glUniform4fv(lightPosLoc, 1, glm::value_ptr(lightSource.position()));
    glUniform3fv(lightColLoc, 1, glm::value_ptr(lightSource.color()));
}

void Renderer::buildShaderProgram(ShaderProgram* program) {
    shaderProgram = program;
}

void Renderer::useProgram(ShaderProgram& program) {
    program.use();
}
   
Renderer::~Renderer() {

}