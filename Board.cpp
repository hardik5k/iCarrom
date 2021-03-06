#include <vector> 
#include "Coin.hpp"
#include "Board.hpp"
 Board::Board(const char* texturename, SDL_Renderer* ren, int x, int y) : Object( texturename, ren,  x,  y){
        Vector v1(20, 580);
        Vector v2(20, 20);
        Vector v3(580, 20);
        Vector v4(580, 580);
        sides.push_back(v1);
        sides.push_back(v2);
        sides.push_back(v3);
        sides.push_back(v4);

        Vector h1(40, 565);
        Vector h2(40,40);
        Vector h3(565, 40);
        Vector h4(565, 565);
        holes.push_back(h1);
        holes.push_back(h2);
        holes.push_back(h3);
        holes.push_back(h4);
 }