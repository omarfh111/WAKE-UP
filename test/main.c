/**
 * @file main.c
 * @brief the game loop code.
 * @author SASSI FATMA
 * @version 1.0
 * @date 08/5/2024
 */
// importing libraries
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "perso.h"
#include "background.h"
#include "enemy.h"
#include "constants.h"
#include "heart.h"
#include "boundingbox.h"

void main(){
bg bg;
perso p1;
enemy e;
int q=1;
int scrollLeft = 0;
int scrollRight = 0; 
int c=0;
int c1=0;
heart h;

SDL_PumpEvents();
SDL_Init(SDL_INIT_EVERYTHING);
TTF_Init();
SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
init_perso( & p1); 
initEnemy(&e);
SDL_Event event;
initbg(&bg);
inith(&h);

 while (q) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                q = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 1; 
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 1; 
                        break;
                }
            }
            }
             /*else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 0; // Clear left scroll flag when left arrow is released
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 0; // Clear right scroll flag when right arrow is released
                        break;
                    case SDLK_ESCAPE: 
                 	   q = 0; 
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
                        
                     /*   SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	   if (scrollLeft) {
            scrolling(&bg, 1, p1.pos.x,0.01); // Scroll left continuously
        }
        if (scrollRight) {
            scrolling(&bg, 0, p1.pos.x,0.01); // Scroll right continuously
        } */
        // Display background
        afficherbg(&bg, screen);
                    SDL_PumpEvents();
		    SDL_Delay(60);
		    afficher_perso(p1, screen);
		    afficher_score_vie(p1, screen, 0);
		    drawEnemy(screen,e);
		    drawh(screen,h);
		    animer_perso( & p1);
		    move_perso( & p1);
		    saut_perso( & p1);
		    player_limite(&p1,screen);
		    updateEnemy(&e, p1.pos);
		    SDL_Flip(screen);
		    c = collision(p1.pos, e.img_pos);
        if (c == 1){
            p1.vie -= 10;
            p1.score -= 10;
            if (p1.score <= 0) {
                printf("Game Over\n");
                q = 0;
            }
        }
        
        c1 = collision(p1.pos, h.pos);
        if (c1 == 1) {
            p1.vie += 10;
            p1.score += 10;
            h.pos.x = -100; 
            h.pos.y = -100;
        }

  
		    
		    
		    
        SDL_Flip(screen);

        
        SDL_Delay(10);
        
        }
        
        
      
        
    	SDL_Quit();   
    	}
