#include "Game.h"
// #include "Coin.cpp"
// #include "Board.cpp"
#include "Collision.cpp"
#include <iostream>
#include <fstream>

//Scoring System 
int cpu_moves; int player_moves ;
int cpu_score; int player_score;


//for Rendering 
SDL_Surface* loadimage,*temp ; 
Board* bg; 
Coin* striker; Coin *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8; Coin* c0; 
SDL_Rect boardsrc, boarddest ;
Vector direction ;


//For mouse movemnet 
bool lmb = false; // left mouse button
SDL_Point mousepointer ;
SDL_Rect* hitbox ; 
SDL_Point clickoffset;
int currx,curry;  


//For State Machine 
int STATE = 1, prevState = 1;
bool isclicked = 0 ; 


//Class methods 
Game::Game()
{}
Game::~Game()
{}
void Game:: init(const char* title,int xcord,int ycord,int width,int height){
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        
            std::cout<<"Subsys_init\n";
            window = SDL_CreateWindohttps://github.com/hardik5k/iCarrom.gitw(title,xcord,ycord,width,height,0);
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
    c1 = new Coin("textures/black1.png",renderer,258,301,17, 10,10);
    c5 = new Coin("textures/white1.png",renderer,266,267,17, 10,20);
    c2 = new Coin("textures/black2.png",renderer,299,257,17, 10,10);
    c6 = new Coin("textures/white2.png",renderer,332,267,17, 10,20);
    c3 = new Coin("textures/black3.png",renderer,342,301,17, 10,10);
    c7 = new Coin("textures/white2.png",renderer,333,335,17, 10,20);
    c4 = new Coin("textures/black4.png",renderer,299,343,17, 10,10);
    c8 = new Coin("textures/white2.png",renderer,265,335,17, 10,20);
    c0 = new Coin("textures/gold.png",renderer,300,300,17,10,50);
    bg->coins.push_back(striker);
    bg->coins.push_back(c1);
    bg->coins.push_back(c2);
    bg->coins.push_back(c3);
    bg->coins.push_back(c4);
    bg->coins.push_back(c5);
    bg->coins.push_back(c6);
    bg->coins.push_back(c7);
    bg->coins.push_back(c8);
    bg->coins.push_back(c0);
    bg->coinsOnBoard.push_back(striker);
    bg->coinsOnBoard.push_back(c1);
    bg->coinsOnBoard.push_back(c2);
    bg->coinsOnBoard.push_back(c3);
    bg->coinsOnBoard.push_back(c4);
    bg->coinsOnBoard.push_back(c5);
    bg->coinsOnBoard.push_back(c6);
    bg->coinsOnBoard.push_back(c7);
    bg->coinsOnBoard.push_back(c8);
    bg->coinsOnBoard.push_back(c0); 


}

void Game::setStrikerPosition()
{
    if(prevState == 1)
    {
        return;
    }
    else
    {
        striker->pos.x = 140;
        striker->pos.y = 490;
    }
}

void Game::EventHandling(){
    SDL_Event event; 
    SDL_PollEvent(&event);
    if(STATE==0) //Striker set
    {
        switch(event.type){
            case SDL_QUIT:
                run = false;
                break;
            case SDL_MOUSEMOTION:
                mousepointer = {event.motion.x,event.motion.y};
                // std::cout<<mousepointer.x<<" "<<mousepointer.y<<"\n";
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
                    delete hitbox; 
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

    if(STATE == 1)
    {
        setStrikerPosition();
        prevState = 1; 
        
        switch(event.type)
        {
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                        if(striker->pos.getX()<459)
                        {
                            std::cout << "Right" << std::endl;
                            striker->pos.set(striker->pos.getX() + 4, striker->pos.getY());
                            std::cout << striker->pos.getX() << std::endl;
                        }
                        break;

                    case SDLK_LEFT:
                        if(striker->pos.getX()>141)
                        {
                            striker->pos.set(striker->pos.getX() - 4, striker->pos.getY());
                        }
                        break;

                    case SDLK_RETURN:
                        cout << "Enter pressed" << endl;
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
        prevState = 1;
       
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
        prevState = 2;
        switch(event.type)
        {
            case SDL_QUIT:
                run = false;
                break;
            default:
              if (direction.x!=-1){
                for (int i = 0; i  < bg->coinsOnBoard.size(); i++){
                    Coin* coin1 = bg->coinsOnBoard[i];
                    coin1->move();
                    resolveCollisionWithBoard(bg, coin1);
                    resolveParticleInHoles(coin1, bg);
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
                    STATE = 1;
                } 
                // resolveCollisionWithBoard(bg, striker);
                // resolveCollisionWithBoard(bg, c);
                // resolveCollisionWithCoins(striker, c);
                break; 
            }
               
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
    // striker->Render();
    // c1->Render();
    // c2->Render();
    // c3->Render();
    // c4->Render();
    // c5->Render();
    // c6->Render();
    // c7->Render();
    // c8->Render();
    // c0->Render(); 
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