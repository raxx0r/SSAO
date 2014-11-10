#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
#include <string>

class Shader {

private:
    GLuint shaderID;
    GLuint createShaderFromFile(const GLchar* path, GLenum shaderType);
public:
    GLuint getShaderID();
    Shader(std::string path, GLenum type);
    virtual ~Shader();
    
};
