#include "Game.h"
#include "Coin.hpp"
#include "Board.hpp"
#include "Collision.cpp"
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <fstream>


//Scoring System 
int cpu_moves = 0, player_moves = 0;
int cpu_total = 0, player_total = 0;
float cpu_score = 0, player_score = 0;
int current_player = 0; // 0 ---> user, 1 ---> computer
Vector start_striker_pos(140, 460);

//for Rendering 
SDL_Surface* loadimage,*temp ; 
Board* bg; 
Coin* striker, *c0, *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8, *ima; 
SDL_Rect boardsrc, boarddest ;
bool flag = false;
float x, y;

//For Rendering font
TTF_Font *font;
SDL_Color Black = {0, 0, 0};
SDL_Surface *surface_message, *surface_message2;
SDL_Texture *Message, *Message2;
SDL_Rect Message_rect, Message_rect2;
std::string str = "";

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
    TTF_Init();
    if(SDL_Init(SDL_INIT_EVERYTHING)==0){
        
            std::cout<<"Subsys_init\n";
            window = SDL_CreateWindow(title,xcord,ycord,width,height,0);

            if(window){
                std::cout<<"Window is working\n"; 
            }
            renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
            if(renderer){
                std::cout<<"Successful rendering of window\n";
                SDL_SetRenderDrawColor(renderer,255,255,255,255);
                run = true ;     

            }
            else{
                run = false ;
            }
    }

    font = TTF_OpenFont("Font2.otf", 20);
    if (!font)  printf("TTF_OpenFont: %s\n", TTF_GetError());

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
    if(bg->coinsOnBoard[0]->coinScore != -10){
        bg->coinsOnBoard.insert(bg->coinsOnBoard.begin(),striker);

    }
    if(current_player == 0)
        {   if(prevState == 1)
            {
                return;
            }
            else
            {
            striker->pos.x = 140;
            striker->pos.y = 490;
            }
        }
    
    else
    {
        if(prevState == 4)
        {
            return ;
        }
        else
        {
            striker->pos.x = 140;
            striker->pos.y = 110;

        }
    }
}

void Game:: updateScore(Coin* c, int score){
        if (!current_player){
            player_moves++; 
            player_total += score;
            //player_score = (1.0 * player_total)/player_moves;
        }
        else{
            cpu_moves++;
            cpu_total += score;
            //cpu_score = (1.0 * cpu_total)/cpu_moves;
        }
        //cout<<player_total<<endl ; 
    return;
}

void Game::EventHandling(){
    SDL_Event event; 
    SDL_PollEvent(&event);

    if(bg->coinsOnBoard[0]->coinScore ==-10 && bg->coinsOnBoard.size()<=1 ){
        //update highscore function 
        setHighScore(player_total);
        //run = false ;
        this->snum = 0;
        SDL_DestroyWindow(window); 

    }

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
                        if(striker->pos.getX() <459)
                        {
                            striker->pos.set(striker->pos.getX() + 4, striker->pos.getY());
                        }
                        break;

                    case SDLK_LEFT:
                        if(striker->pos.getX() >141)
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
                // run = false;

                this->snum = 0;
                SDL_DestroyWindow(window); 
                break;
            case SDL_WINDOWEVENT:
            if(event.window.event ==SDL_WINDOWEVENT_CLOSE)
            {
                current_player = 0;
                player_total = 0;
                cpu_total = 0 ;
                STATE = 1 ;
                prevState = 1;
                this->snum = 0;
                cout<<"Main game quit\n";
                SDL_DestroyWindow(window); 
                break;

            }
        }
    }

    if(STATE == 2)
    {
        switch(event.type){
        case SDL_QUIT:
            this->snum = 0;
            SDL_DestroyWindow(window);
            // run = false;
            break;
        case SDL_WINDOWEVENT:
            if(event.window.event ==SDL_WINDOWEVENT_CLOSE)
            {
                current_player = 0;
                player_total = 0;
                cpu_total = 0 ;
                STATE = 1 ;
                prevState = 1;
                // run = false;
                this->snum = 0;
                SDL_DestroyWindow(window); 
                cout<<"Main game quit\n";
                break;

            }
        case SDL_MOUSEMOTION:
            mousepointer = {event.motion.x,event.motion.y};
            if(lmb && hitbox !=NULL){
                hitbox->x = mousepointer.x-clickoffset.x;
                hitbox->y = mousepointer.y-clickoffset.y;
                float m = (striker->pos.y - mousepointer.y)/(striker->pos.x - mousepointer.x);
                if(m>0 && mousepointer.y > striker->pos.y)
                {
                    x = striker->pos.x - 100*(1/sqrt(m*m + 1));
                    y = striker->pos.y - 100*(m/sqrt(m*m + 1));
                }
                else if(m>0 && mousepointer.y < striker->pos.y)
                {
                    x = striker->pos.x + 100*(1/sqrt(m*m + 1));
                    y = striker->pos.y + 100*(m/sqrt(m*m + 1));
                }
                else if(m<0 && mousepointer.y < striker->pos.y)
                {
                    x = striker->pos.x - 100*(1/sqrt(m*m + 1));
                    y = striker->pos.y - 100*(m/sqrt(m*m + 1));
                }
                else if(m<0 && mousepointer.y > striker->pos.y)
                {
                    x = striker->pos.x + 100*(1/sqrt(m*m + 1));
                    y = striker->pos.y + 100*(m/sqrt(m*m + 1));
                }
                ima = new Coin("textures/test.png", renderer, int(x), int(y), 17, 10, 0);
                flag = true;
                resolveCollisionWithBoard(bg, ima);
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
                    striker->vel.set(striker->vel.getX()/6, striker->vel.getY()/6);
                    STATE = 3 ; 
                    flag = false;
                    
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
                //run = false;
                this->snum = 0;
                SDL_DestroyWindow(window); 
                break;
            case SDL_WINDOWEVENT:
            if(event.window.event ==SDL_WINDOWEVENT_CLOSE)
            {
                current_player = 0;
                //run = false;
                player_total = 0;
                cpu_total = 0 ;
                STATE = 1 ;
                prevState = 1;
                this->snum = 0;
                SDL_DestroyWindow(window); 
                cout<<"Main game quit\n";
                break;

            }
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
                    if(current_player==1) {
                        STATE = 1;
                        current_player = 0 ;
                    } 
                    else{
                        STATE = 4;
                        current_player = 1 ; 
                        
                    }
                }                
                break; 
               
        }
        
        

    }

    if(STATE == 4 ) 
    {
        setStrikerPosition(current_player);
        prevState = 4 ; 
        srand(time(0));

        int randpos = rand()%(459-141+1) +141; 
        if(striker->pos.getX()<randpos){
            striker->pos.x+=0.02 ; 
        }
        else

        {   int randcoin = rand()%(bg->coinsOnBoard.size()-1)+1;
            cout<<randcoin<<endl  ; 
            Coin* c = bg->coinsOnBoard[randcoin] ; 
            Vector v  = c->pos.sub(striker->pos) ;
            cout<<v.getMagnitute()<<endl ; 
            striker->vel = v.normalize(); 
            striker->vel.set(striker->vel.getX()/6, striker->vel.getY()/6);
            STATE = 3; 
            cout<<"Should fire\n" ; 
        }
    }

}

