#include "TextureUtils.h"
#include <IL/il.h>
#include <iostream>
 
GLuint TextureUtils::createTexture(const GLchar *path){
    ILuint image = ilGenImage();
    ilBindImage(image);
   
    std::cout << "success" << std::endl;
    ILboolean loadSuccess = ilLoadImage(path);
 
    if(!loadSuccess){
        std::cout << "Failed to load image: " << path << std::endl;
        ilBindImage(NULL);
        ilDeleteImage(image);
        return 0;
    }
   
    ILboolean convertSuccess = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
   
    if(!convertSuccess){
            std::cout << "Failed to convert image: " << path << std::endl;
            ilBindImage(NULL);
            ilDeleteImage(image);
            return 0;
    }
   
    GLuint texture;
    glGenTextures(1, &texture);
   
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), ilGetInteger(IL_IMAGE_TYPE), ilGetData());
    glBindTexture(GL_TEXTURE_2D, 0);
   
    ilDeleteImage(image);
    return texture;
}