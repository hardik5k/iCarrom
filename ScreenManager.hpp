#pragma once 


using namespace std;
class Game; class MainMenu; 
class Screens{
    public:
    virtual void init(const char* title,int xcord,int ycord,int width,int height) = 0; 
    virtual void updatescr() = 0;
    virtual void setStrikerPosition(int) = 0;
    virtual void renderscr() = 0;
    virtual void cleanscr() = 0;
    virtual bool rungame() = 0;
    virtual void setHighScore(float score) = 0;
    virtual void EventHandling() = 0 ;
    friend void checkscreen(MainMenu* ,Game* ); 
    
    public:
    static int snum ; 

};
