#ifndef GRID_H
#define GRID_H
#define GRID_SIZE 11
#include <SDL/SDL.h>

typedef struct{
	int cell[GRID_SIZE][GRID_SIZE];
	SDL_Surface* b;
	SDL_Surface* bh;
	SDL_Surface* h;
	SDL_Rect posH;
}Grid;

typedef struct{
	int x[61];
	int y[61];
	int content;
}CellBlock;

SDL_Rect gridCursorPosition();

int inGrid();

int emptyCell(Grid g, SDL_Rect p);

void initGrid(Grid *g);

void addToGrid(Grid *g, SDL_Rect p);

int blockContainsX(CellBlock cb, int y);

int blockContainsY(CellBlock cb, int y);

int blockContains(CellBlock cb, int x, int y);

void addToBlock(Grid g, CellBlock *cb, int x, int y);

#endif
