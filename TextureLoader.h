#pragma once 
#include<SDL2/SDL.h> 
#include<SDL2/SDL_image.h>
class Texture
{
public:
    static SDL_Texture* LoadTexture(const char* name, SDL_Renderer* r);

};