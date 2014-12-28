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
	glGenTextures(3, fbo.texids);

	// Setup texture that stores normals.
	glBindTexture(GL_TEXTURE_2D, fbo.texids[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbo.texids[0], 0);

	// Setup texture that stores positions.
	glBindTexture(GL_TEXTURE_2D, fbo.texids[1]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, fbo.texids[1], 0);

	// Setup depthbuffer.
	glGenRenderbuffers(1, &fbo.depth);
	glBindRenderbuffer(GL_RENDERBUFFER, fbo.depth);

	// Attach renderbuffer to framebuffer
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, fbo.width, fbo.height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo.depth);

	GLenum drawbuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
	glDrawBuffers(2, drawbuffers);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	checkFramebufferStatus();
}

void FboHandler::initFBO2(FBOstruct& fbo, GLint width, GLint height) {
	fbo.width = width;
	fbo.height = height;

	glGenFramebuffers(1, &fbo.index);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo.index);
	glGenTextures(3, fbo.texids);

	// Setup texture that stores occlusion.
	glBindTexture(GL_TEXTURE_2D, fbo.texids[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, fbo.texids[0], 0);

	GLenum drawbuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, drawbuffers);

	// Unbind
	glBindTexture(GL_TEXTURE_2D, 0);
	checkFramebufferStatus();
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

void FboHandler::deleteFBO(FBOstruct& fbo) {
    glDeleteTextures(3, fbo.texids);

    glDeleteBuffers(1, &fbo.depth);
    glDeleteBuffers(1, &fbo.index);
}

FboHandler::~FboHandler() {

}
