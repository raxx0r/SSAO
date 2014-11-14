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
    LightSource* lightSource = new LightSource(glm::vec3(0.0, 20.0, 0.0), glm::vec3(1.0, 0.5f, 0.0));
    renderer->initLightSource(lightSource);

    while(!window->isClosed()) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //GLfloat time = glfwGetTime();
        M = glm::mat4(); //glm::rotate( glm::mat4(), time * 7.0f, glm::vec3(0.0, 1.0, 0.0));
        V = camera->getMatrix();

        renderer->update(M, V);

        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
        glDrawArrays(GL_TRIANGLES, 0, model.numVerts);

        window->update();
        camera->update(window);
    }

    // Cleanup
    delete window;
    delete camera;
    delete lightSource;

    glfwTerminate();

    return 0;
}
