#ifndef RENDERER_H
#define RENDERER_H

#include "ShaderProgram.h"
#include "LightSource.h"
#include "Model.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

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

	// Inverted view matrix, used for specular highlights.
	glm::mat4 vInv;

	// Model matrix
	glm::mat4 M;

	// Normal matrix
	glm::mat3 N;
	
	long offset;
    
  public:
	Renderer();
	void update(glm::mat4 modelMat, glm::mat4 viewMat);
	void initBuffers(Model* m[], const int AMOUNT_MODELS);
	void initUniforms();
	void initLightSource(const LightSource& lightSource);
	void useProgram(ShaderProgram* program);
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
};

#endif
