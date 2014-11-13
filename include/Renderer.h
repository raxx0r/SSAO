#include "ShaderProgram.h"

// GLM includes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {

private:
	ShaderProgram* shaderProgram;
	GLuint vao;
	GLuint vbo;
	glm::mat4 P;
	glm::mat4 V;
	glm::mat4 M;
    
public:
	Renderer();
	void updateModelMatrix(glm::mat4 modelMat);
	void initBuffers();
	void initUniforms();
	void useProgram(ShaderProgram* program);
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
    
};
