
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

<<<<<<< HEAD
=======
void deleteSave (){
	if( access( "historique.sav", F_OK ) != -1 ) {
		FILE* fHistorique = NULL;
		fHistorique = fopen("historique.sav", "w");
		fclose(fHistorique);
	}
}

>>>>>>> 71b21431b1aa5d2c7797fe6dc2e4c0318a3d416b
void saveTurn (int x,int y, int player){
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "a");
	if (fHistorique != NULL){
		char turn[16];
		saveString(x,y,player,turn);
		fputs(turn, fHistorique);
		fclose(fHistorique);
	}
}

void loadTurn (Grid *g) {
	FILE* fHistorique = NULL;
	fHistorique = fopen("historique.sav", "r");
	if (fHistorique != NULL){
		char turn[1], x[2], y[2];
		SDL_Rect p;
		while (fscanf(fHistorique, "%c,%c,%c\n", turn,x,y) != EOF){
			p.x=atoi(x); p.y=atoi(y);
			addToGrid(g,p);
			if(player)player=0; else player=1;
		}
	}
}
