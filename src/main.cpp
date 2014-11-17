#include <stdio.h>
#include "Renderer.h"
#include "Camera.h"
#include "Utils.h"


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
    Model* teapot = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");
    
    // Setup VAO, VBO and Uniforms.
    renderer->initBuffers(teapot);
    renderer->initBuffers(sphere);
    renderer->initUniforms();

    delete phongVert;
    delete phongFrag;

    glm::mat4 M, M2, V, P;
    
    
    while(!window->isClosed()){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        M = glm::rotate(M, Utils::degToRad(0.01), glm::vec3(1.0,0.0,0.0));
	//M = glm::translate(glm::mat4(), glm::vec3(10.0,0.0,0.0));
        V = camera->getMatrix();

        renderer->update(M,V);
    
        glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());
	glDrawArrays(GL_TRIANGLES, 0, teapot->numVertices);
	
	M2 = glm::translate(glm::mat4(), glm::vec3(-10.0,0.0,0.0));
        V = camera->getMatrix();

        renderer->update(M2,V);
	
	glDrawArrays(GL_TRIANGLES, teapot->numVertices, sphere->numVertices);
	
        window->update();
        camera->update(window);
    }

    // Cleanup
    delete window;
    delete camera;
    glfwTerminate();

    return 0;
}
