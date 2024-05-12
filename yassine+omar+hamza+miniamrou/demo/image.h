#ifndef Image_H
#define Image_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string.h>
#include <stdlib.h>
#define SCREEN_W 1938
#define SCREEN_H 1115
typedef struct
{
SDL_Rect pos1;
SDL_Rect pos2;
SDL_Surface * img;
//int state;
}image;


void initBackground(image *Backg,char name[]);
void initBackgroundwindow(image *Backg,char name[]);
void initbouton(image *B,char name[],int x,int y);
void liberer(image A);
void afficher (image P, SDL_Surface *screen);
#endif
