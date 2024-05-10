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
#include "image.h"
#include "texte.h"
#define SCREEN_W 1938
#define SCREEN_H 1115
#define NUMBER_OF_IMAGES 4
int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();
 	/*INITItoALISATION IMAGE*/
	TTF_Init();
	SDL_Surface *text=NULL;
	TTF_Font *font1 ;
	SDL_Color textColor;
	char string[20];
	textColor.r=136;
	textColor.g=8;
	textColor.b=8;
	SDL_Rect positiontext;

	font1 = TTF_OpenFont("AVENGEANCE HEROIC AVENGER.ttf", 40);
	if (font1 == NULL) {
	    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	    return 1; 
	}
	positiontext.x=800;
	positiontext.y=0;
	

	//SDL_Surface *backgrounds[4];
	    bg bag,mask;
    perso p1;
    enemy e;
    Minimap minimap;

    int q=1;
    int scrollLeft = 0; // Flag for left scrolling
    int scrollRight = 0; // Flag for right scrolling
    int resizingFactor=4;
  
    SDL_PumpEvents();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Font *font = TTF_OpenFont("fonts/score.ttf", 24);
    
    
    int tempsDebut = SDL_GetTicks(); 
    int dureeTotale = 60 * 1000; 
    SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
    init_perso(&p1); 
    initEnemy(&e);
    initbg(&bag);
    initmask(&mask);
    InitializeMinimap(&minimap, screen, 1000, 188);
	//SDL_Surface *f[11];
	int boucle=0;
	int soundp=0;
	int m=5;
	int bg=0;
	int bs=0;
	int b3=0;
	int b4=0;
	int i1=0;
	int i2=0;
	int fullscreenMode = 0;
	image Backg,Backg1,Backg2,Backgr,Backg3,Backg4;
	image B1,B2,B3,B4,B5,B6,B7,B8,B9,B11,B12,B13,B14,B15,B16,B17,B18,B19,B20,B21,B22	;
	SDL_Event event;
	SDL_Event event1;
	Text t2,t3,t4,t5,t6;
 	int bfin= 0;
	int currentFrame= 0;
	int animationSpeed = 300;
	int animationDelay = 0;
    
