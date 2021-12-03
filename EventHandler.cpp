#include "EventHandler.h"

void EventHandler::EventBlockMain()
{
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			quit = 1;
			return;
		}
		if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
			int x, y; 
			SDL_GetMouseState(&x, &y);

			if () {


			}
		}

	}
}
