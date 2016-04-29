
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "globals.h"
#include "grid.h"
#include "Save.h"
#include <SDL/SDL.h>


void saveString(int x,int y, int player, char* turn){
	sprintf(turn, "%d,%d,%d\n",player,x,y);
}

/*void loadString(char* turn){
	sprintf(turn, "%d,%d,%d\n",player,x,y);
}
*/
void saveTurn (int x,int y, int player){
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "a");
	if (fHistorique != NULL){
		char turn[16];
		saveString(x,y,player,turn);
		printf("turn %s\n",turn);
		fputs(turn, fHistorique);
		fclose(fHistorique);
	}
}

void loadTurn (Grid *g) {
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "r");
	if (fHistorique != NULL){
		char turn[16], x[2], y[2];
		SDL_Rect p;
		while (fscanf(fHistorique, "%c,%c,%c\n", turn,x,y) != EOF){
			p.x=atoi(x); p.y=atoi(y);
			addToGrid(g,p);
			if(player)player=0; else player=1;
		}
	}
}
