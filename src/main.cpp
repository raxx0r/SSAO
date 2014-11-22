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
    int const AMOUNT_MODELS = 2;
    Model* models[AMOUNT_MODELS]; 
    Model* teapot = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");
    models[0] = teapot;
    models[1] = sphere;
    
    // Setup VAO, VBO and Uniforms.
    renderer->initBuffers(models, AMOUNT_MODELS);
    renderer->initUniforms();

    delete phongVert;
    delete phongFrag;

    glm::mat4 M, M2, V, P;
    
    while(!window->isClosed()){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, window->getFrameBufferWidth(), window->getFrameBufferHeight());

	// Set movement of object
	sphere->setModelmatrix(glm::translate(sphere->getModelmatrix(), glm::vec3(0.01,0.0,0.0)));
	teapot->setModelmatrix(glm::rotate(teapot->getModelmatrix(), Utils::degToRad(0.01), glm::vec3(1.0,0.0,0.0)));
	
	// Draw each object
	V = camera->getMatrix();
	for(int i = 0; i < AMOUNT_MODELS; i++) {
	  renderer->update(models[i]->getModelmatrix(),V);
	  glDrawArrays(GL_TRIANGLES, models[i]->getOffset(), models[i]->numVertices);
	}
        
        window->update();
        camera->update(window);
    }

    // Cleanup
    for(int i = 0; i < AMOUNT_MODELS; i++) {
	delete models[i];
    }
    delete window;
    delete camera;
    glfwTerminate();

    return 0;
}
