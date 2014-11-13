#include <stdio.h>
#include "Renderer.h"
#include "Window.h"


int main(void)
{
    Window* window;
    window = new Window(640, 480, "Screen Space Ambient Occlusion");

    // Create shaders
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Initalize renderer.
    Renderer* renderer = new Renderer();

    // Create shader program with the two current shaders and make it the current program.
    ShaderProgram* phongProgram = renderer->buildShaderProgram(phongVert, phongFrag);
    renderer->useProgram(phongProgram);

    ModelImporter* importer = new ModelImporter();
    Model model = importer->importModel("models/sphere.obj");

    // Setup VAO, VBO and Uniforms.
    renderer->initBuffers(model);
    renderer->initUniforms();

    // renderer->sendVertices(importer->getVertices());
    

    delete phongVert;
    delete phongFrag;

    while(!window->shouldClose()){
        
        glClear(GL_COLOR_BUFFER_BIT);
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glDrawArrays(GL_TRIANGLES, 0, 3);


        window->swapBuffers();
    }

    // Cleanup
    delete window;
    glfwTerminate();


    return 0;
}
