#include "Renderer.h"
#include "Camera.h"
#include "FboHandler.h"
#include "Utils.h"
#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

enum WindowSize {
    WIDTH = 800,
    HEIGHT = 600
};

#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    Window window = Window(WIDTH, HEIGHT, "Screen Space Ambient Occlusion");
    Camera camera = Camera();

    // Create shaders.
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Initalize renderer.
    Renderer renderer = Renderer();

    // Initalize FBO:s
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(WIDTH, HEIGHT);

    // Draw to window.
    fboHandler.useFBO(0);

    // Create shader program with the two current shaders and make it the current program.
    ShaderProgram phongProgram;
    renderer.buildShaderProgram(phongProgram, phongVert, phongFrag);
    renderer.useProgram(phongProgram);

    delete phongVert;
    delete phongFrag;

    // Load in model.
    int const AMOUNT_MODELS = 2;
    Model* models[AMOUNT_MODELS]; 
    Model* teapot = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");
    models[0] = teapot;
    models[1] = sphere;
    
    // Setup VAO, VBO and Uniforms.
    renderer.initBuffers(models, AMOUNT_MODELS);
    renderer.initUniforms();

    glm::mat4 M, V, P;

    LightSource lightSource = LightSource::PointLightSource(glm::vec3(0.0, 11.0, 18.0), glm::vec3(1.0, 0.5, 0.0));
    //LightSource* lightSource = LightSource::DirectionalLightSource(glm::vec3(0.0, 1.0, 0.0), glm::vec3(0.7, 0.2f, 0.0));
    renderer.initLightSource(lightSource);
    
    while(!window.isClosed()){

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());

    	// Set movement of object
    	sphere->setModelmatrix(glm::translate(sphere->getModelmatrix(), glm::vec3(0.01,0.0,0.0)));
    	teapot->setModelmatrix(glm::rotate(teapot->getModelmatrix(), Utils::degToRad(0.05), glm::vec3(1.0,0.0,0.0)));
    	
    	// Draw each object
    	V = camera.getMatrix();
    	for(int i = 0; i < AMOUNT_MODELS; i++) {
    	  renderer.update(models[i]->getModelmatrix(),V);
    	  glDrawArrays(GL_TRIANGLES, models[i]->getOffset(), models[i]->numVertices);
    	}
            
        window.update();
        camera.update(window);
    }

    // Cleanup
    for(int i = 0; i < AMOUNT_MODELS; i++) {
	   delete models[i];
    }
    
    glfwTerminate();

    return 0;
}
