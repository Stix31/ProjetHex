
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Save.h"

void saveString(int x,int y, int player, char* turn){
    sprintf(turn, "%d,%d,%d\n",player,x,y);
}

void saveTurn (int x,int y, int player)
{
    FILE* fHistorique = NULL;
    fHistorique = fopen("historique.sav", "a");
    if (fHistorique != NULL){
      char turn[16];
      saveString(x,y,player,turn);
      printf("turn %s\n",turn);
      fputs(turn, fHistorique);
    }
    fclose(fHistorique);
}
