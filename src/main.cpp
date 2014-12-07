#include "Camera.h"
#include "FboHandler.h"
#include "Utils.h"
#include "PhongShaderProgram.h"
#include "SSAOShaderProgram.h"

#include <stdio.h>
#include <vector>
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

    // Setup SSAO program.
    SSAOShaderProgram ssaoProgram(ssaoVert, ssaoFrag);
    ssaoProgram.initBuffers();
    ssaoProgram.initUniforms();

    // Setup Phong program.
    PhongShaderProgram phongProgram(phongVert, phongFrag);

    // Shader pointers not necessary anymore. 
    delete phongVert;
    delete phongFrag;
    delete ssaoVert;
    delete ssaoFrag;

    std::vector<Model*> models;

    Model* teapot = new Model("models/teapot.obj");
    Model* teapot2 = new Model("models/teapot.obj");
    Model* sphere = new Model("models/sphere.obj");

    models.push_back(teapot);
    models.push_back(teapot2);
    models.push_back(sphere);
    
    // Setup VAO, VBO and Uniforms.
    phongProgram.initBuffers(&models);
    phongProgram.initUniforms();

    // Setup lightsource for Phong.
    LightSource lightSource = LightSource::DirectionalLightSource(glm::vec3(0.0, 1.0, 1.0), glm::vec3(1.0, 1.0, 1.0));
    phongProgram.initLightSource(&lightSource);
    
    // Initalize FBO:s
    FBOstruct fbo1;
    FboHandler fboHandler = FboHandler();
    fboHandler.initFBO(fbo1, window.getFramebufferWidth(), window.getFramebufferHeight());
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glm::mat4 M = glm::mat4(), V = glm::mat4();
    while (!window.isClosed()) {
        phongProgram.use();
        fboHandler.useFBO(fbo1.index);
        // float time = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    	glViewport(0, 0, window.getFramebufferWidth(), window.getFramebufferHeight());
      
         
    	// Set movement of object
        M = glm::translate(glm::mat4(), glm::vec3(15.0, 0.0, 0.0));
        M = glm::rotate(M, Utils::degToRad(-90.0), glm::vec3(0.0, 1.0, 0.0));
        teapot->setModelmatrix(M);

        M = glm::translate(glm::mat4(), glm::vec3(-15.0, 0.0, 0.0));
        M = glm::rotate(M, Utils::degToRad(-90.0), glm::vec3(0.0, 1.0, 0.0));
        teapot2->setModelmatrix(M);
        
        M = glm::translate(glm::mat4(), glm::vec3(0.0, 5.0, 5.0));
    	sphere->setModelmatrix(M);

    	// Draw each object
    	V = camera.getMatrix();
    	for (auto &m : models) {
	        phongProgram.update(m->getModelmatrix(), V);
    	    glDrawArrays(GL_TRIANGLES, m->getOffset(), m->numVertices);
    	}

        ssaoProgram.use();
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(ssaoProgram.getUniformLoc("tex"), 0);
        glBindTexture(GL_TEXTURE_2D, fbo1.texids[0]);

        fboHandler.useFBO(0);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        window.update();
        camera.update(window);
    }

    // Cleanup
    for (auto &m : models) {
        delete m;
    }

    glDeleteTextures(3, fbo1.texids);
    glDeleteBuffers(1, &fbo1.depth);
    glDeleteBuffers(1, &fbo1.index);
    
    glfwTerminate();
    return 0;
}
