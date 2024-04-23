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
void imgheart(image *i){
i->img= IMG_Load("heart.png");
i->imgp.x=0;
i->imgp.y=0;
i->imgs.x=10;
i->imgs.y=10;
i->imgs.w=100;
i->imgs.h=100;
}
void imgheart2(image *i){
i->img= IMG_Load("heart.png");
i->imgp.x=500;
i->imgp.y=0;
i->imgs.x=10;
i->imgs.y=10;
i->imgs.w=100;
i->imgs.h=100;
}
void afficherheart(image *i, SDL_Surface *screen){
SDL_BlitSurface(i->img, &i->imgs, screen, &i->imgp);
}
void afficherbg(bg *b, SDL_Surface *screen)
{
SDL_BlitSurface(b->img, &b->imgs, screen, &b->imgp);
}
void musicLoad1(Mix_Music *music)
{
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
{
printf("%s", Mix_GetError());
}
music = Mix_LoadMUS("mgs.mp3");
if (music == NULL)
{
printf("unable to load music Error: %s.\n", Mix_GetError());
return;
}
Mix_PlayMusic(music, -1);
Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

void scrolling(bg *b, int direction, int dx, int dy)
{
if (direction == 0) 
{
b->imgs.x += dx;
if (b->imgs.x + b->imgs.w > b->img->w) 
{
b->imgs.x = b->img->w - b->imgs.w;
}
}
else if (direction == 1) 
{
b->imgs.x -= dx;
if (b->imgs.x < 0) 
{
b->imgs.x = 0;
}
}
else if (direction == 2) 
{
b->imgs.y -= dy;
if (b->imgs.y < 0) 
{
b->imgs.y = 0;
}
}
else if (direction == 3) 
{

b->imgs.y += dy;
if (b->imgs.y + b->imgs.h > b->img->h) 
{
b->imgs.y = b->img->h - b->imgs.h;
}
}
}

/*
void backgroundAnimate(SDL_Surface *screen, image *img)
{
int frame = 0;
Uint32 last_time = 0;
Uint32 current_time = SDL_GetTicks();
if (current_time > last_time + 200)
{+
frame++;
if (frame >= 5)
{
frame = 0;
}
img->img_size.x = frame * (img->img->w / 5);
last_time = current_time;
}
}
*/
void splitscreen(SDL_Surface *screen, bg *b) 
{
int screen_width = screen->w / 2;
int screen_height = screen->h;
SDL_Rect screen1_rect = {0, 0, screen_width, screen_height};
SDL_Rect screen2_rect = {screen_width, 0, screen_width, screen_height};
SDL_BlitSurface(b->img, &(b->imgs), screen, &screen1_rect);
SDL_BlitSurface(b->img, &(b->imgs), screen, &screen2_rect);
}




