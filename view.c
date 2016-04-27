#include <SDL/SDL_image.h>
#include "view.h"
#include "globals.h"

Button initButton(TTF_Font* font, char* text, SDL_Rect rect){
	Button b;
	b.s= SDL_CreateRGBSurface(32,rect.w,rect.h,32,0,0,0,0);
	SDL_FillRect(b.s,NULL,SDL_MapRGB(b.s->format,0,140,0));
	b.text=TTF_RenderText_Blended(font,text,(SDL_Color){0,0,0});
	b.rect=rect;
	return b;
}

void blitImage(SDL_Surface* s, SDL_Surface* ss, int x, int y){
	SDL_Rect p; p.x=x; p.y=y;
	SDL_BlitSurface(s,NULL,ss,&p);
}

void blitButton(Button b){
	blitImage(b.text,b.s,0,0);
	blitImage(b.s,screen,b.rect.x, b.rect.y);
}

void updateHover(Grid *g, SDL_Rect pos){
	if(pos.x<0 || pos.y<0 || pos.x>=GRID_SIZE || pos.y>=GRID_SIZE) g->posH.x=-1;
	else{
		if(!g->cell[pos.x][pos.y])g->h=hover;
		else if(g->cell[pos.x][pos.y]==1)g->h=hblue;
			else g->h=hred;
		g->posH.x=19+pos.x*30+pos.y*15;
		g->posH.y=19+pos.y*25;
	}
}

void highLight(Grid *g, CellBlock cb){
	int i, w, h;
	for(i=0;i<cb.content;i++){
		w=cb.x[i]; h=cb.y[i];
		if(w==GRID_SIZE-1 || g->cell[w][h] != g->cell[w+1][h]) blitImage(x,g->b,w*30+h*15+48,h*25+25);
		if(h==GRID_SIZE-1 || g->cell[w][h] != g->cell[w][h+1]) blitImage(y,g->b,w*30+h*15+33,h*25+43);
		if(w==0 || g->cell[w][h] != g->cell[w-1][h]) blitImage(x,g->b,w*30+h*15+17,h*25+25);
		if(h==0 || g->cell[w][h] != g->cell[w][h-1]) blitImage(y,g->b,w*30+h*15+17,h*25+18);
		if((w==GRID_SIZE-1 && h==0) || g->cell[w][h] != g->cell[w+1][h-1]) blitImage(xy,g->b,w*30+h*15+33,h*25+17);
		if((w==0 && h==GRID_SIZE-1) || g->cell[w][h] != g->cell[w-1][h+1]) blitImage(xy,g->b,w*30+h*15+18,h*25+43);
	}
}

void update(Grid *g){
	updateHover(&(*g),gridCursorPosition());
	if(g->posH.x!=-1 && mode!=2) blitImage(g->h,g->bh,g->posH.x, g->posH.y);
	blitImage(g->bh,screen,GRID_POS_X, GRID_POS_Y);
}
void mouse(SDL_Surface** s){
    int time = SDL_GetTicks() / 250;
    SDL_ShowCursor(0);
    int xMouse, yMouse;
    SDL_GetMouseState(&xMouse,&yMouse);
    //printf("x: %d ; y: %d\n",xMouse, yMouse);
    if (yMouse > 138 && yMouse < 431 && xMouse < 635 && xMouse > 136)
        blitImage(s[time%4], screen, xMouse, yMouse);
}