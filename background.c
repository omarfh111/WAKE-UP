#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
void initbg(bg *b){
b->img= IMG_Load("screen1.jpg");
b->imgp.x=0;
b->imgp.y=0;
b->imgs.x=0;
b->imgs.y=200;
b->imgs.w=1000;
b->imgs.h=800;
}

void initmask(bg *b)
{
b->img= IMG_Load("mask.png");
b->imgp.x=0;
b->imgp.y=0;
b->imgs.x=0;
b->imgs.y=200;
b->imgs.w=1000;
b->imgs.h=800;
}


void afficherbg(bg *b, SDL_Surface *screen){
SDL_BlitSurface(b->img, &b->imgs, screen, &b->imgp);

}
void scrolling(bg *b, int direction, float dx, float dy)
{
if (direction == 0)
{
b->imgs.x = dx;
if (b->imgs.x + b->imgs.w > b->img->w)
{
b->imgs.x = b->img->w - b->imgs.w;
}
}
else if (direction == 1)
{
b->imgs.x = dx;
if (b->imgs.x < 0)
{
b->imgs.x = 0;
}
}
else if (direction == 2)
{
b->imgs.y = dy;
if (b->imgs.y < 0)
{
b->imgs.y = 0;
}
}
else if (direction == 3)
{

b->imgs.y = dy;
if (b->imgs.y + b->imgs.h > b->img->h)
{
b->imgs.y = b->img->h - b->imgs.h;
}
}
}






