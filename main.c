#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 800

int main() {
if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
printf("SDL initialization failed: %s\n", SDL_GetError());
return 1;
}
SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
if (screen == NULL) {
printf("Failed to set video mode: %s\n", SDL_GetError());
SDL_Quit();
return 1;
}
bg background;
initbg(&background);
image heart;
imgheart(&heart);
Mix_Music *bgMusic;
musicLoad1(bgMusic);
int quit = 0;
int scrollingRight = 0, scrollingLeft = 0, scrollingUp = 0, scrollingDown = 0;
SDL_Event event;
while (!quit) 
{
while (SDL_PollEvent(&event)) 
{
if (event.type == SDL_QUIT) 
{
quit = 1;
}
else if (event.type == SDL_KEYDOWN) 
{
switch (event.key.keysym.sym) 
{
case SDLK_RIGHT:
scrollingRight = 1;
break;
case SDLK_LEFT:
scrollingLeft = 1;
break;
case SDLK_UP:
scrollingUp = 1;
break;
case SDLK_DOWN:
scrollingDown = 1;
break;
}
}
else if (event.type == SDL_KEYUP) 
{
switch (event.key.keysym.sym) 
{
case SDLK_RIGHT:
scrollingRight = 0;
break;
case SDLK_LEFT:
scrollingLeft = 0;
break;
case SDLK_UP:
scrollingUp = 0;
break;
case SDLK_DOWN:
scrollingDown = 0;
break;
}
}
}
if (scrollingRight) 
{
scrolling(&background, 0, 10, 0); 
}
if (scrollingLeft) 
{
scrolling(&background, 1, 10, 0); 
}
if (scrollingUp) 
{
scrolling(&background, 2, 0, 10); 
}
if (scrollingDown)
{
scrolling(&background, 3, 0, 10); 
}
SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
afficherbg(&background, screen);
afficherheart(&heart, screen);
SDL_Flip(screen);
SDL_Delay(10);
}
Mix_FreeMusic(bgMusic);
SDL_Quit();
return 0;
}


