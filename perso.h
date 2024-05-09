#ifndef _PERSO_H_
#define _PERSO_H_
#include <SDL/SDL_image.h>

#include <SDL/SDL.h>

#include <SDL/SDL_ttf.h>

#include "controls.h"

enum state {
  idle,
  walk,
  walk2,
  jump
};
typedef struct {
  int health;
  int score;
  int vie;
  int speed;
  int jump;
  keymapping keys;
  SDL_Rect pos;
  SDL_Rect sprite;
  enum state state;
  int d; 
  SDL_Surface * image;
  int sprite_num;
  double scale;
}
perso;
void init_images_perso(perso * p);
void init_perso(perso * p);
void init_perso_controls(perso * p);
void afficher_perso(perso p, SDL_Surface * screen);
void afficher_score_vie(perso p, SDL_Surface * screen, int n);
void animer_perso(perso * p);
void move_perso(perso * p);
void player_limite(perso * p, SDL_Surface * screen);
void saut_perso(perso * p);
void init_perso_controls_p2(perso * p);

#endif
