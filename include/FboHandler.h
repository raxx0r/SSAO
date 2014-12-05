#ifndef FBO_HANDLER_H
#define FBO_HANDLER_H

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES
#include <GLFW/glfw3.h>

/// Container struct for fbos. 
typedef struct FBOstruct {
	GLuint fb;
	GLuint rb;
	GLuint tex;
	GLint width;
	GLint height;
} FBOstruct;

class FboHandler {
  public:
  	FboHandler();
  	GLuint initFBO(GLint width, GLint height);
    void useFBO(GLuint fboindex);
  	virtual ~FboHandler();

  private:
  	void setupRenderTexture(FBOstruct& fbo);
  	bool checkFramebufferStatus();
};

#endif // FBO_HANDLER_H
