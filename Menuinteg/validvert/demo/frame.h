// frame.h
#ifndef FRAME_H
#define FRAME_H

#include <SDL/SDL.h>

#define SCREEN_W 1938
#define SCREEN_H 1115

typedef struct
{
    SDL_Rect pos1;
    SDL_Rect pos2;
    SDL_Surface *img;
} image;

void initFrame(image *frame, char name[]);
void libererFrame(image frame);
void afficherFrame(image frame, SDL_Surface *screen);

#endif // FRAME_H

