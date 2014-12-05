#ifndef RENDERER_H
#define RENDERER_H

#include "BaseShaderProgram.h"
#include "LightSource.h"
#include "Utils.h"

class Renderer {

  private:
	BaseShaderProgram* shaderProgram;
  public:
	Renderer();
	void initLightSource(const LightSource& lightSource);
	void useProgram(BaseShaderProgram& program);
	void buildShaderProgram(BaseShaderProgram* program);
    virtual ~Renderer();
};

#endif
