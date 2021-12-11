#include"Object.cpp"

class Coin : public Object{
    private:
        Vector vel, acc;
        float mass, radius;
        static int id;
        int coinID;
        int coinScore; 
    public:
        Coin();
        ~Coin(); 
        void move();

    friend class Game;
    friend class CollisionResolver;

};
