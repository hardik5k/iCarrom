#include<SDL2/SDL.h> 
class Texture
{
public:
    static SDL_Texture* LoadTexture(const char* name, SDL_Renderer* r);

};