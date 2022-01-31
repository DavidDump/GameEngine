#ifndef TEXTURE_H
#define TEXTURE_H

class Texture{
    private:
        unsigned int id;

    public:
        // Constructor - send the texture to a slot in the shader
        Texture(const unsigned char* imgData, int slot, int width, int height);

        // Bind texture
        void Bind();

        // Unbind texture
        void Unbind();
};

#endif