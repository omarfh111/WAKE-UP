#ifndef _PERSO_H_
#define _PERSO_H_
#include <SDL/SDL_image.h>

#include <SDL/SDL.h>

#include <SDL/SDL_ttf.h>

#include "controls.h"
/**
* @struct perso
* @brief struct for perso
*/ 
enum state {
  idle,	 /*!< mou init*/
  walk,	 /*!< mouv 1*/
  walk2,/*!< mouve 2*/
  jump	 /*!< saut*/
};
typedef struct {
  int health;	 /*!< health*/
  int score;	/*!< score*/
  int vie;	/*!< vie*/
  int speed;	/*!< speed*/
  int jump;	/*!< jump*/
  keymapping keys;	
  SDL_Rect pos;	/*!< rectangle*/
  SDL_Rect sprite;	/*!< rectangle*/
  enum state state;	/*!< stat*/
  int d; 
  SDL_Surface * image;	/*!< surface*/
  int sprite_num;
  double scale;
}
perso;
void init_images_perso(perso * p,char *name);
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
