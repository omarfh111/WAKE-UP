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
#include "enigme.h"

void main(){
	
//declaration game
    scoreinfo scores[15];
    scoreinfo s;
    loadbestscore("scores.txt", scores);
    bg bg,mask;
    perso p1,p2;
    enemy e;
    Minimap minimap;
    enigme en;

    int q=1;
    int scrollLeft = 0; // Flag for left scrolling
    int scrollRight = 0; // Flag for right scrolling
    int resizingFactor=4;
    char playername[20];
    SDL_PumpEvents();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("fonts/score.ttf", 24);
    
    //hajet enigme
    TTF_Font *funt=TTF_OpenFont("MontserratAlternates-Black.otf",24);
    int tempsDebute=SDL_GetTicks();
    int dureeTotalee=60*1000;
    image IMAGE, IMAGE_BTN1, IMAGE_BTN2;
    Mix_Music *music;
    en.numbr=0;
    
     int input=0;
     int boucleinput=0;
     srand(time(NULL));
	int tb = rand() % 3;

	initialiser_imageBACK(&IMAGE);
	initialiser_imageBOUTON1(&IMAGE_BTN1) ; 
	initialiser_imageBOUTON2(&IMAGE_BTN2) ; 
        //initialiser_audio(music);
        en.f = fopen("enigme.txt", "r");
        fgets(en.question, sizeof(en.question), en.f);

    	fgets(en.r1, sizeof(en.r1), en.f);
    	fgets(en.r2, sizeof(en.r2), en.f);
    	fgets(en.r3, sizeof(en.r3), en.f);
    	fscanf(en.f, "%d", &en.numbr);
	printf("\n correct response is : %d \n",en.numbr); 
    	fgets(en.x, sizeof(en.x), en.f); 
    	srand(time(NULL));
	genererEnigme("enigme.txt", &en);
    
    
    int tempsDebut = SDL_GetTicks(); 
    int dureeTotale = 60 * 1000; 
    SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
    init_perso(&p1); 
    init_images_perso(&p1,"spritesheet.png");
    init_perso_controls(&p1);
    initEnemy(&e);
    SDL_Event event,evente;
    initbg(&bg);
    initmask(&mask);
    InitializeMinimap(&minimap, screen, 1000, 188);


//declaration console menu
	int c;
	int c1;
	printf("1.solo\n2.multiplayer\n3.bestscore\n4.playername\n0.quit");
	scanf("%d",&c);
	 do {
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
                        case SDLK_LCTRL: // Check for left Ctrl key
                    if ((event.key.keysym.mod & KMOD_CTRL) != 0) { // Check if Ctrl key is pressed
                        p1.score += 100; // Increment score by 100
                        printf("Score: %d\n", p1.score); // Debug print to check if the score increases
                    }
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
        afficherbg(&bg, screen);
        SDL_Delay(60);
        afficher_perso(p1, screen);
        afficher_score_vie(p1, screen, 0);
        animer_perso(&p1);
        drawEnemy(screen, e);
        move_perso(&p1);
        saut_perso(&p1);
        
   /* hethi collision mich partfaite fi jorrit el mask  */  
          
           /*if (!CollisionHorizontale(mask.img, p1.pos)) {
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
    */
 
    
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
displayScore(screen, font, p1);
        afficherTempsLevel(tempsDebut, dureeTotale, screen, font);
        if (event.key.keysym.sym == SDLK_o) {
            sauvegarder(p1, bg, "Load.bin");
            printf("p1 data saved successfully\n");
            printf("Final score: %d\n", p1.score);
            savescore(SDL_GetTicks() - tempsDebut, p1,scores,"scores.txt",playername);
            q = 0;
        }
         if(event.key.keysym.sym==SDLK_e) 
         { 
         afficher_imageBMP(screen, IMAGE);
         afficherEnigme(screen,en,tb);
	 animate(screen,&en) ;
	 while (SDL_PollEvent(&evente))
        {
            switch (evente.type)
            {
		 case SDL_KEYDOWN :			 
			if (evente.key.keysym.sym<=SDLK_a)
			{
			input=1;
			}

			else if (evente.key.keysym.sym<=SDLK_b){
			input=2;
			}

			else if (evente.key.keysym.sym<=SDLK_c){
			input=3;	
			}
			break;

		  case SDL_QUIT:
			q = 0;
			break;
			    }
			}

	if (input!=0){   
	if(input==en.numbr){
		boucleinput=1;
		while (boucleinput){
		while (SDL_PollEvent(&evente)){

				switch (evente.type)
					   	 {

				case SDL_QUIT:
						    boucleinput=0;
						    input=0;
						    break;
						}
						}
	afficher_imageBTN1(screen,IMAGE_BTN1 ) ;
	SDL_Flip(screen);
}	
}
else{
	boucleinput=-1;
	while (boucleinput==-1){
while (SDL_PollEvent(&evente)){

switch (evente.type)
            {

case SDL_QUIT:
                    boucleinput=0;
		    input=0;
                    break;



}
}
	afficher_imageBTN2(screen,IMAGE_BTN2 ) ;       
	SDL_Flip(screen);
}
}
}
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
        afficherbg(&bg, screen);
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
	case 3:
	printBestScores(scores);
	printf("1.solo\n2.multiplayer\n3.bestscore\n4.playername\n0.quit");
    scanf("%d", &c);
	break;
	   
case 4:
    printf("playername:\n");
    scanf("%s",playername);
    printf("1.solo\n2.multiplayer\n3.bestscore\n4.playername\n0.quit");
    scanf("%d", &c); // Update the value of c
    break;
 }

    } while (q); // Continue looping until q is not true (i.e., 0)

}
