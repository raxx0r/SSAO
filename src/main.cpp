#include "Camera.h"
#include "FboHandler.h"
#include "Utils.h"
#include "PhongShaderProgram.h"
#include "SSAOShaderProgram.h"

#include <stdio.h>
#include <glm/gtc/matrix_transform.hpp>

enum WindowSize {
    WIDTH = 800,
    HEIGHT = 600
};

int main(void)
{
    Window window = Window(WIDTH, HEIGHT, "Screen Space Ambient Occlusion");
    Camera camera = Camera();

    // Create shaders for Phong.
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Create shaders for SSAO.
    Shader* ssaoVert = new Shader("shaders/ssao.vert", GL_VERTEX_SHADER);
    Shader* ssaoFrag = new Shader("shaders/ssao.frag", GL_FRAGMENT_SHADER);

    // Create shader program with the two current shaders and make it the current program.
    PhongShaderProgram phongProgram(phongVert, phongFrag);
    SSAOShaderProgram ssaoProgram(ssaoVert, ssaoFrag);
    phongProgram.use();

    // Shader pointers not necessary anymore. 
    delete phongVert;
    delete phongFrag;
    delete ssaoVert;
    delete ssaoFrag;

    // Initalize FBO:s
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(WIDTH, HEIGHT);

    // Draw to window.
    fboHandler.useFBO(0);

    // Load in model.
    int const AMOUNT_MODELS = 2;
    Model* models[AMOUNT_MODELS]; 
    Model* teapot = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");
    models[0] = teapot;
    models[1] = sphere;
    
    // Setup VAO, VBO and Uniforms.
    phongProgram.initBuffers(models, AMOUNT_MODELS);
    phongProgram.initUniforms();

    ssaoProgram.initBuffers();
    ssaoProgram.initUniforms();

    // Setup lightsource for Phong.
    LightSource lightSource = LightSource::PointLightSource(glm::vec3(0.0, 10.0, 0.0), glm::vec3(1.0, 0.5, 0.0));
    phongProgram.initLightSource(&lightSource);

    glm::mat4 M = glm::mat4(), V = glm::mat4();
    ssaoProgram.use();
    while (!window.isClosed()) {

     //    float time = glfwGetTime();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());

        /* 
    	// Set movement of object
        M = glm::rotate(glm::mat4(), Utils::degToRad(10.0 * time), glm::vec3(0.0, 1.0, 0.0));
        M = glm::translate(M, glm::vec3(15.0, 0.0, 0.0));
        M = glm::rotate(M, Utils::degToRad(90.0), glm::vec3(0.0, 1.0, 0.0));
        teapot->setModelmatrix(M);
        
        M = glm::rotate(glm::mat4(), Utils::degToRad(10.0 * time), glm::vec3(0.0, 1.0, 0.0));
        M = glm::translate(M, glm::vec3(-15.0, 5.0, 0.0));
    	sphere->setModelmatrix(M);

    	// Draw each object
    	V = camera.getMatrix();
    	for(int i = 0; i < AMOUNT_MODELS; i++) {
	        phongProgram.update(models[i]->getModelmatrix(), V);
    	    glDrawArrays(GL_TRIANGLES, models[i]->getOffset(), models[i]->numVertices);
    	}
        */
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.update();
        camera.update(window);
    }

    // Cleanup
    for (int i = 0; i < AMOUNT_MODELS; i++) {
	   delete models[i];
    }
    
    glfwTerminate();
    return 0;
}
