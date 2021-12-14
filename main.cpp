#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include<SDL2/SDL_image.h>
#include "Game.cpp"
Game* game = NULL; 

int main(int argc, const char* argv[]){
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 framestart ;
	int frametime ; 

	game = new Game();
	game->init("iCarrom",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600);
	
	while(game->rungame()){
		game->EventHandling();
		game->updatescr();
		game->renderscr();

		frametime = SDL_GetTicks()-framestart ; 
		if(frameDelay > frametime){
			SDL_Delay(frameDelay-frametime);
		}



	}
	
	game->cleanscr(); 
	return 0 ;
}