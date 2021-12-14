#include <vector> 
#include "Coin.cpp"


class Board : public Object{
    public:
        std::vector<Vector> sides;
        std::vector<Coin*> coins; 
        std::vector<Coin*> coinsOnBoard; 
        std::vector<Vector> holes; 
        int width = 600, height = 600;  
    public:
    Board(const char* texturename, SDL_Renderer* ren, int x, int y) : Object( texturename, ren,  x,  y){
        Vector v1(20, 580);
        Vector v2(20, 20);
        Vector v3(580, 20);
        Vector v4(580, 580);
        sides.push_back(v1);
        sides.push_back(v2);
        sides.push_back(v3);
        sides.push_back(v4);

        Vector h1(40, 564);
        Vector h2(40,40);
        Vector h3(564, 40);
        Vector h4(564, 564);
        holes.push_back(h1);
        holes.push_back(h2);
        holes.push_back(h3);
        holes.push_back(h4);
        
    }
    friend class Game;

};