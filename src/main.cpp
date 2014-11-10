#include <stdio.h>
#include "ShaderProgram.h"

int main(void)
{
    GLFWwindow* window;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    // Use GLSL 3.2 or higher
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Initalize Shaders
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);
    
    // Setup Shaderprogram
    ShaderProgram* shaderProgram = new ShaderProgram();
    shaderProgram->attachShader(phongVert);
    shaderProgram->attachShader(phongFrag);
    shaderProgram->bindFragDataLocation(0, "outColor");
    shaderProgram->link();
    shaderProgram->use();

    float vertices[] = {
         0.0f,  0.5f, // Vertex 1 (X, Y)
         0.5f, -0.5f, // Vertex 2 (X, Y)
        -0.5f, -0.5f  // Vertex 3 (X, Y)
    };

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLint posAttrib = shaderProgram->getAttribLoc("position");
    glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(posAttrib);


    //Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}
