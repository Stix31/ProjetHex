
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Save.h"

void saveString(int x,int y, int player, char* turn){
    sprintf(turn, "%d,%d,%d\n",player,x,y);
}

void saveTurn (int x,int y, int player, int mode)
{
    FILE* fHistorique = fopen("historique.sav", "a");
    if (!fHistorique){
        /* mode == 1 -> sauvegarde / mode != 1 -> charge */
        if (mode == 1){
            char turn[16];
            saveString(x,y,player,turn);
            printf("turn %s\n",turn);
            fputs(turn, fHistorique);
        }
    }
    fclose(fHistorique);
}
