#include "perso.h"
#include <stdio.h>
#define ACCELERATION 1.5
#define LIM_LEFT 600
#define LIM_RIGHT 600	

void init_perso(perso * p) {
  ( *p).health = 0;
  ( *p).score = 1000;
  ( *p).vie = 100;
  ( *p).d = 1;
  ( *p).jump = 0;
  ( *p).pos.x = 50;
  ( *p).pos.y = 580;
  ( *p).sprite.x = 0;
  ( *p).sprite.y = 0;
  ( *p).sprite.w = ( *p).image->w * (*p).scale;
  ( *p).sprite.h = ( *p).image->h * (*p).scale;
  ( *p).state = idle;
  ( *p).sprite_num = 0;
  (*p).scale = 7000;
  ( *p).image = IMG_Load("spritesheet.png");
  ( *p).pos.w = ( *p).image->w /4;
  ( *p).pos.h = ( *p).image->h /4;
}

void afficher_perso(perso p, SDL_Surface * screen) {
  SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);
}

void afficher_score_vie(perso p, SDL_Surface * screen, int n) {
  if (p.pos.x + p.pos.w > 0) {
    TTF_Font * font = TTF_OpenFont("fonts/score.ttf", 25);
    SDL_Color color = {
      255 * n,
      255,
      255
    };
    SDL_Surface * text, * s;
    SDL_Rect pos = p.pos;
    pos.x+=10;
    pos.y -= 10;
    s = SDL_CreateRGBSurface(0, p.pos.w * p.vie / 100, 10, 32, 0, 0, 0, 10);
    SDL_FillRect(s, NULL, SDL_MapRGB(s -> format,255, 0, 0));
    char ch[15];
    sprintf(ch, "%d", p.score);
    text = TTF_RenderText_Solid(font, ch, color);
    SDL_BlitSurface(s, NULL, screen, & pos);
    pos.y -= 25;
    SDL_BlitSurface(text, NULL, screen, & pos);
    TTF_CloseFont(font);
    font = NULL;
    SDL_FreeSurface(text);
    text = NULL;
    SDL_FreeSurface(s);
    s = NULL;
  }
}

void animer_perso(perso * p) {

  (*p).sprite.w = (*p).image->w / 4;
  (*p).sprite.h = (*p).image->h / 4;
  (*p).sprite_num++;

  if (( *p).sprite_num > 3)( *p).sprite_num = 0;
  (*p).sprite.x = ( *p).sprite.w * ( *p).sprite_num;
  (*p).sprite.y = ( *p).sprite.h * ( *p).state;
  //if (( *p).d==2) ( *p).sprite.y+= ( *p).sprite.h * 3;
}

void move_perso(perso * p) {
  Uint8 * keystate = SDL_GetKeyState(NULL);
  if (keystate[SDLK_RIGHT]) {
    if (( *p).d == 1) {
      if (( *p).speed < 20)( *p).speed = 1 + ( *p).speed *ACCELERATION;
    } else( *p).speed = 5;
    ( *p).d = 1;
    ( *p).state = walk;
  } else if (keystate[SDLK_LEFT]) {
    if (( *p).d == 1) {
      if (( *p).speed < 20)( *p).speed = 1 + ( *p).speed * ACCELERATION;
    } else( *p).speed = 5;
    ( *p).d = 1;
    ( *p).state = walk2;
  } else {
    ( *p).state = idle;
    ( *p).speed = 0;
  }
  if (keystate[SDLK_RIGHT])( *p).pos.x += ( *p).speed;
  else( *p).pos.x -= ( *p).speed;
  ( *p).pos.y -= 20 * ( *p).jump;
}

void saut_perso(perso * p) {
  SDLMod modstate = SDL_GetModState();
  if (modstate == 4096 + KMOD_LCTRL)
    if (( *p).jump == 0)( *p).jump = 1;
  if (( *p).jump > 0) {
    ( *p).state = jump;
    if (( *p).jump < 4)( *p).jump++;
    else( *p).jump = -1;
  }
  if (( *p).jump < 0) {
    ( *p).state = jump;
    if (( *p).jump > -4)( *p).jump--;
    else( *p).jump = 0;
  }
}

void player_limite(perso * p,SDL_Surface * screen){
    if(( *p).state !=0){
       if(( *p).pos.x < LIM_LEFT)( *p).pos.x =LIM_LEFT;
       if(( *p).pos.x > ( * screen).w - LIM_RIGHT)( *p).pos.x =( * screen).w - LIM_RIGHT;
    }
}
