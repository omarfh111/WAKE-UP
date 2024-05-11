#ifndef TEXTE_H
#define TEXTE_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>


typedef struct {
	SDL_Rect position;
	TTF_Font *font;
	SDL_Surface *surfaceTexte;
	SDL_Color textColor;
	char texte[50];
}Text;


void inittext2(Text *t2);
void inittext3(Text *t3);
void inittext4(Text *t4);
void inittext5(Text *t5);
void freetext(Text A);
void displaytext2(Text t2,SDL_Surface *screen);
void displaytext3(Text t3,SDL_Surface *screen);
void displaytext4(Text t4,SDL_Surface *screen);
void displaytext5(Text t5,SDL_Surface *screen);
#endif
