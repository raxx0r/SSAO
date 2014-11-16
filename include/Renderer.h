#ifndef RENDERER_H
#define RENDERER_H

#include "ShaderProgram.h"
#include "ModelImporter.h"
#include "LightSource.h"

// GLM includes
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
    
  public:
	Renderer();
	void update(glm::mat4 modelMat, glm::mat4 viewMat);
	void initBuffers(Model m);
	void initUniforms();
	void initLightSource(LightSource* lightSource);
	void useProgram(ShaderProgram* program);
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
};

#endif