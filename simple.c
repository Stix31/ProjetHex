/* Simple program:  Create a blank window, wait for keypress, quit.
 
   Please see the SDL documentation for details on using the SDL API:
   /Developer/Documentation/SDL/docs.html
*/
  // sudo apt-get install libsdl1.2-dev libsdl-mixer1.2-dev libsdl-image1.2-dev libsdl-ttf2.0-dev
  
  // `sdl-config --cflags --libs` -lSDL -lSDL_Image -lSDL_TTF -lSDL_GFX -Wall simple.c
   // ajouter -lSDL_image pour la librairie SDL_image
   // ajouter -lSDL_ttf pour la librairie des fonts ttf

// Programme trouvé sur le web et sauvagement modifié par Vincent Dugat décembre 2015
   // ça fait beaucoup plus de chuose qu'à l'origine

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
 
//#include <SDL2/SDL.h> // ce serait pour la SDL 2
#include "SDL.h"
#include "SDL_keysym.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_rotozoom.h"
 
#define WINHI 600 // window height
#define WINWI 800 // window width

typedef struct
{
    int h, w;
}Dimensions;
int i = 302, j = 124, axeX = 0, axeY = 0;
SDL_Surface *ecran, *rectangle, *board, *texte1, *fondEcran, *pionBleu, *pionRouge; // quelques surfaces
SDL_Rect posBoard, posPionBleu, posPionRouge, posEcran;                     // sa position

void Ecran ()
{
    SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran);
    SDL_BlitSurface(board,NULL,ecran,&posBoard);
    SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);
    SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);
}

