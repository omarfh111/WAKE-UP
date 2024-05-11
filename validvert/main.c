/**
* @file main.c
* @brief Testing Program.
* @author wake up
* @version 0.1
* @date 5,2,2015
*
* test main.c
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "perso.h"
#include "background.h"
#include "enemy.h"
#include "constants.h"
#include "minimap.h"


void main(){
    bg bg,mask;
    perso p1;
    enemy e;
    Minimap minimap;

    int q=1;
    int scrollLeft = 0; // Flag for left scrolling
    int scrollRight = 0; // Flag for right scrolling
    int resizingFactor=4;
  
    SDL_PumpEvents();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/score.ttf", 24);
    
    
    int tempsDebut = SDL_GetTicks(); 
    int dureeTotale = 180 * 1000; 
    SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
    init_perso(&p1); 
    initEnemy(&e);
    SDL_Event event;
    initbg(&bg);
    initmask(&mask);
    InitializeMinimap(&minimap, screen, 1000, 188);
/*
	SDL_Surface *dotImage1 = NULL;
    SDL_Surface *dotImage2 = NULL;
        dotImage1 = IMG_Load("p1.png");
    if (!dotImage1) {
    printf("Failed to load image: %s\n", IMG_GetError());

}
    dotImage2 = IMG_Load("p2.png");
    if (!dotImage2) {
    printf("Failed to load image: %s\n", IMG_GetError());

}*/

  

    while (q) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                q = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 1; // Set left scroll flag when left arrow is pressed
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 1; // Set right scroll flag when right arrow is pressed
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 0; // Clear left scroll flag when left arrow is released
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 0; // Clear right scroll flag when right arrow is released
                        break;
                }
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        if (scrollLeft) {
            scrolling(&bg, 1, p1.pos.x, 0);
            scrolling(&mask, 1, p1.pos.x, 0); // Scroll left continuously
        }
        if (scrollRight) {
            scrolling(&bg, 0, p1.pos.x, 0);
            scrolling(&mask, 0, p1.pos.x, 0); // Scroll right continuously
        }
	
	afficherbg(&mask, screen);
        //afficherbg(&bg, screen);
        SDL_Delay(60);
        afficher_perso(p1, screen);
        afficher_score_vie(p1, screen, 0);
        animer_perso(&p1);
        drawEnemy(screen, e);
       // move_perso(&p1);
        //saut_perso(&p1);
        
        
   /*  hethi collision mich partfaite fi jorrit el mask  */  
          
           if (!CollisionHorizontale(mask.img, p1.pos)) {
        move_perso(&p1);
        saut_perso(&p1);
    }
    else
    {
    p1.pos.x=p1.pos.x-1;
    }
    if(CollisionVerticale(mask.img, p1.pos))
    {
    printf("collision hoz");
      move_perso(&p1);
      saut_perso(&p1);
      p1.pos.y -= 2;
     }
    
 
    
    printf("Player position: X = %d, Y = %d\n", p1.pos.x, p1.pos.y);

        if (p1.pos.x < 40) { 
            player_limite(&p1, screen);
            p1.pos.x = 40;
        }
        if (p1.pos.x > 3700) { 
            player_limite(&p1, screen);
            p1.pos.x = 3700;
        }

        updateEnemy(&e, p1.pos);
        
        UpdateMinimap(&minimap, p1.pos, resizingFactor, screen->w, screen->h);
        DisplayMinimap(&minimap, screen);

        afficherTempsLevel(tempsDebut, dureeTotale, screen, font);

        SDL_Flip(screen);
        SDL_Delay(10); 
    }

    FreeMinimap(&minimap);
    SDL_Quit();
}
