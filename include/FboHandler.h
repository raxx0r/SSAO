#ifndef FBO_HANDLER_H
#define FBO_HANDLER_H

#define GLFW_INCLUDE_GLCOREARB
#define GL_GLEXT_PROTOTYPES

#ifndef _glfw3_h_
#include <GLFW/glfw3.h>
#endif 

/// Container struct for fbos. 
typedef struct FBOstruct {
	GLuint index;
	GLuint depth;
	GLuint texids[3];  // Original, Normals, Textures
	GLint width;
	GLint height;
} FBOstruct;

class FboHandler {
  public:
    FboHandler();
    void initFBO(FBOstruct& fbo, GLint width, GLint height);
    void initFBO2(FBOstruct& fbo, GLint width, GLint height);
    void useFBO(GLuint fboindex);
    void deleteFBO(FBOstruct& fbo); 
    virtual ~FboHandler();

  private:
  	bool checkFramebufferStatus();
};

#endif // FBO_HANDLER_H
