#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
typedef struct{
SDL_Rect imgp;
SDL_Rect imgs;
SDL_Surface *img;
int scrollingspeed;
SDL_Rect camerapos;
int direction;
}bg;
typedef struct{
int score;
int temps;
char palyername[20];
}scoreinfo;
void initbg(bg *b);
void afficherbg(bg *b, SDL_Surface *screen);
void animatebg(SDL_Surface *screen,SDL_Surface *img);
void scrolling(bg *b, int direction, int dx, int dy,float speed);
void savescore(scoreinfo s,char *filename);;
void loadbestscore(char *filename, scoreinfo t[]);
void displayscore(SDL_Surface *screen, scoreinfo t[]);
void splitscreen(SDL_Surface *screen,SDL_Surface *lvl);

#endif

