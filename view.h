#ifndef VIEW_H
#define VIEW_H
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "grid.h"

typedef struct{
	SDL_Surface* s;
	SDL_Surface* text;
	SDL_Rect rect;
}Button;

Button initButton(TTF_Font* font, char* text, SDL_Rect rect, int R, int G, int B);

void blitImage(SDL_Surface* s, SDL_Surface* ss, int x, int y);

void blitButton(Button b);

void highLight(Grid *g, CellBlock cb);

void update(Grid *g);

void updateHover(Grid *g, SDL_Rect pos);

void mouse(SDL_Surface** s);
#endif
