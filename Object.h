#include<SDL2/SDL.h>
class Object{
public :
    Object(const char* texturename, SDL_Renderer* ren,int x,int y);
    ~Object() ; 
    void Update(int ,int);
    void Render(); 

private:
    int xcord;
    int ycord;

    SDL_Texture* obj;
    SDL_Rect srcRect,destRect;
    SDL_Renderer* renderer; 

};