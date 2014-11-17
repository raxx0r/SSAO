#include "ShaderProgram.h"
#include "Model.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer {

private:
	enum vboIndices {
		POSITION_VBO,
		NORMAL_VBO
	};

	ShaderProgram* shaderProgram;
	GLuint vao;
	GLuint vbo[2];

	// Perspective matrix
	glm::mat4 P;

	// View matrix
	glm::mat4 V;

	// Model matrix
	glm::mat4 M;

	// Normal matrix
	glm::mat3 N;
	
	int amountModels;
	long offset;
    
public:
	Renderer();
	void update(glm::mat4 modelMat, glm::mat4 viewMat);
	void initBuffers(Model* m);
	void initUniforms();
	void useProgram(ShaderProgram* program);
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
};
