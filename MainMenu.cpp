#include "MainMenu.hpp"
#include "Object.h"
#include <SDL2/SDL_ttf.h>
#include <iostream>
//for Rendering 
SDL_Surface* mloadimage,*mtemp ; 
SDL_Rect mboardsrc, mboarddest ;
Object* mbg;
SDL_Rect btn1 = {600,150,200,100} ;    SDL_Rect btn2  = {600, 400, 200, 100 };  SDL_Rect btn3  = {600, 280, 200, 100 };  


//For Rendering font
TTF_Font *font1;
SDL_Color Black1 = {0, 0, 0};
SDL_Surface *surface_message_play, *surface_message_exit,*surface_message_help;
SDL_Texture *message_play,*message_exit,*message_help;
SDL_Rect Message_rect3,Message_rect1, Message_rect4 ; 
std::string str1 = "";


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
    TTF_Init();
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
    font1 = TTF_OpenFont("Font2.otf", 20);
    if (!font1)  printf("TTF_OpenFont: %s\n", TTF_GetError());
    mbg = new Object("textures/mainscr.png",renderer,0,0);

}

void MainMenu::updatescr()
{
    mbg->UpdateMainMenu(600,600);
}
void MainMenu::renderscr(){
    SDL_RenderClear(renderer); 
    mbg->Render();
    //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    SDL_RenderFillRect(renderer, &btn1);
    SDL_RenderFillRect(renderer, &btn2);
    SDL_RenderFillRect(renderer, &btn3);
    
    // Rendering Play
    std::string newstr1 = "PLAY";
    surface_message_play = TTF_RenderText_Solid(font1, newstr1.c_str(), Black1);
    if (surface_message_play == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
    message_play = SDL_CreateTextureFromSurface(renderer, surface_message_play);
    if ( message_play== NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    
    SDL_FreeSurface(surface_message_play);
    Message_rect1.x = 600;
    Message_rect1.y = 150;
    Message_rect1.w = 200;
    Message_rect1.h = 100;

    // Rendering exit
    std::string newstr3 = "EXIT";
    surface_message_exit = TTF_RenderText_Solid(font1, newstr3.c_str(), Black1);
    if (surface_message_exit == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
    message_exit = SDL_CreateTextureFromSurface(renderer, surface_message_exit);
    if ( message_exit== NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    
    SDL_FreeSurface(surface_message_exit);
    Message_rect3.x = 600;
    Message_rect3.y = 400;
    Message_rect3.w = 200;
    Message_rect3.h = 100;
   //HELP 

       
    std::string newstr2 = "HELP";
    surface_message_help = TTF_RenderText_Solid(font1, newstr2.c_str(), Black1);
    if (surface_message_help == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
    message_help = SDL_CreateTextureFromSurface(renderer, surface_message_help);
    if ( message_help== NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    
    SDL_FreeSurface(surface_message_help);
    Message_rect4.x = 600;
    Message_rect4.y = 280;
    Message_rect4.w = 200;
    Message_rect4.h = 100;
    SDL_RenderCopy(renderer, message_play, NULL, &Message_rect1);
    SDL_RenderCopy(renderer, message_exit, NULL, &Message_rect3);
    SDL_RenderCopy(renderer, message_help, NULL, &Message_rect4);
    SDL_DestroyTexture(message_play);
    SDL_DestroyTexture(message_exit);
    SDL_DestroyTexture(message_help);
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
        //cout<<mmousepointer.x<<" "<<mmousepointer.y<<"\n";

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
                        this->snum = 2 ;
                        cout<<"click succesfull btn2\n";
                        break; 
                        
                       
                    }
                    if(SDL_PointInRect(&mmousepointer,&btn3)){
                        mhitbox = &btn3; 
                        
                        cout<<"click succesfull btn3\n";
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
