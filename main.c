#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "globals.h"
#include "input.h"
 
#define WINHI 600 // window height
#define WINWI 800 // window width

int main(int argc, char *argv[]){
	Uint32 initflags = SDL_INIT_VIDEO; //| SDL_DOUBLEBUF;  /* See documentation for details */
   
	Uint8  video_bpp = 32; // 32 bits de couleur

	Uint32 videoflags = SDL_HWSURFACE;

	Uint32 vert, rouge;
 
	if ( SDL_Init(initflags) < 0 ){
		fprintf(stderr, "SDL could not be initialized successfully : %s\n", SDL_GetError());
		exit(1);
	}
 
	/* Set video mode */
	SDL_Surface *ecran = SDL_SetVideoMode(WINWI, WINHI, video_bpp, videoflags); // surface principale

	if (ecran == NULL){
		fprintf(stderr, "Couldn't establish video mode %dx%dx%d : %s\n", WINHI, WINHI, video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}

	vert = SDL_MapRGB(ecran->format,0,128,0);

	SDL_FillRect(ecran,NULL,vert);
	SDL_WM_SetCaption("Jeu de Hex", NULL); // legende de la fenêtre

	TTF_Init();
	
	TTF_Font* fontMenu = TTF_OpenFont("arvo/Arvo-Regular.ttf",60);
	SDL_Color fontBlack = {0,0,0};
	SDL_Surface* texte1 = TTF_RenderText_Blended(fontMenu,"Test",fontBlack);

	SDL_Surface *rectangle = SDL_CreateRGBSurface(initflags,225,80,video_bpp,0,0,0,0);
	rouge = SDL_MapRGB(rectangle->format,255,0,0);
	SDL_FillRect(rectangle,NULL,rouge); // un fond rouge

	SDL_Rect posRect, posTexte1;
	posRect.x = 20;
	posRect.y = 80;

	posTexte1.x = 25;
	posTexte1.y = 85;

	SDL_BlitSurface(rectangle,NULL,ecran,&posRect);
	SDL_BlitSurface(texte1,NULL,ecran,&posTexte1);

	SDL_Surface* board = SDL_LoadBMP("Images/TMP/hex.bmp");
	SDL_Rect posBoard;
	posBoard.x = 270;
	posBoard.y = 100;
	SDL_BlitSurface(board,NULL,ecran,&posBoard);

	SDL_Surface *pionBleu;
	pionBleu = SDL_LoadBMP("Images/TMP/blue.bmp");
	SDL_Rect posPionBleu;               
	posPionBleu.x = 377;
	posPionBleu.y = 149;
	SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);

	// Affichege du pion rouge
	SDL_Surface *pionRouge = SDL_LoadBMP("Images/TMP/red.bmp");
	SDL_Rect posPionRouge;               
	posPionRouge.x = 543;
	posPionRouge.y = 273;
	SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);

	SDL_Flip(ecran); //maj des surfaces
	end=0;
	while(!end){
		SDL_Flip(ecran); //maj des surfaces
		input();
	}
		// refresh screen
	SDL_Flip(ecran); //maj des surfaces pour affichage
	//
	/* Clean up the SDL library */
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(rectangle);
	SDL_FreeSurface(board);
	TTF_CloseFont(fontMenu);
	SDL_FreeSurface(texte1);
	TTF_Quit();
	SDL_Quit();
	return(0);
}
