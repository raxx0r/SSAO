#ifndef RENDERER_H
#define RENDERER_H

#include "ShaderProgram.h"
#include "LightSource.h"
#include "Utils.h"

class Renderer {

  private:
	ShaderProgram* shaderProgram;
  public:
	Renderer();
	void initLightSource(const LightSource& lightSource);
	void useProgram(ShaderProgram& program);
	void buildShaderProgram(ShaderProgram* program);
    virtual ~Renderer();
};

#endif
