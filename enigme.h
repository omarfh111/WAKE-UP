#ifndef FONCTION_H
#define FONCTION_H

#include <SDL/SDL.h>
/*--------ETAPE 0 DECLARATION DU BIBLIOTHEQUE SDL ---------------*/
#include <SDL/SDL_image.h>  // pour manipuler des image 
#include <SDL/SDL_mixer.h>  // pour manipuler des audio 
/*-------------------------------------------------------------------*/

#define SCREEN_H 410 
#define SCREEN_W 640


typedef struct 
{ 
  char *url ; 
 SDL_Rect    pos_img_affiche;
 SDL_Rect      pos_img_ecran ;
 SDL_Surface    *img ;

}image; 

typedef struct {
    FILE* f;
    char question[400];
    char r1[50];
    char r2[50];
    char r3[50];
    int numbr;
    char x[50];
    image images[3];
} enigme;


void afficherEnigme(SDL_Surface *screen, enigme e);

// definition des fenetre des fonction 

//definition pour la manipulation de l'image 
void initialiser_imageBACK(image *image) ; 
void initialiser_imageBOUTON1(image *image) ; 
void initialiser_imageBOUTON2(image *image) ; 

void afficher_imageBTN1(SDL_Surface *screen , image image ) ;
void afficher_imageBTN2(SDL_Surface *screen , image image) ;

void afficher_imageBMP(SDL_Surface *screen , image image) ; 
void genererEnigme(char* filename, enigme* e);

void animate(SDL_Surface *screen,enigme *e);

void liberer_image(image image) ; 


//definition pour la manipulation de l'audio 
void initialiser_audio(Mix_Music *music) ; 
void liberer_musique(Mix_Music *music) ;

 
#endif 












