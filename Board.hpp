#pragma once 
#include <vector>
#include "Coin.hpp"
#include "Object.h"
class Board : public Object{
    public:
        std::vector<Vector> sides;
        std::vector<Coin*> coins; 
        std::vector<Coin*> coinsOnBoard; 
        std::vector<Vector> holes; 
        int width = 600, height = 600;  
    
        Board(const char* texturename, SDL_Renderer* ren, int x, int y) ;
        friend class Game;

};