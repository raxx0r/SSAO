#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(Shader* vert, Shader* frag) {
    programID = glCreateProgram();
    
    // Attach two shaders and links them together to create a ShaderProgram
    attachShader(vert);
    attachShader(frag);
    bindFragDataLocation(0, "out_color");
    link();
    
    // Intialize vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
     
    // Initialize vbo
    glGenBuffers(2, vbo);
    offset = 0;
}

ShaderProgram::~ShaderProgram() {
    glDeleteShader(programID);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, vbo);
}

void ShaderProgram::attachShader(Shader* shader) {
    glAttachShader(programID, shader->getShaderID());
}

void ShaderProgram::update(glm::mat4 modelMat, glm::mat4 viewMat){ 

    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint nLoc = getUniformLoc("N");
    GLuint vInvLoc = getUniformLoc("V_inv");

    N = glm::transpose(glm::inverse(glm::mat3(viewMat * modelMat)));
    vInv = glm::inverse(viewMat);

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));

}

void ShaderProgram::initUniforms() {

    float aspect = (float) 800 / 600;

    // Init matrices
    M = glm::mat4();
    V = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, -30.0f));
    P = glm::perspective(Utils::degToRad(60.0f), aspect, 0.1f, 200.0f);
    N = glm::transpose(glm::inverse(glm::mat3(V * M)));
    vInv = glm::inverse(V);

    // Find GPU locations
    GLuint mLoc = getUniformLoc("M");
    GLuint vLoc = getUniformLoc("V");
    GLuint pLoc = getUniformLoc("P");
    GLuint nLoc = getUniformLoc("N");
    GLuint vInvLoc = getUniformLoc("V_inv");

    // Send data to GPU
    glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
    glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
    glUniformMatrix4fv(vInvLoc, 1, GL_FALSE, glm::value_ptr(vInv));
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, glm::value_ptr(N));
}

// Init buffers for rendering. 
void ShaderProgram::initBuffers(Model* m[], const int AMOUNT_MODELS) {
    
    long bufferSize = 0;
    GLuint posLoc = getAttribLoc("position");
    GLuint normLoc = getAttribLoc("normal");    

    // Calculate the buffer size
    for(int i = 0; i < AMOUNT_MODELS; i++) {
        bufferSize += 3.0 * sizeof(float) * m[i]->numVertices;
    }
    
    // Give specified size to position buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    // Give specified size to normal buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glBufferData(GL_ARRAY_BUFFER, 3.0 * sizeof(float) * bufferSize, NULL, GL_STATIC_DRAW);
    
    for(int i = 0; i < AMOUNT_MODELS; i++) {
        long size = 3.0 * sizeof(float) * m[i]->numVertices;
      
        // Position buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m[i]->vertices);
      
        glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(posLoc);
      
        // Normal buffer
        glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
        glBufferSubData(GL_ARRAY_BUFFER, offset, size, m[i]->normals);
      
        glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)(offset));
        glEnableVertexAttribArray(normLoc);
      
        m[i]->setOffset(offset / (3.0 * sizeof(float)));
      
        offset += 3.0 * sizeof(float) * m[i]->numVertices;
    }
      
    // Set attribute pointer to first object
    glBindBuffer(GL_ARRAY_BUFFER, vbo[POSITION_VBO]);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posLoc);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[NORMAL_VBO]);
    glVertexAttribPointer(normLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(normLoc);
}

// Links the attached shaders together, prints out an error message if
// linking fails.
void ShaderProgram::link() {
    
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

void ShaderProgram::use() {
    glUseProgram(programID);
}

GLuint ShaderProgram::getProgramID() {
    return programID;
}

void ShaderProgram::bindFragDataLocation(GLint colorAttachment, std::string name){
    glBindFragDataLocation(programID, colorAttachment, name.c_str());
}

GLint ShaderProgram::getAttribLoc(std::string name) {
    return glGetAttribLocation(programID, name.c_str());
}

GLint ShaderProgram::getUniformLoc(std::string name) {
    return glGetUniformLocation(programID, name.c_str());
}