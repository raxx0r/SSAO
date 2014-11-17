#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <Shader.h>
#include <iostream>
#include <string>


class ShaderProgram {
private:
    GLuint programID;
    
public:
    ShaderProgram();
    virtual ~ShaderProgram();
    
    void bindFragDataLocation(GLint colorAttachment, std::string name);
    void attachShader(Shader* shader);
    void link();
    void use();
    GLuint getProgramID();
    GLint getAttribLoc(std::string name);
    GLint getUniformLoc(std::string name);


    
};

#endif