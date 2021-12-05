#include"Circle.cpp"
#include <SDL2/SDL.h> 
class Coin : public Circle{
    protected:
        Vector vel, acc;
        float mass;
        SDL_surface* imagesrc ;

    public:
        Coin(float x, float y, float r, float mass,string res) : Circle(x, y, r){
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
            imagesrc = Texture::LoadTexture(res,renderer);
        }
};
