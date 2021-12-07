#include"Vector.cpp"

class Coin{
    protected:
        Vector pos, vel, acc;
        float mass, radius;

    public:
        Coin(float x, float y, float r, float mass){
            pos.set(x, y);
            this->radius = r;
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
        }
        friend class Game ; 
};
