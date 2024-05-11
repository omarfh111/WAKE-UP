#include "perso.h"

#include <stdio.h>

#define ACCELERATION 1.5
#define LIM_LEFT 50
#define LIM_RIGHT 150	
/**
* @file perso.c
* @brief Testing Program.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Testing program for perso
*
*/
/**
* @brief To initialize the perso p .
* @param p the perso
* @return Nothing
*/
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
  ( *p).state = idle;
  ( *p).sprite_num = 0;
}
/**
* @brief To mouve the perso p1 .
* @param p the perso
* @return Nothing
*/
void init_perso_controls(perso * p) {
  ( *p).keys.left = SDLK_LEFT;
  ( *p).keys.right = SDLK_RIGHT;
  ( *p).keys.jump = KMOD_LCTRL;
}
/**
* @brief To mouve the perso p2 .
* @param p the perso
* @return Nothing
*/
void init_perso_controls_p2(perso * p) {
  ( *p).keys.left = SDLK_q;
  ( *p).keys.right = SDLK_d;
  ( *p).keys.jump = KMOD_LALT;
}
/**
* @brief To initialize  sprite the perso p .
* @param p the perso
* @return Nothing
*/
void init_images_perso(perso * p,char *name) {
  ( *p).image = IMG_Load(name);
  ( *p).pos.w = ( *p).image->w/4;
  ( *p).pos.h = ( *p).image->h/4;
}
/**
* @brief To show the perso p .
* @param p the perso
* @param screen the screen
* @return Nothing
*/
void afficher_perso(perso p, SDL_Surface * screen) {
  SDL_BlitSurface(p.image, & p.sprite, screen, & p.pos);
}
/**
* @brief To initialize the perso p .
* @param p the perso
* @param screen the screen
* @param n the var for detection
* @return Nothing
*/
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
    pos.y -= 10;
    s = SDL_CreateRGBSurface(0, p.pos.w * p.vie / 100, 10, 32, 0, 0, 0, 10);
    SDL_FillRect(s, NULL, SDL_MapRGB(s -> format, 100 + 155 * n, 0, 0));
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
/**
* @brief To animate the perso p .
* @param p the perso
* @return Nothing
*/
void animer_perso(perso * p) {

  (*p).sprite.w = (*p).image->w / 4;
  (*p).sprite.h = (*p).image->h / 4;
  (*p).sprite_num++;

  if (( *p).sprite_num > 3)( *p).sprite_num = 0;
  (*p).sprite.x = ( *p).sprite.w * ( *p).sprite_num;
  (*p).sprite.y = ( *p).sprite.h * ( *p).state;
  //if (( *p).d==2) ( *p).sprite.y+= ( *p).sprite.h * 3;
}
/**
* @brief To mouve the perso p .
* @param p the perso
* @return Nothing
*/
void move_perso(perso * p) {
  Uint8 * keystate = SDL_GetKeyState(NULL);
  if (keystate[( *p).keys.right]) {
    if (( *p).d == 1) {
      if (( *p).speed < 20)( *p).speed = 1 + ( *p).speed * ACCELERATION;
    } else( *p).speed = 5;
    ( *p).d = 1;
    ( *p).state = walk;
  } else if (keystate[( *p).keys.left]) {
    if (( *p).d == 1) {
      if (( *p).speed < 20)( *p).speed = 1 + ( *p).speed * ACCELERATION;
    } else( *p).speed = 5;
    ( *p).d = 2;
    ( *p).state = walk2;
  } else {
    ( *p).state = idle;
    ( *p).speed = 0;
  }
if (keystate[( *p).keys.right])( *p).pos.x += ( *p).speed;
  else( *p).pos.x -= ( *p).speed;
  ( *p).pos.y -= 20 * ( *p).jump;
  if((*p).d==1)
   (*p).pos.x+=2*(*p).jump*(*p).jump;
   else
   (*p).pos.x-=2*(*p).jump*(*p).jump;
}
/**
* @brief To jump the perso p .
* @param p the perso
* @return Nothing
*/
void saut_perso(perso * p) {
  SDLMod modstate = SDL_GetModState();
  if (modstate == 4096 + ( *p).keys.jump)
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
/**
* @brief To lim the perso p .
* @param p the perso
* @return Nothing
*/
void player_limite(perso * p, SDL_Surface * screen) {
  if (( *p).state != 0) {
    if (( *p).pos.x < LIM_LEFT)( *p).pos.x = LIM_LEFT;
    if (( *p).pos.x > ( * screen).w - LIM_RIGHT)( *p).pos.x = ( * screen).w - LIM_RIGHT;
  }
}
