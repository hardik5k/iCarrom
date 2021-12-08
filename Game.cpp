#include "Game.h"
// #include "Coin.cpp"
// #include "Board.cpp"
#include "Collision.cpp"
#include <iostream>
#include <fstream>

//for Rendering 
SDL_Surface* loadimage,*temp ; 
Board* bg; 
Coin* striker;
Coin* c;
SDL_Rect boardsrc, boarddest ;
Vector direction ;
//For mouse movemnet 
bool lmb; // left mouse button
SDL_Point mousepointer ;
SDL_Rect* hitbox ; 
SDL_Point clickoffset;
int currx,curry;  
//For State Machine 
int STATE = 2 ;
bool isclicked = 0 ; 
//Class methods 
Game::Game()
{}
Game::~Game()
{}
void Game:: init(const char* title,int xcord,int ycord,int width,int height){
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        
            std::cout<<"Subsys_init\n";
            window = SDL_CreateWindow(title,xcord,ycord,width,height,0);
            if(window){
                std::cout<<"Window is working\n"; 
            }
            renderer = SDL_CreateRenderer(window,-1,0);
            if(renderer){
                std::cout<<"Successful rendering of window\n";
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                run = true ;     

            }
            else{
                run = false ;
            }
            
    }
    bg = new Board("textures/Board.png",renderer,0,0);
    striker = new Coin("textures/striker.png",renderer,285,282,17, 7);
    c = new Coin("textures/black.png",renderer,50,282,17, 7);
    
    


}
void Game::EventHandling(){
    SDL_Event event; 
    SDL_PollEvent(&event);
    if(STATE==1) //Striker set
    {
        switch(event.type){
            case SDL_QUIT:
                run = false;
                break;
            case SDL_MOUSEMOTION:
                mousepointer = {event.motion.x,event.motion.y};
                if(lmb && hitbox !=NULL){
                // hitbox->x = mousepointer.x-clickoffset.x;
                // hitbox->y = mousepointer.y-clickoffset.y;
                    striker->pos.x =mousepointer.x-clickoffset.x;
                    striker->pos.y = mousepointer.y-clickoffset.y;
                
                    std::cout<<striker->destRect.x<<" "<<striker->destRect.y<<"\n";
                }
                break;
            case SDL_MOUSEBUTTONUP:
      


                if(lmb and event.button.button ==SDL_BUTTON_LEFT)
                {
                    lmb = false ;
                    hitbox = NULL ;
                }
                break ; 
            case SDL_MOUSEBUTTONDOWN:
                if(!lmb && event.button.button == SDL_BUTTON_LEFT)
                {
                    lmb = true ;
                //add a for loop for all objects 

                    if(SDL_PointInRect(&mousepointer,&striker->destRect)){
                        hitbox = &striker->destRect ; 
                        clickoffset.x = mousepointer.x-striker->pos.x;
                        clickoffset.y = mousepointer.y-striker->pos.y;
                        std::cout<<clickoffset.x<<" "<<clickoffset.y<<"\n"; 
                    }
                
                }
            
                break;
            default:
                break;
            }
        }
    if(STATE == 2)
    {
        
       
        switch(event.type){
        case SDL_QUIT:
            run = false;
            break;
        case SDL_MOUSEMOTION:
            mousepointer = {event.motion.x,event.motion.y};
            if(lmb && hitbox !=NULL){
                hitbox->x = mousepointer.x-clickoffset.x;
                hitbox->y = mousepointer.y-clickoffset.y;
                
                
                
            }
            break; 
            
        case SDL_MOUSEBUTTONUP:

            if(lmb and event.button.button ==SDL_BUTTON_LEFT)
                {
                    SDL_GetMouseState(&currx,&curry);
                    std::cout<<currx<<" "<<curry<<"\n";  
                    lmb = false ;
                    hitbox = NULL ;
                    Vector temp(currx,curry);
                    striker->vel = striker->pos.sub(temp).normalize();
                    STATE = 3 ; 
                    
                }
                break ; 
        case SDL_MOUSEBUTTONDOWN:
            if(!lmb && event.button.button == SDL_BUTTON_LEFT)
            {
                 
                lmb = true ;
                if(SDL_PointInRect(&mousepointer,&striker->destRect)){
                    hitbox = &striker->destRect ; 
                    clickoffset.x = mousepointer.x-striker->pos.x;
                    clickoffset.y = mousepointer.y-striker->pos.y;
                    std::cout<<"Object hit\n";
                    isclicked = 1 ;

                
                }
                
            }
            
            break;
        default:
            break;
    }
        
}
    if(STATE==3) //Striker set
    {
        switch(event.type)
        {
            case SDL_QUIT:
                run = false;
                break;
            default:
              if (direction.x!=-1){
                if (striker->vel.getMagnitute() < 0.1) striker->vel.set(0,0);
                striker->pos = striker->pos.add(striker->vel);
                c->pos = c->pos.add(c->vel);
                resolveCollisionWithBoard(bg, striker);
                resolveCollisionWithBoard(bg, c);
                resolveCollisionWithCoins(striker, c);
                break; 
            }
               
        }

        

    }
}
    







void Game:: updatescr(){
 
    
    striker->Update(34.33, 34.33);
    bg->Update(600,600);
    c->Update(40, 40);
}
void Game:: renderscr(){
    SDL_RenderClear(renderer);
     
    bg->Render();
    striker->Render();
    c->Render();
    
    //Add more stuff to render here 
    SDL_RenderPresent(renderer);
}
void Game:: cleanscr(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Window and game ded\n"; 
}

void Game:: setHighScore(float score){
    std::ifstream ifile("Leaderboard.txt");

    if (!ifile.is_open()){
        std:: cout<<"Could not fetch leaderboard" << std::endl;
        return;
    }

    float highestScore;
    ifile >> highestScore;


    std::ofstream ofile("Leaderboard.txt");
    if (score > highestScore){
        ofile << score;
    }
    else{
        ofile << highestScore;
    }
}

bool Game :: rungame(){return run;}