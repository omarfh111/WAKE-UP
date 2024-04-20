#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"

int main() 
{
bg background;
initbg(&background);
if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) 
{
printf("SDL initialization failed: %s\n", SDL_GetError());
return 1;
}
if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) 
{
printf("SDL_mixer initialization failed: %s\n", Mix_GetError());
return 1;
}
SDL_Surface *screen = SDL_SetVideoMode(1000, 800, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
if (screen == NULL) 
{
printf("Failed to set video mode: %s\n", SDL_GetError());
return 1;
}
Mix_Music *bgMusic = Mix_LoadMUS("mgs.mp3");
if (bgMusic == NULL) 
{
printf("Failed to load music: %s\n", Mix_GetError());
} else 
{
Mix_PlayMusic(bgMusic, -1);
}
int quit = 0;
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
scrolling(&background, 0, 10, 0);
break;
case SDLK_LEFT:
scrolling(&background, 1, 10, 0);
break;
case SDLK_UP:
scrolling(&background, 2, 0, 10);
break;               
case SDLK_DOWN:
scrolling(&background, 3, 0, 10);
break;
default:
break;
}
}
}
SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
afficherbg(&background, screen);
SDL_Flip(screen);
SDL_Delay(10);
}
Mix_FreeMusic(bgMusic);
SDL_Quit();
return 0;
}
