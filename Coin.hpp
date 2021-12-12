#include"Object.h"

class Coin : public Object{
    private:
        Vector vel, acc;
        float mass, radius;
        static int id;
        int coinID;
        int coinScore; 
        
    public:
        Coin(const char* texturename, SDL_Renderer* ren, int x, int y, int r, float mass, int coinscore);
        ~Coin(); 
        void move();

    friend class Game;
    friend class CollisionResolver;

};
