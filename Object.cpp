#include "Object.h"
#include "TextureLoader.cpp"

Object::Object(const char* texturename, SDL_Renderer* ren, int x, int y){
    renderer = ren;
    obj = Texture::LoadTexture(texturename,ren);
    pos.set(x,y);
}
Object::~Object()  {}
void Object::Update(float h, float w)
{
    
    //return an int by some manner 
    // xcord = ;
    // ycord = ;
    srcRect.h = h;
    srcRect.w = w;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = pos.getX() - w/2;
    destRect.y = pos.getY() - h/2;  
    destRect.h = h;
    destRect.w = w;
    


}
void Object::UpdateBoard(float h, float w)
{
    
    //return an int by some manner 
    // xcord = ;
    // ycord = ;
    srcRect.h = h;
    srcRect.w = w;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = pos.getX();
    destRect.y = pos.getY();
    destRect.h = h;
    destRect.w = w;
    


}
void Object::Render()
{
    SDL_RenderCopy(renderer,obj,&srcRect,&destRect);

}