#include "BaseShaderProgram.h"

BaseShaderProgram::BaseShaderProgram(Shader* vert, Shader* frag) {
    programID = glCreateProgram();
    
    // Attach two shaders and links them together to create a ShaderProgram
    attachShader(vert); 
    attachShader(frag);
    link();
    
    // Initialize vao
    glGenVertexArrays(1, &vao);
}
    
void BaseShaderProgram::bindFragDataLocation(GLint colorAttachment, std::string name) {
    glBindFragDataLocation(programID, colorAttachment, name.c_str());
}

void BaseShaderProgram::attachShader(Shader* shader) {
    glAttachShader(programID, shader->getShaderID());
}

void BaseShaderProgram::link() {

    glLinkProgram(programID);
    
    GLint linkStatus;
    glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
    if (linkStatus != GL_TRUE) {
        std::cout << "Program link failed!" << std::endl;
        GLint infoLogLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* infoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(programID, infoLogLength, NULL, infoLog);
        std::cout << infoLog << std::endl;
        delete[] infoLog;
    }
}

void BaseShaderProgram::use() {
    glUseProgram(programID);
    glBindVertexArray(vao); 
}
    
GLuint BaseShaderProgram::getProgramID() {
    return programID;
}       
    
GLint BaseShaderProgram::getUniformLoc(std::string name) {
    return glGetUniformLocation(programID, name.c_str());
}

BaseShaderProgram::~BaseShaderProgram() {
    glDeleteShader(programID);
    glDeleteVertexArrays(1, &vao);
}