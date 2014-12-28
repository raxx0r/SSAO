#include "Camera.h"
#include "FboHandler.h"
#include "Utils.h"
#include "PhongShaderProgram.h"
#include "DeferredShaderProgram.h"
#include "PassShaderProgram.h"
#include "TextureUtils.h"

#include <stdio.h>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <IL/il.h>

#define GL_GLEXT_PROTOTYPES

enum WindowSize {
    WIDTH = 800,
    HEIGHT = 600
};

int main(void)
{
    // Initalize window and camera
    Window window = Window(WIDTH, HEIGHT, "Screen Space Ambient Occlusion");
    Camera camera = Camera();
    
    // Create texture
    ilInit();
    GLuint rndNormalsText = TextureUtils::createTexture("textures/normals.jpg");

    // Initalize FBO:s
    FBOstruct fbo1, fbo2, fbo3;
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(fbo1, window.getFramebufferWidth(), window.getFramebufferHeight());
    fboHandler.initFBO2(fbo2, window.getFramebufferWidth(), window.getFramebufferHeight());
    fboHandler.initFBO2(fbo3, window.getFramebufferWidth(), window.getFramebufferHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Create shaders
    Shader* deferredVert = new Shader("shaders/deferred.vert", GL_VERTEX_SHADER);
    Shader* passVert = new Shader("shaders/pass.vert", GL_VERTEX_SHADER);

    Shader* deferredFrag = new Shader("shaders/deferred.frag", GL_FRAGMENT_SHADER);
    Shader* phongFrag = new Shader("shaders/phong.frag", GL_FRAGMENT_SHADER);
    Shader* ssaoFrag = new Shader("shaders/ssao.frag", GL_FRAGMENT_SHADER);
    Shader* blurFrag = new Shader("shaders/blur.frag", GL_FRAGMENT_SHADER);

    // Setup Phong program
    PhongShaderProgram phongProgram(passVert, phongFrag);
    phongProgram.use();
    phongProgram.initBuffers();
    phongProgram.initUniforms();
    camera.attachPhongProgram(&phongProgram);

    // Setup SSAO program.
    PassShaderProgram ssaoProgram(passVert, ssaoFrag);
    ssaoProgram.use();
    ssaoProgram.initBuffers();
    ssaoProgram.initUniforms();

    PassShaderProgram blurProgram(passVert, blurFrag);
    blurProgram.use();
    blurProgram.initBuffers();
    blurProgram.initUniforms();

    // Setup Deferred program.
    DeferredShaderProgram deferredProgram(deferredVert, deferredFrag);
    deferredProgram.use();

    // Shader pointers not necessary anymore. 
    delete deferredVert;
    delete deferredFrag;
    delete blurFrag;
    delete phongFrag;
    delete ssaoFrag;
    delete passVert;

    // Load all models and store in vector
    std::vector<Model*> models;
    Model bunny = Model("models/bunny.obj");
    Model armadillo = Model("models/armadillo.obj");
    Model plane = Model("models/plane.obj");
    Model tea = Model("models/teapot.obj");
    
    models.push_back(&bunny);
    models.push_back(&armadillo);
    models.push_back(&plane);
    models.push_back(&tea);
    
    // Setup VAO, VBO and Uniforms.
    deferredProgram.initBuffers(&models);
    deferredProgram.initUniforms();

    // Setup lightsource for Phong.
    LightSource lightSource = LightSource::DirectionalLightSource(glm::vec3(0.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    phongProgram.use();
    phongProgram.initLightSource(&lightSource);


    glm::mat4 M = glm::mat4(), V = glm::mat4();
    glUniform1i(phongProgram.getUniformLoc("ssao_onoff"), 0);
    while (!window.isClosed()) {
        deferredProgram.use();
        fboHandler.useFBO(fbo1.index);
	    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());
	
	   // Set movement of teapot
    	M = glm::scale(glm::mat4(1.0f),glm::vec3(10.0f));
    	M = glm::translate(M, glm::vec3(0.0, 0.5, 0.0));
    	tea.setModelmatrix(M);
	
    	// Set movement of plane
    	M = glm::scale(glm::mat4(1.0f),glm::vec3(5.0f));
    	M = glm::translate(M, glm::vec3(3.0, -0.1, 0.0));
    	plane.setModelmatrix(M);
	
    	// Set movement of bunny
    	M = glm::scale(glm::mat4(1.0f),glm::vec3(6.0f));
    	M = glm::translate(M, glm::vec3(3.0, 0.0, 0.0));
    	bunny.setModelmatrix(M);
    	
    	// Set movement of armadillo
    	M = glm::scale(glm::mat4(1.0f),glm::vec3(6.0f));
    	M = glm::translate(M, glm::vec3(-2.5, 1.0, 0.0));
    	M = glm::rotate(M, Utils::degToRad(180.0), glm::vec3(0.0, 1.0, 0.0));
    	armadillo.setModelmatrix(M);

    	// Draw each object 
    	V = camera.getMatrix();
    	for (auto &m : models) {
	    deferredProgram.update(m->getModelmatrix(), V);
    	    glDrawArrays(GL_TRIANGLES, m->getOffset(), m->numVertices);
    	}

        // Generate SSAO component
        ssaoProgram.use();

        fboHandler.useFBO(fbo3.index);

        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[0]);

        glActiveTexture(GL_TEXTURE0 + 2);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[1]);

        glActiveTexture(GL_TEXTURE0 + 3);
        glBindTexture(GL_TEXTURE_2D, rndNormalsText);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Blur SSAO component
        blurProgram.use();
        fboHandler.useFBO(fbo2.index);
        
        glActiveTexture(GL_TEXTURE0 + 1);
        glBindTexture(GL_TEXTURE_2D, fbo3.texids[0]);

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
    fboHandler.deleteFBO(fbo1);
    fboHandler.deleteFBO(fbo2);
    fboHandler.deleteFBO(fbo3);
    
    glfwTerminate();
    
    return 0;
}
