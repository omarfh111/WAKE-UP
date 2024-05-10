// frame.c
#include "frame.h"
#include <SDL/SDL_image.h>
#include <stdio.h>

void initFrame(image *frame, char name[])
{
    frame->img = IMG_Load(name);
    if (frame->img == NULL)
    {
        fprintf(stderr, "Unable to load image %s\n", name);
        exit(EXIT_FAILURE);
    }

    frame->pos1.x = 0;
    frame->pos1.y = 0;
    frame->pos2.x = 0;
    frame->pos2.y = 0;
    frame->pos2.w = SCREEN_W;
    frame->pos2.h = SCREEN_H;
}

void libererFrame(image frame)
{
    SDL_FreeSurface(frame.img);
}

void afficherFrame(image frame, SDL_Surface *screen)
{
    SDL_BlitSurface(frame.img, &frame.pos2, screen, &frame.pos1);
}

