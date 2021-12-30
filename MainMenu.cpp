#include "MainMenu.hpp"
#include "Object.h"
#include<iostream>
//for Rendering 
SDL_Surface* mloadimage,*mtemp ; 
SDL_Rect mboardsrc, mboarddest ;
Object* mbg;
SDL_Rect btn1 = {200,200,100,100} ;    SDL_Rect btn2  = {50, 50, 100, 80 }; ; 


//For mouse movemnet 
bool mlmb = false; // left mouse button
SDL_Point mmousepointer ;
SDL_Rect* mhitbox ; 
SDL_Point mclickoffset;
int mcurrx,mcurry;  


//For State Machine 
bool misclicked = 0 ; 



//Class methods 
MainMenu::MainMenu(){}
MainMenu::~MainMenu(){}
void MainMenu::init(const char* title,int xcord,int ycord,int width,int height)
{
     if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        
            std::cout<<"Subsys_init Menu\n";
            window = SDL_CreateWindow(title,xcord,ycord,width,height,0);

            if(window){
                std::cout<<"Menu Window is working\n"; 
            }
            renderer = SDL_CreateRenderer(window,-1,0);
            if(renderer){
                std::cout<<"Menu Successful rendering of window\n";
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                run = true ;     

            }
            else{
                run = false ;
            }
            
    }
    mbg = new Object("textures/Mainscr.jpg",renderer,0,0);

}

void MainMenu::updatescr()
{
    mbg->UpdateMainMenu(600,800);
}
void MainMenu::renderscr(){
    SDL_RenderClear(renderer); 
    mbg->Render();
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &btn1);
    SDL_RenderPresent(renderer);
}
void MainMenu::cleanscr(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout<<"MAIN MENU DEAD\n";
}
bool MainMenu::rungame(){return run; }

void MainMenu::EventHandling(){
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        run = false;
        break; 
        
    case SDL_MOUSEMOTION:
        mmousepointer = {event.motion.x,event.motion.y};
        cout<<mmousepointer.x<<" "<<mmousepointer.y<<"\n";
                
                    
            
                
        break;
    case SDL_MOUSEBUTTONUP:
      


        if(mlmb and event.button.button ==SDL_BUTTON_LEFT)
                {
                    mlmb = false ;
                   
                }
        break ; 
                
    case SDL_MOUSEBUTTONDOWN:
                if(!mlmb && event.button.button == SDL_BUTTON_LEFT)
                {
                    mlmb = true ;
                    //play btn 

                    if(SDL_PointInRect(&mmousepointer,&btn1)){
                        mhitbox = &btn1;
                        this->snum = 1 ;
                        cout<<"click succesfull\n";
                        break; 
                        
                       
                    }

                     if(SDL_PointInRect(&mmousepointer,&btn2)){
                        mhitbox = &btn2;
                        //add help btn 
                        //this->snum = 1 ;
                        cout<<"click succesfull btn2\n";
                        break; 
                        
                       
                    }
                
                }
                break;
            
                
    default:
            break; 
            

    }
}
void MainMenu:: setHighScore(float score){}
void MainMenu::setStrikerPosition(int player){}