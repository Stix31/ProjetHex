#include "globals.h"
#include "grid.h"

SDL_Rect gridCursorPosition(){
	SDL_Rect pos;
	int x,y,j;
	y=cursorY-GRID_POS_Y-19; j=y;
	if(y<0)y-=25;
	y/=25;
	x=cursorX-GRID_POS_X-15*y-19;
	if(x<0)x-=30;
	if(j%25<=5){
		if(x%30 < 13-(j%25)*2) y--;
		else
			if(x%30 > 15+(j%25)*2){
				x+=30;
				y--;
			}
	}
	x/=30;
	pos.x=x; pos.y=y;
	return pos;
}

void initGrid(Grid *g){
	int i,j;
	for(i=0; i<GRID_SIZE; i++)
		for (j=0; j<GRID_SIZE; j++)
			g->cell[i][j]=0;
}

int inGrid(){
	SDL_Rect p=gridCursorPosition();
	return (p.x>=0 && p.y>=0 && p.x<GRID_SIZE && p.y<GRID_SIZE);
}

int emptyCell(Grid g, SDL_Rect p){
	return !g.cell[p.x][p.y];
}

void addToGrid(Grid *g, SDL_Rect p){
	g->cell[p.x][p.y]=player+1;
	blitImage(player?red:blue,g->b,p.x*30+p.y*15+19,p.y*25+19);
}

int blockContainsX(CellBlock cb, int x){
	int i;
	for(i=0;i<cb.content;i++)
		if(cb.x[i]==x) return 1;
	return 0;
}

int blockContainsY(CellBlock cb, int y){
	int i;
	for(i=0;i<cb.content;i++)
		if(cb.y[i]==y) return 1;
	return 0;
}

int blockContains(CellBlock cb, int x, int y){
	int i;
	for(i=0;i<cb.content;i++)
		if(cb.x[i]==x && cb.y[i]==y) return 1;
	return 0;
}

void addToBlock(Grid g, CellBlock *cb, int x, int y){
	if(g.cell[x][y]==player+1 && !blockContains(*cb,x,y)){
		cb->x[cb->content]=x;
		cb->y[cb->content]=y;
		cb->content++;
		if(x<GRID_SIZE-1) addToBlock(g,cb,x+1,y);
		if(y<GRID_SIZE-1) addToBlock(g,cb,x,y+1);
		if(x>0) addToBlock(g,cb,x-1,y);
		if(y>0) addToBlock(g,cb,x,y-1);
		if(x<GRID_SIZE-1 && y>0) addToBlock(g,cb,x+1,y-1);
		if(y<GRID_SIZE-1 && x>0) addToBlock(g,cb,x-1,y+1);
	}
}
