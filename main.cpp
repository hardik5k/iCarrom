#include<bits/stdc++.h>
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Button.h"
#include "Holes.h"
#include "Sides.h"
#include<SDL2/SDL_image.h>
#include "Game.cpp"
Game* game = NULL; 

int main(int argc, const char* argv[]){
	game = new Game();
	game->init("iCarrom",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600);
	
	while(game->rungame()){
		game->EventHandling();
		game->updatescr();
		game->renderscr();

		}
	game->cleanscr(); 
	return 0 ;
}