void Game:: updatescr(){
    for (Coin* c : bg->coinsOnBoard){
        c->Update(2 * c->radius, 2 * c->radius);
    } 
    if(flag)
    {
        ima->Update(2*ima->radius, 2*ima->radius);
    }
    bg->UpdateBoard(600,600);
}
void Game:: renderscr(){
    SDL_RenderClear(renderer);
    
    
    bg->Render();
      for (Coin* c : bg->coinsOnBoard){
        c->Render();
    } 
    if(flag)
    {
        ima->Render();
    }

    //Rendering score for player1
    std::string newstr = "Player1: " + std::to_string(player_total);
    surface_message = TTF_RenderText_Solid(font, newstr.c_str(), Black);
    if (surface_message == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }
    
    Message = SDL_CreateTextureFromSurface(renderer, surface_message);
    if (Message == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }
    
    SDL_FreeSurface(surface_message);
    Message_rect.x = 600;
    Message_rect.y = 450;
    Message_rect.w = 200;
    Message_rect.h = 100;

    //Rendering score for player2
    std::string newstr2 = "Computer: " + std::to_string(cpu_total);
    surface_message2 = TTF_RenderText_Solid(font, newstr2.c_str(), Black);
    if (surface_message2 == NULL)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
    }

    Message2 = SDL_CreateTextureFromSurface(renderer, surface_message2);
    if (Message2 == NULL)
    {
        printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    SDL_FreeSurface(surface_message2);
    Message_rect2.x = 600;
    Message_rect2.y = 50;
    Message_rect2.w = 200;
    Message_rect2.h = 100;

    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);

    SDL_DestroyTexture(Message);
    SDL_DestroyTexture(Message2);
    //Add more stuff to render here 
    SDL_RenderPresent(renderer);
}
void Game:: cleanscr(){
    //SDL_DestroyTexture(Message);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout<<"Window and game ded\n"; 
}

void Game:: setHighScore(float score){
    
    cout<<"SetHigh "<<score<<"\n" ; 
    std::ofstream ofile("Leaderboard.txt");
    if (score > highestScore){
        ofile << score;
    }
    else{
        ofile << highestScore;
    }
}

float Game:: getHighScore()
{
    return highestScore;
}
void Game:: displayHighScore(){
     std::ifstream ifile("Leaderboard.txt");

    if (!ifile.is_open()){
        std:: cout<<"Could not fetch leaderboard" << std::endl;
        return;
    }
   
     cout<<" displayHighScore";
    ifile >> highestScore;
    cout<<highestScore;

}

bool Game :: rungame(){return run;}
