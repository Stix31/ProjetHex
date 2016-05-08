#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "globals.h"
#include "grid.h"
#include "Save.h"
#include <SDL/SDL.h>


void saveString(int x,int y, int player, char* turn){
	sprintf(turn, "%d,%d,%d\n",player,x,y);
}

void saveTurn(int x,int y, int player){
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "a");
	if (fHistorique != NULL){
		char turn[16];
		saveString(x,y,player,turn);
		fputs(turn, fHistorique);
		fclose(fHistorique);
	}
}

int loadTurn(Grid *g) {
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "r");
	int m=0;
	if (fHistorique != NULL){
		int turn, x, y;
		fscanf(fHistorique, "%d,%d,%d\n", &m,&x,&y);
		while (fscanf(fHistorique, "%d,%d,%d\n", &turn,&x,&y) != EOF){
			SDL_Rect p; p.x=x;p.y=y;
			addToGrid(g,p);
			if(player)player=0; else player=1;
		}
		fclose(fHistorique);
	}
	return m;
}
