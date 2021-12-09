#include"Object.cpp"
class Coin : public Object{
    public:
        Vector vel, acc;
        float mass, radius;

    public:
        Coin(const char* texturename, SDL_Renderer* ren, int x, int y, int r, float mass) : Object( texturename, ren,  x,  y){
            this->radius = r;
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
            

        }
        void move(){
            if (this->vel.getMagnitute() < 0.005) this->vel.set(0,0);
                this->pos = this->pos.add(this->vel);
                this->pos = this->pos.add(this->vel);
                this->vel = this->vel.multiply(0.98);
        }
        friend class Game; 
};
