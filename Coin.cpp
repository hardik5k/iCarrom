#include"Circle.cpp"

class Coin : public Circle{
    protected:
        Vector vel, acc;
        float mass;

    public:
        Coin(float x, float y, float r, float mass) : Circle(x, y, r){
            this->mass = mass;
            this->vel.set(0 ,0);
            this->acc.set(0, 0);
        }
};
