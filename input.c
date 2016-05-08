#include <SDL/SDL_image.h>
#include "input.h"
#include "grid.h"
#include "view.h"
#include "Save.h"

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
	int i;
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
<<<<<<< HEAD
							remove("historique.sav");
=======
>>>>>>> 71b21431b1aa5d2c7797fe6dc2e4c0318a3d416b
							mode=1;
							deleteSave();
						break;
						case 1:break;
						case 2:
							loadTurn(g);
							mode=1;
						break;
						case 3:
							return 0;
						default: break;
					}
				break;
				case 1:
					if(mode==2)break;
					if(inGrid() && emptyCell(*g,p)){
						addToGrid(&(*g),p);
						cb.content=0;
						addToBlock(*g,&cb,p.x,p.y);
						if((!player && blockContainsX(cb,0) && blockContainsX(cb,GRID_SIZE-1))||(player && blockContainsY(cb,0) && blockContainsY(cb,GRID_SIZE-1))){
							printf("%s wins\n",player? "red":"blue");
							highLight(g, cb);
							mode=2;
						}
						SDL_Rect gridpos=gridCursorPosition();
						saveTurn(gridpos.x,gridpos.y, player);
						if(player)player=0; else player=1;
					}
				break;
				default: break;
			}
		break;
		case SDL_KEYDOWN:
			key_pressed = event.key.keysym.sym;
			switch(key_pressed){
				case SDLK_ESCAPE: return 0;
				break;
				case SDLK_LEFT:
					addToBlock(*g,&cb,p.x,p.y);
				break;
				case SDLK_RIGHT:
					for(i=0;i<cb.content;i++) printf("%d %d\n", cb.x[i], cb.y[i]);
					printf("\n");
				break;
				case SDLK_UP: break;
				case SDLK_DOWN:
					cb.content=0;
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
