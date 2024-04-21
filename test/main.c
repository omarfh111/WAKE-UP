#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "perso.h"
#include "background.h"
void main(){
bg bg;
perso p1;
int q=1;
int scrollLeft = 0; // Flag for left scrolling
int scrollRight = 0; // Flag for right scrolling


SDL_PumpEvents();
SDL_Init(SDL_INIT_EVERYTHING);
TTF_Init();
SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
init_perso( & p1); 
SDL_Event event;
initbg(&bg);

 while (q) {
        while (SDL_PollEvent(&event)) {
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
                        /*
                    case SDLK_UP:
                        scrolling(&bg, 2, 0, 10); // Scroll up
                        break;
                        
                    case SDLK_DOWN:
                        scrolling(&bg, 3, 0, 10); // Scroll down
                        break;*/
                    //default:
                        //break;
                        
                        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	   if (scrollLeft) {
            scrolling(&bg, 1, 10, 0); // Scroll left continuously
        }
        if (scrollRight) {
            scrolling(&bg, 0, 10, 0); // Scroll right continuously
        }
        // Display background
        afficherbg(&bg, screen);
                    SDL_PumpEvents();
		    SDL_Delay(60);
		    afficher_perso(p1, screen);
		    afficher_score_vie(p1, screen, 0);
		    animer_perso( & p1);
		    move_perso( & p1);
		    saut_perso( & p1);
		    player_limite(&p1,screen);
		    
		    
		     // Clear screen
        

        // Update screen
        SDL_Flip(screen);

        // Delay to control frame rate
        SDL_Delay(10);
        
        }
        
        //Mix_FreeMusic(bgMusic);
        
    	SDL_Quit();   
    	}



