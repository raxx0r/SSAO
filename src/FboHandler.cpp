#include "FboHandler.h"
#include "stdio.h"

FboHandler::FboHandler() {

}

void FboHandler::useFBO(GLuint fboindex) {
	glBindFramebuffer(GL_FRAMEBUFFER, fboindex);
}

GLuint FboHandler::initFBO(GLint width, GLint height) {

	// Create new fbo struct
	FBOstruct fbo;
	fbo.width = width;
	fbo.height = height;

	// Setup framebuffer
	glGenFramebuffers(1, &fbo.fb);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.fb);

	// Setup texture
	setupRenderTexture(fbo);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fbo.tex, 0);

	// Setup depthbuffer.
	glGenRenderbuffers(1, &fbo.rb);
	glBindRenderbuffer(GL_RENDERBUFFER, fbo.rb);

	// Attach renderbuffer to framebuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fbo.width, fbo.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo.rb);

	if (!checkFramebufferStatus()) {
		return -1;
	}
	return fbo.fb;
}

/// Create a texture which we can render to.
void FboHandler::setupRenderTexture(FBOstruct& fbo) {
	glGenTextures(1, &fbo.rb);
	glBindTexture(GL_TEXTURE_2D, fbo.rb);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, fbo.width, fbo.height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/// Checks if anything wrong has happened to the framebuffer.
bool FboHandler::checkFramebufferStatus() {
	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE) {
		printf("Framebuffer error\n");
		return false;
	}
	return true;
}

FboHandler::~FboHandler() {

}