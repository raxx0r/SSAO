#ifndef TEXTURE_UTILS_H
#define TEXTURE_UTILS_H
 
#include <GLFW/glfw3.h>

 
class TextureUtils
{
public:
    static GLuint createTexture(const GLchar* path);
};

#endif // TEXTURE_UTILS_H