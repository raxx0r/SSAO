#include "Renderer.h"

Renderer::Renderer() {
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnable(GL_DEPTH_TEST);
}

void Renderer::update(glm::mat4 modelMat, glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint mLoc = shaderProgram->getUniformLoc("M");
    GLuint vLoc = shaderProgram->getUniformLoc("V");
    GLuint nLoc = shaderProgram->getUniformLoc("N");

    N = glm::transpose(glm::inverse(glm::mat3(viewMat * modelMat)));

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));

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

// Init buffers for rendering. 
void Renderer::initBuffers(Model m) {

    // Generate VBOs
    glGenBuffers(2, vbo);

    // Buffer positions
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * m.numVerts, m.vertices, GL_STATIC_DRAW);

    GLuint posLoc = shaderProgram->getAttribLoc("position");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posLoc);

    // Buffer normals
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * m.numVerts, m.normals, GL_STATIC_DRAW);

    GLuint normLoc = shaderProgram->getAttribLoc("normal");
    glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normLoc);
}

void Renderer::useProgram(ShaderProgram* program) {
    program->use();
}

void Renderer::initUniforms() {

	float aspect = (float) 640 / 480;

    // Init matrices
    M = glm::scale(glm::mat4(), glm::vec3(0.25f, 0.25f, 0.25f));
    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    P = glm::perspective(60.0f, aspect, 0.1f, 200.0f);
    N = glm::transpose(glm::inverse(glm::mat3(V * M)));

    // Find GPU locations
    GLuint mLoc = shaderProgram->getUniformLoc("M");
    GLuint vLoc = shaderProgram->getUniformLoc("V");
    GLuint pLoc = shaderProgram->getUniformLoc("P");
    GLuint nLoc = shaderProgram->getUniformLoc("N");

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}

   
Renderer::~Renderer() {
	glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
    delete shaderProgram;
}