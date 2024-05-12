#include "perso.h"
/**
* @file main.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for perso
*
*/
void quit(int * q) {
  Uint8 * keystate = SDL_GetKeyState(NULL);
  if (keystate[SDLK_ESCAPE])( * q) = 1;
}
int main() {
  perso p1, p2;
  init_perso( & p1);
  init_perso_controls( & p1);
  init_images_perso(& p1,"spritesheet.png");
  init_perso( & p2);
  init_perso_controls_p2( & p2);
  init_images_perso(& p2,"spritesheet.png");
  SDL_Init(SDL_INIT_EVERYTHING);
  TTF_Init();
  SDL_Surface * screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
  SDL_Surface * bg;
  bg = IMG_Load("bg.png");
  int q = 0;
  while (q == 0) {
    SDL_PumpEvents();
    quit( & q);
    SDL_Delay(60);
    SDL_BlitSurface(bg, NULL, screen, NULL);
    afficher_perso(p1, screen);
    afficher_score_vie(p1, screen, 0);
    animer_perso( & p1);
    move_perso( & p1);
    player_limite( & p1, screen);
    saut_perso( & p1);
    afficher_perso(p2, screen);
    afficher_score_vie(p2, screen, 1);
    animer_perso( & p2);
    move_perso( & p2);
    player_limite( & p2, screen);
    saut_perso( & p2);
    SDL_Flip(screen);
  }
}