/*CREATION D'UNE FENETRE*/
	
	screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	
	if(!screen)
	{
		printf("Unable to set video %s\n",SDL_GetError());
		return 1;	
	}
	image BackgroundAnimation[NUMBER_OF_IMAGES];
    	for (int i = 0; i < NUMBER_OF_IMAGES; ++i) {
        	char filename[20];
       	 	sprintf(filename, "background%d.jpg", i + 1);
        	initBackground(&BackgroundAnimation[i], filename);
    	}

	//initBackground(&Backg,"background.jpg");
	/*backgrounds[0] = IMG_Load("background1.jpg");
    	backgrounds[1] = IMG_Load("background2.jpg");
    	backgrounds[2] = IMG_Load("background3.jpg");
    	backgrounds[3] = IMG_Load("background4.jpg");*/
	initBackground(&Backg1,"settings.png");
	initBackground(&Backg2,"comingsoon.png");
	initBackground(&Backgr,"help them.png");
	initBackgroundwindow(&Backg3,"4.png");
	initBackgroundwindow(&Backg4,"5.png");
	initbouton(&B1,"start1.png",241.5,506);
	initbouton(&B2,"settings1.png",618.5,504.25);
	initbouton(&B3,"help1.png",1077.5,506.25);
	initbouton(&B4,"quit1.png",1485.5,506.25);
	initbouton(&B5,"start2.png",241.5,506);
	initbouton(&B6,"settings2.png",618.5,504.25);
	initbouton(&B7,"help2.png",1077.5,506.25);
	initbouton(&B8,"quit2.png",1485.5,506.25);
	//initbouton(&B9,"logo",800,250);
	/*f[1]=IMG_Load("f1.png");
   	 f[2]=IMG_Load("f2.png");
    	 f[3]=IMG_Load("f3.png");
  	 f[4]=IMG_Load("f4.png");
  	 f[5]=IMG_Load("f5.png");
   	 f[6]=IMG_Load("f6.png");*/
	initbouton(&B11,"home.png",16.93,31.54);
	initbouton(&B12,"home2.png",16.93,10);
        initbouton(&B13,"home2.png",535,837);
	initbouton(&B14,"plus1.png",1350,300);
	initbouton(&B15,"moins1.png",820,300);
	initbouton(&B16,"plus2.png",1350,300);
	initbouton(&B17,"moins2.png",820,300);
	initbouton(&B18,"v2.png",630,-60);
	initbouton(&B20,"2.png",703,203);
	initbouton(&B19,"3.png",705,460);
	initbouton(&B22,"6.png",703,188);
	initbouton(&B21,"7.png",705,444);
	inittext2(&t2);
	inittext3(&t3);
	inittext4(&t4);
	inittext5(&t5);
	inittext5(&t6);
	

	SDL_WM_SetCaption("SDL_Mixer",NULL);
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
	{
		printf("%s",Mix_GetError());
	}
	Mix_Music *music;
	Mix_Chunk *son;
	Mix_Chunk *son1;
	music= Mix_LoadMUS("8-bit-halloween-story-166454.mp3");
	son=Mix_LoadWAV("clic.wav");
	son1=Mix_LoadWAV("DOORCreak_Grincement de porte (ID 0302)_LS.wav");
	Mix_PlayMusic(music,-1);
	Mix_VolumeMusic(MIX_MAX_VOLUME/m);
	/*if (backgrounds[0] == NULL || backgrounds[1] == NULL || backgrounds[2] == NULL || backgrounds[3] == NULL)
    {
        fprintf(stderr, "Erreur de chargement d'image de fond.\n");
        return 1;
    }*/

	while ((!boucle))
	{
        if (SDL_GetTicks() - animationDelay > animationSpeed)
        {
        	SDL_Flip(screen);
            afficher(BackgroundAnimation[currentFrame], screen);
            currentFrame = (currentFrame + 1) % NUMBER_OF_IMAGES;
            animationDelay = SDL_GetTicks();
        }
		//afficher(Backg,screen);
		afficher(B1,screen);
		afficher(B2,screen);
		afficher(B3,screen);
		afficher(B4,screen);
		//afficher(B9,screen);
		displaytext5(t5,screen);	
		//SDL_Flip(screen);
    		SDL_WaitEvent(&event);
		switch (event.type)
		{
			case SDL_QUIT:
				boucle=1;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				    boucle = 1;
				if (event.key.keysym.sym == SDLK_f)
				{
				    fullscreenMode = !fullscreenMode;
				    SDL_WM_ToggleFullScreen(screen);
				}
				else if (event.key.keysym.sym == SDLK_n)
				{
				    fullscreenMode = 0;
				    SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
				}
				break;
				      if(((event.motion.x >= 230 && event.motion.x <= 483 && event.motion.y >= 507 && event.motion.y <= 923) || (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)||(event.motion.x >= 630 && event.motion.x <= 883 && event.motion.y >= 507 && 				event.motion.y <= 923) || (event.motion.x >= 1080 && event.motion.x <= 1333 && event.motion.y >= 507 && event.motion.y <= 923) || (event.motion.x >= 1500 && event.motion.x <= 1753 && event.motion.y >= 507 && event.motion.y <= 923)))
                {
                
                if(soundp==0)
                 Mix_PlayChannel(-1,son1, 0);
                    soundp=1;
                }
                else if (soundp ==1)
                    soundp=0;
			break;
			case SDL_MOUSEBUTTONDOWN :
		
				if ((event.motion.x>622)&&(event.motion.x<=872)&&(event.motion.y>860)&&(event.motion.y<=921))//settings
				{
					while (bg)
					{
						
						afficher(Backg1,screen);
						//bs=1;
						afficher(B11,screen);
						//afficher(B13,screen);
						afficher(B18,screen);
						afficher(B14,screen);
						afficher(B15,screen);
						displaytext3(t3,screen);
						displaytext4(t4,screen);
						SDL_Flip(screen);

						SDL_WaitEvent(&event1);
						switch (event1.type)
						{	case SDL_KEYDOWN:
								if (event1.key.keysym.sym == SDLK_ESCAPE)
								    boucle = 1;
								if (event1.key.keysym.sym == SDLK_f)
								{
								    fullscreenMode = !fullscreenMode;
								    SDL_WM_ToggleFullScreen(screen);
								}
								else if (event1.key.keysym.sym == SDLK_n)
								{
								    fullscreenMode = 0;
								    SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
								}
								break;
							/*case SDL_KEYUP:
								if(event1.key.keysym.sym==SDLK_f)
									screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
								if(event1.key.keysym.sym==SDLK_n)
									screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
								break;*/
							case SDL_MOUSEMOTION ://in settings
	 							if (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)
								{	
									afficher(B12,screen);
									Mix_PlayChannel(-1,son,0);
									//SDL_Flip(screen);
								}
								if (event1.motion.x>1350 && event1.motion.x<=1400 && event1.motion.y>300 && event1.motion.y<=350)
								{	
									afficher(B16,screen);
									Mix_PlayChannel(-1,son,0);
									//SDL_Flip(screen);
								}
								if (event1.motion.x>820 && event1.motion.x<=850 && event1.motion.y>300 && event1.motion.y<=350)
								{	
									afficher(B17,screen);
									Mix_PlayChannel(-1,son,0);
									//SDL_Flip(screen);
								}
								break;
							case SDL_MOUSEBUTTONUP:
								if (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)//retour au menu
								{
									bg=0;
									SDL_Flip(screen);	
								}
	
								else if (event1.motion.x>1350 && event1.motion.x<=1400 && event1.motion.y>300 && event1.motion.y<=350)//ajout de music
								{	
									if(B18.pos1.x<=630)
										{
										B18.pos1.x=B18.pos1.x+25;
										m=m-5;
										Mix_VolumeMusic(MIX_MAX_VOLUME/m);
										}
									B18.pos1.y=-60;
									B18.pos2.x=0;
									B18.pos2.y=0;
									B18.pos2.w=1938;
									B18.pos2.h=1115;
									SDL_Flip(screen);						
								}		
								else if (event1.motion.x>820 && event1.motion.x<=850 && event1.motion.y>300 && event1.motion.y<=350)//deminuer le music
								{	
									if(B18.pos1.x>=250)
									{
										B18.pos1.x=B18.pos1.x-25;
										m=m+5;
										Mix_VolumeMusic(MIX_MAX_VOLUME/m);
									}
									B18.pos1.y=-60;
									B18.pos2.x=0;
									B18.pos2.y=0;
									B18.pos2.w=1938;
									B18.pos2.h=1115;
									SDL_Flip(screen);
								}
								break;
				}
				
				SDL_Flip(screen);			
			}
						
		}
		
		
		bg=1;
		SDL_Flip(screen);
		if ((event.motion.x>1486)&&(event.motion.x<=1736)&&(event.motion.y>860)&&(event.motion.y<=921))//exite
			{
				boucle=1;
			}
		if ((event.motion.x>1078)&&(event.motion.x<=1328)&&(event.motion.y>863)&&(event.motion.y<=924))//help
		{
			while (bg)
			{
				afficher(Backgr,screen);
				afficher(B11,screen);
				//SDL_Flip(screen);
				SDL_WaitEvent(&event1);
				switch (event1.type)
				{
					case SDL_MOUSEMOTION :
						if (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)//touche home
						{	
							afficher(B12,screen);
							Mix_PlayChannel(-1,son,0);
							//SDL_Flip(screen);
						}
						break;
					case SDL_MOUSEBUTTONUP:
						if (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)//retour
						{	
							bg=0;
							SDL_Flip(screen);	
						}
						break;
				}
				SDL_Flip(screen);
			}
			bg=1;
			//SDL_Flip(screen);
		}	
 	if (event.motion.x>245 && event.motion.x<=495 && event.motion.y>862 && event.motion.y<=923)//play
	{			
  	while (bg)
	{
    	afficher(Backg3,screen);
   	SDL_PollEvent(&event);
    	//displaytext2(t2,screen);
    	//SDL_Flip(screen);
   
    	switch(event.type)
   	 	{
      	case SDL_QUIT:
      		bfin= 1;
        	break;
	case SDL_KEYUP:
      		switch(event.key.keysym.sym)
       		{
			case SDLK_h:
				bg=0;
				//SDL_Flip(screen);
				bfin=1;
				break;
  		}
  	case SDL_MOUSEMOTION ://in play yassine
	 	if (event.motion.x >= 657 && event.motion.x <= 1265 && event.motion.y >= 305 && event.motion.y <= 453)
		{	
			afficher(B20,screen);
			//b3=1;
			//Mix_PlayChannel(-1,son,0);
			SDL_Flip(screen);
		}
		if (event.motion.x >= 657 && event.motion.x <= 1265 && event.motion.y >= 560 && event.motion.y <= 708)
		{	
			afficher(B19,screen);
			//b3=1;
			//Mix_PlayChannel(-1,son,0);
			SDL_Flip(screen);
		}
		if (event.motion.x >= 520 && event.motion.x <= 860 && event.motion.y >= 837 && event.motion.y <= 900)
		{	
			afficher(B13,screen);
			//Mix_PlayChannel(-1,son,0);
			SDL_Flip(screen);
		}
		break;
	case SDL_MOUSEBUTTONUP://menu solo ou multiplaers
		if (event.motion.x >= 520 && event.motion.x <= 860 && event.motion.y >= 837 && event.motion.y <= 900)
		{	
			bg=0;
			b3=0;
			SDL_Flip(screen);
		}
		if (event.motion.x >= 657 && event.motion.x <= 1265 && event.motion.y >= 305 && event.motion.y <= 453)
		{	
			b3=1;
		}
		if (event.motion.x >= 657 && event.motion.x <= 1265 && event.motion.y >= 560 && event.motion.y <= 708)
		{
			b3=1;
			//bg=0;
		}
		break;		
  		}
  	//boucle afffichage solo multiplayer omar
  	while (b3!=0){
  		afficher(Backg4,screen);
  		SDL_PollEvent(&event1);
  		switch(event1.type)
   	 	{
      			case SDL_QUIT:
      			bfin= 1;
        		break;
			case SDL_KEYUP:
      			switch(event1.key.keysym.sym)
       			{
				case SDLK_h:
				bg=0;
				//SDL_Flip(screen);
				bfin=1;
				break;
  			}
  			case SDL_MOUSEMOTION ://in menu solo multiplayer omar
			 	if (event1.motion.x >= 657 && event1.motion.x <= 1265 && event1.motion.y >= 305 && event1.motion.y <= 453)
				{	
					afficher(B22,screen);
					b4=1;
					//Mix_PlayChannel(-1,son,0);
					SDL_Flip(screen);
				}
				if (event1.motion.x >= 657 && event1.motion.x <= 1265 && event1.motion.y >= 560 && event1.motion.y <= 708)
				{	
					afficher(B21,screen);
					//b3=1;
					//Mix_PlayChannel(-1,son,0);
					SDL_Flip(screen);
				}
				if (event1.motion.x >= 520 && event1.motion.x <= 860 && event1.motion.y >= 837 && event1.motion.y <= 900)
				{	
					afficher(B13,screen);
					//Mix_PlayChannel(-1,son,0);
					SDL_Flip(screen);
				}
				break;
			case SDL_MOUSEBUTTONUP://menu retour
				if (event1.motion.x >= 520 && event1.motion.x <= 860 && event1.motion.y >= 837 && event1.motion.y <= 900)
				{	
					//bg=0;
					b3=0;
					SDL_Flip(screen);
				}
				break;
  		
  	
  	}
  	SDL_Flip(screen);
  	}
  	while(b4!=0){
  	                /*switch (event.key.keysym.sym) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
					q=0;}*/
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
            scrolling(&bag, 1, p1.pos.x, 0);
            scrolling(&mask, 1, p1.pos.x, 0); // Scroll left continuously
        }
        if (scrollRight) {
            scrolling(&bag, 0, p1.pos.x, 0);
            scrolling(&mask, 0, p1.pos.x, 0); // Scroll right continuously
        }
	
	afficherbg(&mask, screen);
        afficherbg(&bag, screen);
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

  	
  	SDL_Flip(screen);
  	}
  	SDL_Flip(screen);
		}
	}		
		case SDL_MOUSEMOTION : 
			if (event.motion.x>245 && event.motion.x<=495 && event.motion.y>862 && event.motion.y<=923)
				{	
				// here to add txt
					afficher(B5,screen);
					text = TTF_RenderText_Solid(font1, "press play to start ", textColor );
					SDL_BlitSurface(text, NULL, screen, &positiontext);
					//Mix_PlayChannel(-1,son,0);
					
				}
			if ((event.motion.x>622)&&(event.motion.x<=872)&&(event.motion.y>860)&&(event.motion.y<=921))
				{
					afficher(B6,screen);
					text = TTF_RenderText_Solid(font1, "customize your settings ", textColor );
					SDL_BlitSurface(text, NULL, screen, &positiontext);
					//Mix_PlayChannel(-1,son,0);
					//SDL_Flip(screen);		
				}
			if ((event.motion.x>1078)&&(event.motion.x<=1328)&&(event.motion.y>863)&&(event.motion.y<=924))
				{
					afficher(B7,screen);
					text = TTF_RenderText_Solid(font1, "Learn more about us", textColor );
					SDL_BlitSurface(text, NULL, screen, &positiontext);
					//Mix_PlayChannel(-1,son,0); 
					//SDL_Flip(screen);
				}
			if ((event.motion.x>1486)&&(event.motion.x<=1736)&&(event.motion.y>860)&&(event.motion.y<=921))
				{
					afficher(B8,screen);
					text = TTF_RenderText_Solid(font1, "quit the game ", textColor );
					SDL_BlitSurface(text, NULL, screen, &positiontext);
					//Mix_PlayChannel(-1,son,0);
					//SDL_Flip(screen);
				}
			//sound area detection
      if(((event.motion.x >= 230 && event.motion.x <= 483 && event.motion.y >= 507 && event.motion.y <= 923) || (event1.motion.x>29 && event1.motion.x<=309 && event1.motion.y>39 && event1.motion.y<=107)||(event.motion.x >= 630 && event.motion.x <= 883 && event.motion.y >= 507 && 				event.motion.y <= 923) || (event.motion.x >= 1080 && event.motion.x <= 1333 && event.motion.y >= 507 && event.motion.y <= 923) || (event.motion.x >= 1500 && event.motion.x <= 1753 && event.motion.y >= 507 && event.motion.y <= 923) && bg==1))
                {
                
                if(soundp==0)
                 Mix_PlayChannel(-1,son1, 0);
                    soundp=1;
                }
                else if (soundp ==1)
                    soundp=0;
			break;
	
		}
		//SDL_Delay(animationSpeed);
		SDL_Flip(screen);
		SDL_Delay(10); 
		// Animation des images de fond
        /*currentBackground = (currentBackground + 1) % 4;
        SDL_Delay(1000); // Délai pour ralentir l'animation*/
	}

	//liberer(Backg);
	liberer(Backg1);
	liberer(Backg2);
	liberer(Backgr);
	liberer(Backg3);
	liberer(Backg4);
	liberer(B1);
	liberer(B2);
	liberer(B3);
	liberer(B4);
	liberer(B5);
	liberer(B6);
	liberer(B7);
	liberer(B8);
	//liberer(B9);
	liberer(B11);
	liberer(B12);
	liberer(B13);
	liberer(B14);
	liberer(B15);
	liberer(B16);
	liberer(B17);
	liberer(B18);
	liberer(B19);
	liberer(B20);
	liberer(B21);
	liberer(B22);
	//////////////
	freetext(t2);
	freetext(t3);
	freetext(t4);
	freetext(t5);
	freetext(t6);
	SDL_FreeSurface(text);
	Mix_FreeMusic(music);
	Mix_FreeChunk(son);
return 0 ;	
}

