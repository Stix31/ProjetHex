#ifndef Save_h
#define Save_h

#include <stdio.h>

void saveString(int x,int y, int player, char* turn);

void saveTurn(int x,int y, int player);

void loadTurn (Grid *g);

#endif /* Save_h */
