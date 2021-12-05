#include "Game.h"
#include "Object.cpp"


#include <iostream>

SDL_Surface* loadimage,*temp ; 
Object* striker,*bg; 
SDL_Rect boardsrc, boarddest ;
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
    bg = new Object("textures/Board.png",renderer,0,0);
    striker = new Object("textures/black.png",renderer,300,300);
    
    


}
void Game::EventHandling(){
    SDL_Event event; 
    SDL_PollEvent(&event);

    switch(event.type){
        case SDL_QUIT:
            run = false;
            break;
        default:
            break;
    }
    




}

void Game:: updatescr(){
 
    
    striker->Update(34.33,34.33);
    bg->Update(600,600);
}
void Game:: renderscr(){
    SDL_RenderClear(renderer);
     
    bg->Render();
    striker->Render();
    
    //Add more stuff to render here 
    SDL_RenderPresent(renderer);
}
void Game:: cleanscr(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Window and game ded\n"; 
}

bool Game :: rungame(){return run;}