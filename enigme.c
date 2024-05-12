#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>   
#include <SDL/SDL_mixer.h>   
#include <SDL/SDL_ttf.h>     
#include "enigme.h" 
#include <time.h>
void afficherTempsPuzzle(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *funt) {
    int temps_ecoule = (SDL_GetTicks() - tempsDebut) / 1000;
    int temps_restant = dureeTotale - temps_ecoule;
    char tempsText[100];
   
    if (temps_restant <= 0) {
        sprintf(tempsText, "Puzzle Time: %d seconds", temps_ecoule);
    } else {
        sprintf(tempsText, "Remaining Puzzle Time: %d seconds", temps_restant);
    }
   
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Surface *textSurface = TTF_RenderText_Solid(funt, tempsText, textColor);
    SDL_Rect textRect = { 10, 50, 0, 0 };
   
    SDL_BlitSurface(textSurface, NULL, screen, &textRect);
    SDL_FreeSurface(textSurface);
}

  
void initialiser_imageBACK(image *image)
{
image->url="enigme.png" ; 
image->img=IMG_Load(image->url) ; 
if (image->img == NULL) 
{
printf("unable to load background image %s \n",SDL_GetError()) ;
 return ;  
}
image->pos_img_ecran.x=0 ; 
image->pos_img_ecran.y=0 ; 

image->pos_img_affiche.x=0 ; 
image->pos_img_affiche.y=0; 

image->pos_img_affiche.h=521 ; 
image->pos_img_affiche.w=595 ; 

}

void initialiser_imageBOUTON1(image *imgbtn) 
{

imgbtn->url="no.png" ; 
imgbtn->img=IMG_Load(imgbtn->url); 
if (imgbtn->img ==NULL)
   {printf("unable to load background image %s ",SDL_GetError());
   return ;}

imgbtn->pos_img_ecran .x=30; 
imgbtn->pos_img_ecran.y=50 ;
imgbtn->pos_img_ecran.w=200 ;
imgbtn->pos_img_ecran.h=200;

 
imgbtn->pos_img_affiche.x=0 ; 
imgbtn->pos_img_affiche.y=0;
imgbtn->pos_img_affiche.w=0;
imgbtn->pos_img_affiche.h=0 ; 


//imgbtn->pos_img_affiche.x=((SCREEN_W-imgbtn->pos_img_affiche.w)/2) ;
//imgbtn->pos_img_affiche.y=((SCREEN_H-imgbtn->pos_img_affiche.h)/3) ;
}

void initialiser_imageBOUTON2(image *imgbtn) 
{

imgbtn->url="yes.png" ;   
imgbtn->img=IMG_Load(imgbtn->url); 
if (imgbtn->img ==NULL)
   {printf("unable to load background image %s ",SDL_GetError());
   return ;}

imgbtn->pos_img_ecran .x=30; 
imgbtn->pos_img_ecran.y=50 ;
imgbtn->pos_img_ecran.w=200 ;
imgbtn->pos_img_ecran.h=200;

 
imgbtn->pos_img_affiche.x=0 ; 
imgbtn->pos_img_affiche.y=0;
imgbtn->pos_img_affiche.w=0;
imgbtn->pos_img_affiche.h=0 ; 


//imgbtn->pos_img_affiche.x=((SCREEN_W-imgbtn->pos_img_affiche.w)/2) ;
//imgbtn->pos_img_affiche.y=((SCREEN_H-imgbtn->pos_img_affiche.h)/3) ;
}




void afficher_imageBMP(SDL_Surface *screen , image image )
{ 
SDL_BlitSurface(image.img ,NULL , screen , &image.pos_img_ecran ) ; 
}

void afficher_imageBTN1(SDL_Surface *screen , image image )
{ 
SDL_BlitSurface(image.img ,NULL   , screen ,&image.pos_img_ecran ) ; 
 
}

void afficher_imageBTN2(SDL_Surface *screen , image image )
{ 
SDL_BlitSurface(image.img ,NULL   , screen ,&image.pos_img_ecran ) ; 
 }




void liberer_image(image image) 
{
SDL_FreeSurface(image.img) ;
}

void initialiser_audio(Mix_Music *music)
{
 if (Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS ,1024)==-1)
   {printf("%s",SDL_GetError()) ; }

 music=Mix_LoadMUS("happy.mp3"); 
 Mix_PlayMusic(music,-1)  ;
 Mix_VolumeMusic(MIX_MAX_VOLUME/3.5) ; 
}


   
void liberer_musique(Mix_Music *music)
{ Mix_FreeMusic(music) ; }






