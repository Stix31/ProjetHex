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

void UndoAction (Grid *g) {
	int lines=0, newLines=0;
	int endline;
	char turn[TAILLE_MAX] = "";
	FILE* fHistoriqueAncien = NULL;
	fHistoriqueAncien = fopen("historique.sav", "r");
	while(!feof(fHistoriqueAncien)) {
		endline = fgetc(fHistoriqueAncien);
  	if(endline == '\n') {
    	lines++;
  	}
	}
	rewind(fHistoriqueAncien);
	FILE* fHistoriqueNouveau = NULL;
	fHistoriqueNouveau = fopen("historique.sav~", "w");
	while(newLines < lines-1) {
		fgets(turn,TAILLE_MAX,fHistoriqueAncien);
		fputs(turn, fHistoriqueNouveau);
		printf("turn %s ligne %d\n",turn, lines);
		newLines++;
	}
	fclose(fHistoriqueAncien);
	remove("historique.sav");
	rename("historique.sav~", "historique.sav");
	fclose(fHistoriqueNouveau);
	printf("turn %s ligne %d\n",turn, lines);
  initGrid(g);
	g->b=SDL_LoadBMP("Images/TMP/Hex.bmp");
	//if (player) player=0;
	//else player=1;
	loadTurn(g);
}
