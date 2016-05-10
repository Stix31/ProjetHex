#include <SDL/SDL_image.h>
#include "input.h"
#include "grid.h"
#include "view.h"
#include "Save.h"

SDL_Rect last;

int inButton(Button b){
	return cursorX>=b.rect.x && cursorX<b.rect.x+b.rect.w && cursorY>=b.rect.y && cursorY<b.rect.y+b.rect.h;
}

int inWhichButton(Button *b){
	int i;
	for(i=0;i<4;i++){
		if(inButton(b[i])) return i;
	}
	return -1;
}

int input(Grid *g, Button *b){
	SDLKey key_pressed;
	SDL_Rect p=gridCursorPosition();
	SDL_Event event; SDL_WaitEvent(&event);
	CellBlock cb;
	switch(event.type){
		case SDL_MOUSEMOTION:
			cursorX = event.motion.x;
			cursorY = event.motion.y;
		break;
		case SDL_MOUSEBUTTONDOWN:
			switch(mode){
				case 0:
					switch(inWhichButton(b)){
						case 0:
							remove("historique.sav");
							mode=1;
							pvp=1;
							saveTurn(0,0, pvp);
						break;
						case 1:
							remove("historique.sav");
							mode=1;
							pvp=0;
							saveTurn(0,0, pvp);
						break;
						case 2:
							pvp=loadTurn(g);
							mode=1;
						break;
						case 3:
							return 0;
						default: break;
					}
				break;
				case 1:
					if (inButton(b[4])) {
						UndoAction(g);
						if (!pvp) UndoAction(g);
						break;
					};
					if(inGrid() && emptyCell(*g,p)){
						addToGrid(&(*g),p);
						cb.content=0;
						addToBlock(*g,&cb,p.x,p.y);
						if((!player && blockContainsX(cb,0) && blockContainsX(cb,GRID_SIZE-1))||(player && blockContainsY(cb,0) && blockContainsY(cb,GRID_SIZE-1))){
							printf("%s wins\n",player? "red":"blue");
							remove("historique.sav");
							highLight(g, cb);
							mode=2;
						}
						saveTurn(p.x,p.y, player);
						if(player)player=0; else player=1;
						if(!pvp && mode!=2){

							if(g->cell[5][0]!=2){p.x=5; p.y=0;}
							else{
								p.x=last.x; p.y=last.y;
								if(!g->cell[p.x][p.y+1]) p.y++;
									else if(!g->cell[p.x-1][p.y+1]){p.x--;p.y++;}
										else{
											CellBlock cbBlue; cbBlue.content=0;
											player=0;addToBlock(*g,&cbBlue,p.x,p.y+1);
											addToBlock(*g,&cbBlue,p.x-1,p.y+1);player=1;
											if(blockContainsX(cbBlue,10)){
												while(g->cell[p.x-1][p.y]==2)p.x--;
												if(!g->cell[p.x-1][p.y])p.x--;
												else if(!g->cell[p.x][p.y-1])p.y--;
													else
														if(!g->cell[p.x+1][p.y-1]){p.x++; p.y--;}
														else{
															while(g->cell[p.x+1][p.y-1]==2 && g->cell[p.x][p.y-1]==1){p.x++; p.y--;}
															p.y--;
														}
											}else{
												if(!g->cell[p.x+1][p.y])p.x++;
												else if(!g->cell[p.x+1][p.y-1]){p.x++; p.y--;}
													else if(!g->cell[p.x][p.y-1])p.y--;
														else{
															while(g->cell[p.x][p.y-1]==2 && g->cell[p.x+1][p.y-1]==1)p.y--;
															p.x++; y--;
														}
											}
										}
								
							}
							printf("%d %d\n", p.x, p.y);
							last.x=p.x; last.y=p.y;
							addToGrid(&(*g),p);
							cb.content=0;
							addToBlock(*g,&cb,p.x,p.y);
							if((!player && blockContainsX(cb,0) && blockContainsX(cb,GRID_SIZE-1))||(player && blockContainsY(cb,0) && blockContainsY(cb,GRID_SIZE-1))){
								printf("%s wins\n",player? "red":"blue");
								remove("historique.sav");
								highLight(g, cb);
								mode=2;
							}
							saveTurn(p.x,p.y, player);
							if(player)player=0; else player=1;
						}
					}
				break;
				case 2:
					mode=0;
					player=0;
					initGrid(g);
					g->b=SDL_LoadBMP("Images/TMP/hex.bmp");
				break;
				default: break;
			}
		break;
		case SDL_KEYDOWN:
			key_pressed = event.key.keysym.sym;
			switch(key_pressed){
				case SDLK_ESCAPE: return 0;
				break;
				default: break;
			}
		break;
		case SDL_QUIT:
			return 0;
		default:break;
	}
	return 1;
}
