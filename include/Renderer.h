#include "ShaderProgram.h"

class Renderer {

private:
	ShaderProgram* shaderProgram;
	GLuint vao;
	GLuint vbo;
    
public:
	Renderer();
	void initBuffers();
	void initUniforms();
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
    
};
