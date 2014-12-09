#include "Camera.h"
#include "FboHandler.h"
#include "Utils.h"
#include "PhongShaderProgram.h"
#include "DeferredShaderProgram.h"
#include "SSAOShaderProgram.h"
#include "TextureUtils.h"

#include <stdio.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>

#include <IL/il.h>

enum WindowSize {
    WIDTH = 800,
    HEIGHT = 600
};

int main(void)
{
    // Initalize window and camera
    Window window = Window(WIDTH, HEIGHT, "Screen Space Ambient Occlusion");
    Camera camera = Camera();

    ilInit();
    GLuint rndNormalsText = TextureUtils::createTexture("textures/normals.jpg");

    // Initalize FBO:s
    FBOstruct fbo1, fbo2;
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(fbo1, window.getFramebufferWidth(), window.getFramebufferHeight());
    fboHandler.initFBO2(fbo2, window.getFramebufferWidth(), window.getFramebufferHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Create shaders for Deferred.
    Shader* deferredVert = new Shader("shaders/deferred.vert", GL_VERTEX_SHADER);
    Shader* deferredFrag = new Shader("shaders/deferred.frag", GL_FRAGMENT_SHADER);

    // Create shaders for Phong.
    Shader* phongVert = new Shader("shaders/phong.vert", GL_VERTEX_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);

    // Create shaders for SSAO.
    Shader* ssaoVert = new Shader("shaders/ssao.vert", GL_VERTEX_SHADER);
    Shader* ssaoFrag = new Shader("shaders/ssao.frag", GL_FRAGMENT_SHADER);

    // Setup Phong program
    PhongShaderProgram phongProgram(phongVert, phongFrag);
    phongProgram.use();
    phongProgram.initBuffers();
    phongProgram.initUniforms();

    // Setup SSAO program.
    SSAOShaderProgram ssaoProgram(ssaoVert, ssaoFrag);
    ssaoProgram.use();
    ssaoProgram.initBuffers();
    ssaoProgram.initUniforms();

    // Setup Deferred program.
    DeferredShaderProgram deferredProgram(deferredVert, deferredFrag);
    deferredProgram.use();

    // Shader pointers not necessary anymore. 
    delete deferredVert;
    delete deferredFrag;
    delete phongVert;
    delete phongFrag;
    delete ssaoVert;
    delete ssaoFrag;

    // Load all models and store in vector
    std::vector<Model*> models;
    Model* teapot = new Model("models/teapot.obj");
    Model* teapot2 = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");
    models.push_back(teapot);
    models.push_back(teapot2);
    models.push_back(sphere);
    
    // Setup VAO, VBO and Uniforms.
    deferredProgram.initBuffers(&models);
    deferredProgram.initUniforms();

    // Setup lightsource for Phong.
    LightSource lightSource = LightSource::DirectionalLightSource(glm::vec3(0.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    phongProgram.use();
    phongProgram.initLightSource(&lightSource);


    glm::mat4 M = glm::mat4(), V = glm::mat4();
    while (!window.isClosed()) {
        deferredProgram.use();
        fboHandler.useFBO(fbo1.index);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());

    	// Set movement of teapot
        M = glm::translate(glm::mat4(), glm::vec3(15.0, 0.0, 0.0));
        M = glm::rotate(M, Utils::degToRad(-90.0), glm::vec3(0.0, 1.0, 0.0));
        teapot->setModelmatrix(M);
	
	// Set movement of teapot2
        M = glm::translate(glm::mat4(), glm::vec3(-15.0, 0.0, 0.0));
        M = glm::rotate(M, Utils::degToRad(-90.0), glm::vec3(0.0, 1.0, 0.0));
        teapot2->setModelmatrix(M);
        
	// Set movement of sphere
        M = glm::translate(glm::mat4(), glm::vec3(0.0, 5.0, 5.0));
    	sphere->setModelmatrix(M);

    	// Draw each object 
    	V = camera.getMatrix();
    	for (auto &m : models) {
	    deferredProgram.update(m->getModelmatrix(), V);
    	    glDrawArrays(GL_TRIANGLES, m->getOffset(), m->numVertices);
    	}

        // Generate SSAO component
        ssaoProgram.use();

        fboHandler.useFBO(fbo2.index);

        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[0]);

        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Calculate lightning and display on screen.
        phongProgram.use();
        phongProgram.update(V);
        fboHandler.useFBO(0);
        
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[0]);

        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[1]);

        glActiveTexture(GL_TEXTURE0 + 3);
        glBindTexture(GL_TEXTURE_2D, fbo2.texids[0]);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        window.update();
        camera.update(window);
    }

    // Cleanup
    for (auto &m : models) {
        delete m;
    }
    
    fboHandler.deleteFBO(fbo1);
    fboHandler.deleteFBO(fbo2);
    
    glfwTerminate();
    
    return 0;
}
