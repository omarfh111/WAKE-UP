#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "perso.h"
typedef struct{
SDL_Rect imgp;
SDL_Rect imgs;
SDL_Surface *img;
int direction;
}bg;
typedef struct{
int score;
int temps;
char playername[20];
}scoreinfo;
typedef struct{
SDL_Rect imgs;
SDL_Rect imgp;
SDL_Surface *img;
}imagee;
void initbg(bg *b);
void afficherbg(bg *b, SDL_Surface *screen);
void animerbg(SDL_Surface *screen,SDL_Surface *img);
void scrolling(bg *b, int direction, float dx, float dy);
void savescore(int t, perso p, scoreinfo scores[], char *filename, char *playername);
void loadbestscore(char *filename, scoreinfo scores[]);
void displayscore(SDL_Surface *screen, scoreinfo t[]);
void splitscreen(SDL_Surface *screen,bg *b);
void afficherheart(imagee *i, SDL_Surface *screen);
void imgheart(imagee *i);
void initmask(bg *mask); // hethi teb3a les taches mta3 minimap lil init mask bich njm nml collision
void printBestScores(scoreinfo scores[]);
void displayScore(SDL_Surface *screen, TTF_Font *font, perso p);
#endif