void afficherEnigme(SDL_Surface* screen, enigme e,int tb ) {
    

    SDL_Colour text_color;
    SDL_Surface* questionsurface;
    SDL_Surface* r1surface;
    SDL_Surface* r2surface;
    SDL_Surface* r3surface;

    SDL_Rect questionpos;
    SDL_Rect r1pos;
    SDL_Rect r2pos;
    SDL_Rect r3pos;

    TTF_Font* font = NULL;
    int font_loaded = 0;

    
    while (!font_loaded) {
        font = TTF_OpenFont("MontserratAlternates-Black.otf", 30);
        if (font == NULL) {
            printf("Could not load font. Retrying in 1 second...\n");
            SDL_Delay(1000); 
        } else {
            font_loaded = 1;
        }
    }
    
    
    text_color.r=255;
    text_color.g=255;
    text_color.b=255;
    questionsurface = TTF_RenderText_Blended(font, e.question, text_color);
    r1surface = TTF_RenderText_Blended(font, e.r1, text_color);
    r2surface = TTF_RenderText_Blended(font, e.r2, text_color);
    r3surface = TTF_RenderText_Blended(font, e.r3, text_color);
    questionpos.x = 420;
    questionpos.y = 480;
    switch (tb) {
    case 0:
        r1pos.x = 70;
        r1pos.y = 700;
        r2pos.x = 453;
        r2pos.y = 700;
        r3pos.x = 800;
        r3pos.y = 700;
        break;
    case 1:
        r1pos.x = 800;
        r1pos.y = 700;
        r2pos.x = 70;
        r2pos.y = 700;
        r3pos.x = 453;
        r3pos.y = 700;
        break;
    case 2:
        r1pos.x = 453;
        r1pos.y = 700;
        r2pos.x = 800;
        r2pos.y = 700;
        r3pos.x = 70;
        r3pos.y = 700;
        break;
   
}


SDL_BlitSurface(questionsurface, NULL, screen, &questionpos);
SDL_BlitSurface(r1surface, NULL, screen, &r1pos);
SDL_BlitSurface(r2surface, NULL, screen, &r2pos);
SDL_BlitSurface(r3surface, NULL, screen, &r3pos);

SDL_Flip(screen);

TTF_CloseFont(font);
SDL_FreeSurface(questionsurface);
SDL_FreeSurface(r1surface);
SDL_FreeSurface(r2surface);
SDL_FreeSurface(r3surface);

    
}




/* // Free surfaces and font
    SDL_FreeSurface(questionsurface);
    SDL_FreeSurface(r1surface);
    SDL_FreeSurface(r2surface);
    SDL_FreeSurface(r3surface);
    TTF_CloseFont(font); */



void genererEnigme(char* filename, enigme* e) {
  FILE* fp = fopen(filename, "r");
    int random_question_index = rand() % 12 + 1;
    int current_question_index = 0;
    char line[500];
 	
    while (fgets(line, sizeof(line), fp)) {
        switch (current_question_index % 5) {
            case 0:
                strcpy(e->question, line);
                break;
            case 1:
                strcpy(e->r1, line);
                break;
            case 2:
                strcpy(e->r2, line);
                break;
            case 3:
                strcpy(e->r3, line);
                break;
            case 4:
                if (current_question_index / 5 == random_question_index - 1) {
                    e->numbr = atoi(line);
                    
                    fclose(fp);
                    return;
                }
                break;
        }
        current_question_index++;
    }

  
    fclose(fp);
}


void animate(SDL_Surface *screen, enigme *e) {
    int frame = 0;
    char *image_names[3] = {"an1.png", "an2.png","an3.png"};


    for (int i = 0; i < 3; i++) {
        e->images[i].url = image_names[i];
        e->images[i].img = IMG_Load(image_names[i]);
        e->images[i].pos_img_affiche.x = 10;
        e->images[i].pos_img_affiche.y = 255;
        e->images[i].pos_img_ecran.x = -105;
        e->images[i].pos_img_ecran.y = 148;
    }
    while (frame < 3) {
        
        SDL_BlitSurface(e->images[frame].img, NULL, screen, &e->images[frame].pos_img_ecran);
        SDL_Flip(screen);

        
        SDL_Delay(280);

        SDL_FreeSurface(e->images[frame].img);


        frame++;
    }
}
