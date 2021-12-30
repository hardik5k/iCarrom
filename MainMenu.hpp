#pragma once 
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "ScreenManager.hpp"
using namespace std; 
class Screens;
class Game;

class MainMenu : public Screens{

public :     
    MainMenu();
    ~MainMenu();

    void init(const char* title,int xcord,int ycord,int width,int height); 
    void updatescr();
    void setStrikerPosition(int);
    void renderscr();
    void cleanscr();
    bool rungame();
    void setHighScore(float score);
    void EventHandling(); 
    
    
private:
    bool run ;
    SDL_Window *window;
    SDL_Renderer * renderer ; 
};
