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
	void useProgram(ShaderProgram* program);
	ShaderProgram* buildShaderProgram(Shader* vert, Shader* frag);
    virtual ~Renderer();
    
};
