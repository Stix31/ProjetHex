#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "globals.h"
#include "input.h"
#include "grid.h"
#include "view.h"
#include "save.h"

int main(int argc, char *argv[]){
	SDL_ShowCursor(0);
	Uint32 initflags = SDL_INIT_VIDEO;
	Uint8  video_bpp = 32;

	if (SDL_Init(initflags)<0){
		fprintf(stderr, "SDL could not be initialized successfully : %s\n", SDL_GetError());
		return 1;
	}
	screen = SDL_SetVideoMode(WINWI, WINHI, video_bpp, SDL_HWSURFACE);
	if (!screen){
		fprintf(stderr, "Couldn't establish video mode %dx%dx%d : %s\n", WINHI, WINHI, video_bpp, SDL_GetError());
		SDL_Quit();
		return 2;
	}
	Grid g;
	initGrid(&g);
	wallpaper=IMG_Load("Images/wallpaper.jpg");
	TTF_Init();
	TTF_Font* fontMenu = TTF_OpenFont("arvo/Arvo-Regular.ttf",60);
	SDL_Rect posB; posB.x=250; posB.y=115; posB.w=260; posB.h=70;
	Button b[4];
	b[0] =initButton(fontMenu,"      pvp",posB); posB.y+=100;
	b[1] =initButton(fontMenu," 1 player",posB); posB.y+=100;
	b[2] =initButton(fontMenu,"     load",posB); posB.y+=100;
	b[3] =initButton(fontMenu,"     quit",posB);

	SDL_WM_SetCaption("Jeu de Hex", NULL);

	g.b=SDL_LoadBMP("Images/TMP/hex.bmp");
	g.bh=SDL_LoadBMP("Images/TMP/hex.bmp");
	SDL_SetColorKey(g.b,SDL_SRCCOLORKEY,SDL_MapRGB(g.b->format,150,150,150));
	SDL_SetColorKey(g.bh,SDL_SRCCOLORKEY,SDL_MapRGB(g.bh->format,150,150,150));
	red=IMG_Load("Images/red.png");
	blue=IMG_Load("Images/blue.png");
	hover=IMG_Load("Images/hover.png");
	hred=IMG_Load("Images/hover_red.png");
	hblue=IMG_Load("Images/hover_blue.png");
	x=IMG_Load("Images/x.png");
	y=IMG_Load("Images/y.png");
	xy=IMG_Load("Images/xy.png");
	SDL_Surface *cursorgif[4];
	cursorgif[0] = IMG_Load("Images/cursor1.png");
	cursorgif[1] = IMG_Load("Images/cursor2.png");
	cursorgif[2] = IMG_Load("Images/cursor3.png");
	cursorgif[3] = IMG_Load("Images/cursor4.png");
	mode=0; player=0;
	srand(time(NULL));
	while(input(&g,b)){
		int i;
		if(!mode){
			blitImage(wallpaper,screen,0,0);
			for(i=0; i<4; i++) blitButton(b[i]);
		}
		else{
			SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,150,150,150));
			update(&g);
			blitImage(g.b,g.bh,0,0);
		}
		mouse(cursorgif);
		SDL_Flip(screen);
	}

	//Clean up the SDL library
	SDL_FreeSurface(screen);
	SDL_FreeSurface(red);
	SDL_FreeSurface(blue);
	TTF_CloseFont(fontMenu);
	SDL_FreeSurface(hover);
	SDL_FreeSurface(hred);
	SDL_FreeSurface(hblue);
	TTF_Quit();
	SDL_Quit();
	return 0;
}
