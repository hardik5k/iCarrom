#include "TextureLoader.h"

SDL_Texture* Texture::LoadTexture(const char* name,SDL_Renderer* r){
    SDL_Surface* temp = IMG_Load(name);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(r,temp);
    SDL_FreeSurface(temp); 
    return tex ; 

}