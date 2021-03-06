#pragma once 
#include<SDL2/SDL.h>
#include "Vector.cpp"
class Object{
public :
    Object(const char* texturename, SDL_Renderer* ren,int x,int y);
    ~Object() ; 
    void Update(float, float);
    void UpdateBoard(float , float );
    void Render(); 
    Vector pos ; 
    void UpdateMainMenu(float,float); 
    

protected:
   

    SDL_Texture* obj;
    SDL_Rect srcRect,destRect;
    SDL_Renderer* renderer; 
    friend class Game ;

};