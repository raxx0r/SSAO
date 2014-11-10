#include <stdio.h>
#include "Renderer.h"

int main(void)
{
    GLFWwindow* window;

    // Initialize the library. 
    if (!glfwInit())
        return -1;

    // Use GLSL 3.2 or higher.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a windowed mode window and its OpenGL context.
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current.
    glfwMakeContextCurrent(window);

    // Create shaders
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Initalize renderer.
    Renderer* renderer = new Renderer();

    // Setup a shader program and make it the current.
    ShaderProgram* phongProgram = renderer->buildShaderProgram(phongVert, phongFrag);
    phongProgram->use();

    // Setup VAO, VBO and Uniforms.
    renderer->initBuffers();
    renderer->initUniforms();

    delete phongVert;
    delete phongFrag;

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    // Loop until the user closes the window.
    while (!glfwWindowShouldClose(window)) {

        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, width, height);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Swap front and back buffers.
        glfwSwapBuffers(window);

        // Poll for and process events.
        glfwPollEvents();
    }

    // Cleanup
    glfwTerminate();
    glfwDestroyWindow(window);

    return 0;
}
