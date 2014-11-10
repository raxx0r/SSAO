#include "Shader.h"
#include <iostream>
#include <fstream>


Shader::Shader(std::string path, GLenum type) {
    shaderID = createShaderFromFile(path.c_str(), type);
}

// Private method used to compile a shader from a file path.
// Returns 0 and prints an error message if it fails to compile the shader,
// otherwise it returns the ID for the shader created.
GLuint Shader::createShaderFromFile(const GLchar* path, GLenum shaderType) {
    GLuint newShaderId = glCreateShader(shaderType);
    std::ifstream fin;
    fin.open(path);
    if (!fin.is_open()) {
        fin.close();
        std::cout << "File not found! '" << path << "'!" << std::endl;
        return 0;
    }
    
    std::string source((std::istreambuf_iterator<GLchar>(fin)), std::istreambuf_iterator<GLchar>());
    fin.close();
    
    const GLchar* shaderSource = source.c_str();
    glShaderSource(newShaderId, 1, &shaderSource, NULL);
    
    glCompileShader(newShaderId);
    
    GLint compileStatus;
    glGetShaderiv(newShaderId, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus != GL_TRUE) {
        std::cout << "Shader failed to Compile: '" << path << "' !" << std::endl;
        GLint infoLogLength;
        glGetShaderiv(newShaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetShaderInfoLog(newShaderId, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete[] infoLog;
        return 0;
    }
    
    return newShaderId;
}

GLuint Shader::getShaderID(){
    return shaderID;
}

Shader::~Shader(){
    glDeleteShader(shaderID);
}