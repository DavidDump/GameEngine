#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include "debug.h"
#include "texture.h"

Texture::Texture(const unsigned char* imgData, int slot, int width, int height){
    GLCall(glGenTextures(1, &id));
    GLCall(glActiveTexture(slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, id));

    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData));
    GLCall(glGenerateMipmap(id));
}

void Texture::Bind(){
    GLCall(glBindTexture(GL_TEXTURE_2D, id));
}

void Texture::Unbind(){
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}