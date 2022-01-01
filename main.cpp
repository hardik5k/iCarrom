#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Game.h"
using namespace std;

#include "MainMenu.hpp"
#include "ScreenManager.hpp"
Game* game = NULL; 
MainMenu* mgame = NULL;
Screens* s = NULL ; 
int firsttime = 1 ; 


int main(int argc, const char* argv[]){
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 framestart ;
	int frametime ; 

	game = new Game();
	game->displayHighScore();

	mgame = new MainMenu();
	mgame->init("iCarrom",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600);
	
	s = (Screens*)mgame;
	while(s->rungame())
	{
		s->EventHandling();
		s->updatescr();
		s->renderscr();

		frametime = SDL_GetTicks()-framestart ; 
		if(frameDelay > frametime){
			SDL_Delay(frameDelay-frametime);
		}
		if(s->snum==0)
		{
			if(firsttime !=1)
				if(game->rungame()==false)
				{
				cout<<"IN THIS \n"; 
				game->cleanscr(); 
				}
			s=(Screens*)mgame;
			firsttime = 1;
		}
		else
		{
			if(firsttime==1)
			{
				if(s->snum==1)
				{
					game->init("iCarrom",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600);
					firsttime=-1;
				}
				else if(s->snum==2)
				{
					cout<<"exiting"<<endl;
					break;
				}
				s=(Screens*)game;
			}
		}
	}
	s->cleanscr(); 
	return 0 ;
}
