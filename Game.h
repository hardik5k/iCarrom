#include<SDL2/SDL.h>
#include"CollisionResolver.hpp"
class Game{

public :     
    Game();
    ~Game();

    void init(const char* title,int xcord,int ycord,int width,int height); 
    void updatescr();
    void renderscr();
    void cleanscr();
    bool rungame();
    void setHighScore(float score);
    void EventHandling(); 
    friend class Coin;
    
private:
    bool run ;
    CollsionResolver* cr;
    SDL_Window *window;
    SDL_Renderer * renderer ; 

    

};