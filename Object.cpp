#include "Object.h"
#include "TextureLoader.cpp"

Object::Object(const char* texturename, SDL_Renderer* ren,int x,int y){
    renderer = ren;
    obj = Texture::LoadTexture(texturename,ren);
    xcord = x ;
    ycord = y ;
}
Object::~Object()  {}
void Object::Update(int x1,int y1)
{
    
    //return an int by some manner 
    // xcord = ;
    // ycord = ;
    srcRect.h = x1;
    srcRect.w = y1;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xcord;
    destRect.y = ycord; 
    destRect.h = x1;
    destRect.w = y1;
    


}
void Object::Render()
{
    SDL_RenderCopy(renderer,obj,&srcRect,&destRect);

}