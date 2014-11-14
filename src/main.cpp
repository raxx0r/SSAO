#include <stdio.h>
#include "Renderer.h"
#include "Camera.h"


int main(void)
{
    Window* window = new Window(640, 480, "Screen Space Ambient Occlusion");
    Camera* camera = new Camera();

    // Create shaders.
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Initalize renderer.
    Renderer* renderer = new Renderer();

    // Create shader program with the two current shaders and make it the current program.
    ShaderProgram* phongProgram = renderer->buildShaderProgram(phongVert, phongFrag);
    renderer->useProgram(phongProgram);

    // Load in model.
    ModelImporter* importer = new ModelImporter();
    Model model = importer->importModel("models/teapot.obj");

    // Setup VAO, VBO and Uniforms.
    renderer->initBuffers(model);
    renderer->initUniforms();

    delete phongVert;
    delete phongFrag;

    glm::mat4 M, V, P;

    while(!window->isClosed()){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rotate object around z-axis.
        //float time = glfwGetTime();

        M = glm::mat4(); 
        V = camera->getMatrix();

        renderer->update(M,V);


        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glDrawArrays(GL_TRIANGLES, 0, model.numVerts);

        window->update();
        camera->update(window);
    }

    // Cleanup
    delete window;
    delete camera;
    glfwTerminate();

    return 0;
}
