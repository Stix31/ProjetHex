#include "input.h"
#include "globals.h"
#include <stdio.h>
#include <SDL/SDL.h>
void input(){
	SDLKey key_pressed;
	SDL_WaitEvent(&event);
	switch (event.type){
		case SDL_MOUSEMOTION:
			//printf("Ça bouge\n");
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT){
				int clicX = event.motion.x;
				int clicY = event.motion.y;
				printf("X=%d Y=%d\n",clicX,clicY);
			}
			break;
		case SDL_KEYDOWN:
			key_pressed = event.key.keysym.sym;
			switch (key_pressed){
				case SDLK_ESCAPE:
					end=1;
					break;
				case SDLK_LEFT:
					printf("left +1\n");
					break;
				case SDLK_RIGHT:
					printf("right +1\n"); 
					break;
				case SDLK_UP:
					printf("up +1\n");
					break;
				case SDLK_DOWN:
					printf("down +1\n");
					break;
				default: break;
			}
			break;
		case SDL_QUIT:
			end=1;
			break;
		default:
			break;
	}
}