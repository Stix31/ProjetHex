#ifndef GLOBALS_H
#define GLOBALS_H
#define WINHI 600 // window height
#define WINWI 800 // window width
#define GRID_POS_X (WINWI-524)/2
#define GRID_POS_Y (WINHI-319)/2

#include "view.h"
#include "grid.h"

SDL_Surface *screen, *red, *blue, *hover, *hred, *hblue, *cursorgif[4];

SDL_Surface *x, *y, *xy;

int cursorX, cursorY;

int mode, player;

#endif
