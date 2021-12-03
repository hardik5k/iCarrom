#pragma once
#include "SDL.h"
class EventHandler
{
private:
	int keyd, keyup;
	int rmbup, rmbd,lmbd,lmbup; 
	SDL_Event event;
	int quit; 
	 
public:
	int GameState;
	void EventBlockMain(); 
	
};

