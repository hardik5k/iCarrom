#pragma once 
#include<SDL2/SDL.h>
#include "Coin.hpp"
#include "ScreenManager.hpp"
class Game : public Screens{

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
    void displayHighScore();
    float getHighScore();
private:
    bool run ;
    SDL_Window *window;
    SDL_Renderer * renderer ; 
    float highestScore ; 
    

};