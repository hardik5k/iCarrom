#include "Game.h"
#include "Coin.hpp"
#include "Board.hpp"
#include "Collision.cpp"
#include <iostream>
#include <fstream>


//Scoring System 
int cpu_moves = 0, player_moves = 0;
int cpu_total = 0, player_total = 0;
float cpu_score = 0, player_score = 0;
int current_player = 0; // 0 ---> user, 1 ---> computer
Vector start_striker_pos(140, 490);

//for Rendering 
SDL_Surface* loadimage,*temp ; 
Board* bg; 
Coin* striker, c0, c1, c2, c3, c4, c5, c6, c7, c8; 
SDL_Rect boardsrc, boarddest ;


//For mouse movemnet 
bool lmb = false; // left mouse button
SDL_Point mousepointer ;
SDL_Rect* hitbox ; 
SDL_Point clickoffset;
int currx,curry;  


//For State Machine 
int STATE = 1, prevState = 1;
bool isclicked = 0; 


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
    striker = new Coin("textures/striker.png",renderer,140,490,18, 15,-10);
    c1 = new Coin("textures/black1.png",renderer,258,301,17, 10, 10);
    c5 = new Coin("textures/white1.png",renderer,266,267,17, 10, 20);
    c2 = new Coin("textures/black2.png",renderer,299,257,17, 10, 10);
    c6 = new Coin("textures/white2.png",renderer,332,267,17, 10, 20);
    c3 = new Coin("textures/black3.png",renderer,342,301,17, 10, 10);
    c7 = new Coin("textures/white2.png",renderer,333,335,17, 10, 20);
    c4 = new Coin("textures/black4.png",renderer,299,343,17, 10, 10);
    c8 = new Coin("textures/white2.png",renderer,265,335,17, 10, 20);
    c0 = new Coin("textures/gold.png",renderer,300,300,17,10, 50);
    bg->coins.push_back(striker);
    bg->coins.push_back(c0);
    bg->coins.push_back(c1);
    bg->coins.push_back(c2);
    bg->coins.push_back(c3);
    bg->coins.push_back(c4);
    bg->coins.push_back(c5);
    bg->coins.push_back(c6);
    bg->coins.push_back(c7);
    bg->coins.push_back(c8);
    bg->coinsOnBoard.push_back(striker);
    bg->coinsOnBoard.push_back(c0); 
    bg->coinsOnBoard.push_back(c1);
    bg->coinsOnBoard.push_back(c2);
    bg->coinsOnBoard.push_back(c3);
    bg->coinsOnBoard.push_back(c4);
    bg->coinsOnBoard.push_back(c5);
    bg->coinsOnBoard.push_back(c6);
    bg->coinsOnBoard.push_back(c7);
    bg->coinsOnBoard.push_back(c8);
}

void Game:: setStrikerPosition(int current_player)
{
    if(prevState == 1)
    {
        return;
    }
    else
    {
        striker->pos.set(start_striker_pos.getX(), start_striker_pos.getY());
    }
}

void Game:: updateScore(Coin* c, int score){
        if (!current_player){
            player_moves++; 
            player_total += score;
            player_score = (1.0 * player_total)/player_moves;
        }
        else{
            cpu_moves++;
            cpu_total += score;
            cpu_score = (1.0 * cpu_total)/cpu_moves;
        }
    return;
}

void Game::EventHandling(){
    SDL_Event event; 
    SDL_PollEvent(&event);

    if(STATE == 1)
    {
        setStrikerPosition(current_player);
        prevState = 1; 
        
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if(striker->pos.getX() < start_striker_pos.getX() - 1)
                        {
                            std::cout << "Right" << std::endl;
                            striker->pos.set(striker->pos.getX() + 4, striker->pos.getY());
                            std::cout << striker->pos.getX() << std::endl;
                        }
                        break;

                    case SDLK_LEFT:
                        if(striker->pos.getX() > start_striker_pos.getX() + 1)
                        {
                            striker->pos.set(striker->pos.getX() - 4, striker->pos.getY());
                        }
                        break;

                    case SDLK_RETURN:
                        cout << "Enter pressed" << endl;
                        prevState = STATE;
                        STATE = 2;
                        break;
                }
            break;

            case SDL_QUIT:
                run = false;
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
                    striker->vel.set(striker->vel.getX()/4, striker->vel.getY()/4);
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
                    isclicked = 1;

                
                }
                
            }
            
            break;
        default:
            break;
    }
        
}
    if(STATE == 3 ) 
    {
        prevState = 2;
        switch(event.type)
        {
            case SDL_QUIT:
                run = false;
                break;
            default:
                for (int i = 0; i  < bg->coinsOnBoard.size(); i++){
                    Coin* coin1 = bg->coinsOnBoard[i];
                    coin1->move();
                    resolveCollisionWithBoard(bg, coin1);
                    updateScore(coin1, resolveParticleInHoles(coin1, bg));
                    for (int j = 0; j  < bg->coinsOnBoard.size(); j++){
                        if (i != j){
                            Coin* coin2 = bg->coinsOnBoard[j];
                            resolveCollisionWithCoins(coin1, coin2);
                        }
                    }
                }
                int i = bg->coinsOnBoard.size();
                for (Coin* c: bg->coinsOnBoard){
                    if (c->vel.getMagnitute() == 0){
                        i--;
                    }
                }
                if (!i){
                    prevState = STATE;
                    STATE = 4;
                }
                break; 
               
        }

        

    }
}
    







void Game:: updatescr(){
    for (Coin* c : bg->coinsOnBoard){
        c->Update(2 * c->radius, 2 * c->radius);
    } 
    bg->UpdateBoard(600,600);
}
void Game:: renderscr(){
    SDL_RenderClear(renderer);
    
    
    bg->Render();
      for (Coin* c : bg->coinsOnBoard){
        c->Render();
    } 
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