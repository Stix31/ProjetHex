#ifndef Save_h
#define Save_h

#include <stdio.h>
#define TAILLE_MAX 100
void saveString(int x,int y, int player, char* turn);

void saveTurn(int x,int y, int player);

int loadTurn(Grid *g);

void UndoAction(Grid *g);

#endif /* Save_h */
