#include<stdio.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>
#include "background.h"
#include "perso.h"
//#include "enigme.h"
//#include "temps.h"
//#include "minimap.h"
//#include "es.h"
//#include "enig2.h"
//#include "sauvegarde.h"
//#include "enigme2.h"
void main()
{	int mm;
	//enigme2 e;
	int x=0;
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_EnableKeyRepeat(60,60);
	bg bg;
	perso p1, p2;
	int boucle=1;
	int interface =1;
	int temps=0;
	int q=0;
	//int min,max;
	int a=1;
	//Time tmp;
	//map m;
	//enemie en;
	char nom[30];
	printf(" taper votre nom please!!!!!!!:");
	scanf("%s",nom);
	SDL_Surface *screen =SDL_SetVideoMode(1280,720,32,SDL_SWSURFACE);
SDL_EnableKeyRepeat(60,60);
	initbg(&bg);
	init_perso( & p1);
  	//init_perso_controls( & p1);
  	//init_images_perso( & p1);
  	//init_perso( & p2);
  	//init_perso_controls_p2( & p2);
  	//init_images_perso( & p2);
	//inittemps(&tmp);
	//initennemi (&en) ;
	//initialiser_map (&m,screen,&p1) ;
	//enigme enigme;
	//volume volume_enig;
	//mute mute_enig;
	//tempse time_enig;
	//SDL_Surface* anim_enig[4];
	//int *ianimation=0;
	SDL_Rect button_rect = { 0, 0, 0, 0 };
	SDL_Color textColor = {255, 0, 255};
	//SDL_Surface* button_surface = TTF_RenderText_Solid(TTF_OpenFont("font.ttf", 32)," Scores",textColor);
	//button_rect.w = button_surface->w;
	//button_rect.h = button_surface->h;
	SDL_Event event;
//musique(1);
while(q==0)
{
move_perso(&p1);
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                q=1;
            /*case SDL_MOUSEBUTTONDOWN:
                if (event.button.x >= button_rect.x && event.button.x < button_rect.x + button_rect.w &&
                    event.button.y >= button_rect.y && event.button.y < button_rect.y + button_rect.h) {
                    show_top_scores(screen);
                }
                break;*/
			
			case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    scrolling(&bg, 2, 0, 10);
                    break;
                case SDLK_DOWN:
                    scrolling(&bg, 3, 0, 10);
                    break;
                case SDLK_LEFT:
			if (p1.pos.x<100)
                    	{scrolling(&bg, 1, 10, 0);
			p1.pos.x=100;}
                    break;
                case SDLK_RIGHT:
                    if (p1.pos.x>800)
                    	{scrolling(&bg, 0, 10, 0);
			p1.pos.x=800;}
                    break;
                /*case SDLK_e:
		initialisation(&enigme,&volume_enig,&mute_enig,&time_enig,anim_enig); 
		x=resolution(&enigme,screen,volume_enig,mute_enig,time_enig,anim_enig );
                    break;
		case SDLK_m:
		enigme22();
		screen = SDL_SetVideoMode(1280, 720, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    break;*/
 //		case SDLK_s:
		//printf("Perso.x= ");
		//scanf("%hd",&p1.pos.x);
		//printf("vie= ");
//	scanf("%d",&p1.vie);
//	SDL_Surface *screen =SDL_SetVideoMode(1280,720,32,SDL_SWSURFACE);
	//interface_sauvegarde(screen,p1,bg);
	//interface_chargement(screen,&p1,&bg);
	//printf("vie:%d pos perso.x:%d pos bg.x:%d\n",p1.vie,p1.pos.x,bg.camerapos.x);
   //                 break;
            }
            default:
                break;
        }
    }
//if((p1.pos.x>720)&&(p1.pos.x<850)&&(p1.pos.y<360)&&(p1.pos.y>280)&&(bg.camerapos.x<450)&&(bg.camerapos.x>300))
//{play_sound();}
//animation(&bg);
afficherbg(&bg,screen);
//SDL_BlitSurface(button_surface, NULL, screen, &button_rect);
afficher_perso(p1, screen);
//afficher_perso(p2, screen);
//afficher_score_vie(p2, screen, 1);
//affiche_map(&m,screen,&p1);
//MAjMinimap(&p1 ,&m ,bg , 20 );
afficher_score_vie(p1, screen, 0);
animer_perso( & p1);
saut_perso( & p1);
//    animer_perso( & p2);
  //  move_perso( & p2);
    //saut_perso( & p2);
//update_time(&tmp);
//perso_map(&m,&p1);
//update_ennemie (&en,&p1);
//if(colli(&p1,&en)) */
//{a = gerer(&en);
//initialisation(&enigme,&volume_enig,&mute_enig,&time_enig,anim_enig);
//while (x==0) 
//x=resolution(&enigme,screen,volume_enig,mute_enig,time_enig,anim_enig );
//}
/*if (a)
{ //afficherennemi(en ,screen);}		
displaytime(tmp,screen);
SDL_Delay(100);
SDL_Flip(screen);
}*/
//Score score;
//strcpy(score.name,nom);
//score.score = bg.camera.x;
//score.temps = 0;
//save_score(score);
//SDL_FreeSurface(button_surface);
//free_minimap(m);
//chargement(&p1,&bg);
//freeTexttime(tmp.temps);
SDL_Quit();
}
}
