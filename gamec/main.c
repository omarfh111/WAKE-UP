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
	
//declaration game
    bg bg,mask;
    perso p1,p2;
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
    int dureeTotale = 60 * 1000; 
    SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
    init_perso(&p1); 
    init_images_perso(&p1,"spritesheet.png");
    init_perso_controls(&p1);
    initEnemy(&e);
    SDL_Event event;
    initbg(&bg);
    initmask(&mask);
    InitializeMinimap(&minimap, screen, 1000, 188);


//declaration console menu
	int c;
	int c1;
	printf("1.solo\n2.multiplayer\n0.quitter\n");
	scanf("%d",&c);
	switch(c)
	{
		case 0:
			printf("bye");
			break;
		case 1:
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
         if (p2.pos.x < 40) { 
            player_limite(&p2, screen);
            p2.pos.x = 40;
        }
        if (p2.pos.x > 3700) { 
            player_limite(&p2, screen);
            p2.pos.x = 3700;
        }

        updateEnemy(&e, p1.pos);
        
        UpdateMinimap(&minimap, p1.pos, resizingFactor, screen->w, screen->h);
        DisplayMinimap(&minimap, screen);

        afficherTempsLevel(tempsDebut, dureeTotale, screen, font);
        if(event.key.keysym.sym==SDLK_o) 
        {
        sauvegarder(p1, bg,"Load.bin");
        printf("p1 data saved successfully");
        q=0;
        
        }           
	
        SDL_Flip(screen);
        SDL_Delay(10); 
    }
			
			break;
		case 2:
			 init_perso(&p2); 
		    	init_images_perso(&p2,"spritesheet1.png");
		    	init_perso_controls_p2(&p2);
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
        
        afficher_perso(p2, screen);
        afficher_score_vie(p2, screen, 0);
        animer_perso(&p2);
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
    if (!CollisionHorizontale(mask.img, p2.pos)) {
       
        move_perso(&p2);
        saut_perso(&p2);
    }
    else
    {

    p2.pos.x=p2.pos.x-2;
    }
    if(CollisionVerticale(mask.img, p1.pos))
    {
    printf("collision hoz");
      move_perso(&p1);
      saut_perso(&p1);
      p1.pos.y -= 2;
      
      move_perso(&p2);
      saut_perso(&p2);
      p2.pos.y -= 2;
     }
     if(CollisionVerticale(mask.img, p2.pos))
    {
  
      
      move_perso(&p2);
      saut_perso(&p2);
      p2.pos.y -= 2;
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
        if (p2.pos.x < 40) { 
            player_limite(&p2, screen);
            p2.pos.x = 40;
        }
        if (p2.pos.x > 3700) { 
            player_limite(&p2, screen);
            p2.pos.x = 3700;
        }

        updateEnemy(&e, p1.pos);
        
        UpdateMinimap(&minimap, p1.pos, resizingFactor, screen->w, screen->h);
        DisplayMinimap(&minimap, screen);

        afficherTempsLevel(tempsDebut, dureeTotale, screen, font);
         if(event.key.keysym.sym==SDLK_o) 
        {
        sauvegarder(p1, bg,"Load.bin");
        printf("p1 data saved successfully");
        sauvegarder(p2, bg,"Load.bin");
        printf("p2 data saved successfully");
        q=0;
        
        }  
       
        SDL_Flip(screen);
        SDL_Delay(10); 
    }
			break;
	}   
}
