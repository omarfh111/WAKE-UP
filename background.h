#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
}image;
void imgheart2(image *i);
void musicLoad1(Mix_Music *music);
void soundeffect(Mix_Chunk *sound);
void initbg(bg *b, char *filename);
void afficherbg(bg *b, SDL_Surface *screen);
void animerbg(SDL_Surface *screen,SDL_Surface *img);
void scrolling(bg *b, int direction, int dx, int dy);
void savescore(scoreinfo s,char *filename);
void loadbestscore(char *filename, scoreinfo scores[]);
void displayScores(SDL_Surface *screen, scoreinfo scores[]);
void splitscreen(SDL_Surface *screen,bg *b);
void afficherheart(image *i, SDL_Surface *screen);
void imgheart(image *i);

#endif

