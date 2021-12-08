#include"Object.cpp"
class Coin : public Object{
    protected:
        Vector vel, acc;
        float mass, radius;

    public:
        Coin(const char* texturename, SDL_Renderer* ren, int x, int y, int r, float mass) : Object( texturename, ren,  x,  y){
            this->radius = r;
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
        }
        friend class Game; 
};
