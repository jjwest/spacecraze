#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

class Texture
{
public:
    Texture(SDL_Renderer* renderer, const std::string& path, float scale);
    Texture(const Texture&) = delete;
    Texture(Texture&&) = default;
    Texture& operator=(Texture&&) = default;
    Texture& operator=(const Texture&) = delete;
    ~Texture();
    SDL_Texture* getTexture() const;
    int getWidth() const;
    int getHeight() const;
    void setScale(float scale);

private:
    SDL_Texture* texture;
    int width;
    int height;
};

#endif