int main(int argc, char *argv[])
{
    Uint32 initflags = SDL_INIT_VIDEO; // SDL_DOUBLEBUF;  /* See documentation for details */
    SDL_Surface *ecran, *rectangle, *board, *texte1, *fondEcran; // quelques surfaces

    Dimensions fenetre; // main window
   
    fenetre.h = WINHI;  // en pixels
    fenetre.w = WINWI;   

    Uint8  video_bpp = 32; // 32 bits de couleur

    Uint32 videoflags = SDL_HWSURFACE; // utiliser la mémoire vidéo

    Uint32 vert, rouge; // des variables pour des couleurs

    bool continuer; // pour la boucle principale des évènements
    
    SDL_Event event; // aussi
 
    /* Initialize the SDL library */
    if ( SDL_Init(initflags) < 0 )
    {
        fprintf(stderr, "N'arrive pas a` initialiser la SDL : %s\n", SDL_GetError());
        exit(1);
    }
 
    /* Set video mode */
    ecran = SDL_SetVideoMode(fenetre.w, fenetre.h, video_bpp, videoflags); // surface principale

    if (ecran == NULL)
    {
        fprintf(stderr, "N'arrive pas a` etablir mode video%dx%dx%d : %s\n", fenetre.w, fenetre.h, video_bpp, SDL_GetError());
        SDL_Quit();
        exit(2);
    }
    fondEcran = IMG_Load("Images/fondecran.jpg");
    vert = SDL_MapRGB(ecran->format,0,128,0); // c'est du vert
    rouge = SDL_MapRGB(ecran->format,255,0,0); // c'est du rouge
    
    posEcran.x = 0;
    posEcran.y = 0;
    
    SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran); // de la couleur dans le fond de la fenêtre principale
    SDL_WM_SetCaption("Jeu de Hex", NULL); // legende de la fenêtre

    // Une autre surface avec du texte
    TTF_Init();
    
    TTF_Font *fontMenu = TTF_OpenFont("CAC-Champagne/cac_champagne.ttf",60); // charger une fonte (un peu moche)
    SDL_Color fontBlack = {0,0,0};
    texte1 = TTF_RenderText_Blended(fontMenu,"Hello guys !",fontBlack);

    // encore une surface
    rectangle = SDL_CreateRGBSurface(initflags,225,80,video_bpp,0,0,0,0); // une autre surface pour inclure dans l'autre
    SDL_FillRect(rectangle,NULL,rouge); // un fond rouge

    // position des surfaces
    SDL_Rect posRect, posTexte1;
    posRect.x = 20;
    posRect.y = 80;

    posTexte1.x = 25;
    posTexte1.y = 85;

    SDL_BlitSurface(rectangle,NULL,ecran,&posRect); // on associe avec la fenêtre principale
    SDL_BlitSurface(texte1,NULL,ecran,&posTexte1); // idem pour superposer avec la précédente

    // Affichage du plateau de jeu
    board = IMG_Load("Images/hex.png");    // plateau de jeu la taille en pixels est celle de l'image
    posBoard.x = 280;
    posBoard.y = 100;
    SDL_BlitSurface(board,NULL,ecran,&posBoard); // on l'associe avec la surface principale

    // affichage du pion bleu
    pionBleu = IMG_Load("Images/button-blue22.png");
    posPionBleu.x = i;
    posPionBleu.y = j;
    SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);

    // Affichege du pion rouge
    pionRouge = IMG_Load("Images/button-red22.png");
    posPionRouge.x = 543;
    posPionRouge.y = 273;
    SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);

    SDL_Flip(ecran); //maj des surfaces
 
 // boucle des évènements
    continuer = true; // un furieux du c ferait plutôt une boucle infinie. Je préfère rester correct.
    SDLKey key_pressed ;
    while (continuer)
    {
        while ( SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_MOUSEMOTION:
                    printf("Ça bouge\n"); // sans intérêt, c'est juste pour montrer
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {   
                        int clicX = event.motion.x;
                        int clicY = event.motion.y;
                        printf("X=%d Y=%d\n",clicX,clicY); // on récupère les coordonnées du clic
                    }
                    break;
                case SDL_KEYDOWN:
                    key_pressed = event.key.keysym.sym; // on récupère la touche
                    switch (key_pressed)
                    {
                    case SDLK_ESCAPE: /* Esc keypress quits the app... */
                        continuer = false;
                        break;
                    case SDLK_LEFT:
                        printf("left +1\n"); // par exemple
                            if (axeX > 0)
                            {
                                posPionBleu.x = posPionBleu.x - 30;
                                axeX--;
                            }
                            SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran);
                            SDL_BlitSurface(board,NULL,ecran,&posBoard);
                            SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);
                            SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);
                        break;
                    case SDLK_RIGHT:
                        printf("right +1\n");
                            if (axeX < 10)
                            {
                                posPionBleu.x = posPionBleu.x + 30;
                                axeX++;
                            }
                            SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran);
                            SDL_BlitSurface(board,NULL,ecran,&posBoard);
                            SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);
                            SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);
                        break;
                    case SDLK_UP:
                        printf("up +1\n");
                            if (axeY > 0)
                            {
                                posPionBleu.y = posPionBleu.y - 25;
                                posPionBleu.x = posPionBleu.x - 15;
                                axeY--;
                            }
                            SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran);
                            SDL_BlitSurface(board,NULL,ecran,&posBoard);
                            SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);
                            SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);
                        break;
                    case SDLK_DOWN:
                        printf("down +1\n");
                            if (axeY < 10)
                            {
                                posPionBleu.y = posPionBleu.y + 25;
                                posPionBleu.x = posPionBleu.x + 15;
                                axeY++;
                            }
                            SDL_BlitSurface(fondEcran,NULL,ecran,&posEcran);
                            SDL_BlitSurface(board,NULL,ecran,&posBoard);
                            SDL_BlitSurface(pionBleu,NULL,ecran,&posPionBleu);
                            SDL_BlitSurface(pionRouge,NULL,ecran,&posPionRouge);
                        break;
                    case SDLK_RETURN:
                        printf("Rerturn");
                            SDL_Surface *Hexagone, *miniHexa;
                            Hexagone = IMG_Load("Images/bleu-hex.png");
                            SDL_Rect posMiniHexa;
                            posMiniHexa.x = posPionBleu.x - 2;
                            posMiniHexa.y = posPionBleu.y - 5;
                            miniHexa = rotozoomSurface(Hexagone, 0, 0.11, 1);
                            SDL_BlitSurface(miniHexa,NULL,ecran,&posMiniHexa);
                            
                    default:
                        break;
                    }
                    break;
                case SDL_QUIT:
                    continuer = false;
                    break;
                default:
                    break;
            }
        }
        // refresh screen
        // mettre ici tous les blit utiles s'il y a des changements dans les surfaces, board, nouveaux pions
        SDL_Flip(ecran); //maj des surfaces pour affichage
    }
    //
    /* Clean up the SDL library */
    SDL_FreeSurface(ecran);
    SDL_FreeSurface(rectangle);
    SDL_FreeSurface(board);
    TTF_CloseFont(fontMenu);
    SDL_FreeSurface(texte1);
    SDL_FreeSurface(fondEcran);
    TTF_Quit();
    SDL_Quit();
    return(0);
}
