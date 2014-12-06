#include "FboHandler.h"
#include <iostream>

FboHandler::FboHandler() {

}

void FboHandler::useFBO(GLuint fboindex) {
	glBindFramebuffer(GL_FRAMEBUFFER, fboindex);
}

void FboHandler::initFBO(FBOstruct& fbo, GLint width, GLint height) {

	fbo.width = width;
	fbo.height = height;

	// Setup framebuffer
	glGenFramebuffers(1, &fbo.index);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.index);

	// Setup texture
	setupRenderTexture(fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbo.tex, 0);

	// Setup depthbuffer.
	glGenRenderbuffers(1, &fbo.rb);
	glBindRenderbuffer(GL_RENDERBUFFER, fbo.rb);

	// Attach renderbuffer to framebuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fbo.width, fbo.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo.rb);

	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers);

	checkFramebufferStatus();
}

/// Create a texture which we can render to.
void FboHandler::setupRenderTexture(FBOstruct& fbo) {
	glGenTextures(1, &fbo.tex);
	glBindTexture(GL_TEXTURE_2D, fbo.tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fbo.width, fbo.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/// Checks if anything wrong has happened to the framebuffer.
bool FboHandler::checkFramebufferStatus() {
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "ERROR: Framebuffer error." << std::endl;
		return false;
	}
	return true;
}

FboHandler::~FboHandler() {

}