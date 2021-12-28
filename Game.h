#pragma once 
#include<SDL2/SDL.h>
#include "Coin.hpp"
class Game{

public :     
    Game();
    ~Game();

    void init(const char* title,int xcord,int ycord,int width,int height); 
    void updatescr();
    void setStrikerPosition(int);
    void renderscr();
    void cleanscr();
    bool rungame();
    void setHighScore(float score);
    void EventHandling(); 
    void updateScore(Coin*, int);
    
private:
    bool run ;
    SDL_Window *window;
    SDL_Renderer * renderer ; 

    

};