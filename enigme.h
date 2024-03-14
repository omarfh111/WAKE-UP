#ifndef ENIGME_H_INCLUDED
#define ENIGME_H_INCLUDED
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
typedef struct {
     char question[100];
     char reponse1[100];
     char reponse2[100];
     char reponse3[100];
    SDL_Rect questionl;
    SDL_Rect reponsel;
    SDL_Rect textl;
    TTF_Font *font;
    SDL_Surface* screen;
    SDL_Color textColor;
    SDL_Color textg;
    SDL_Color texty;
    SDL_Color textr;
} Enigme;
void afficherEnigme(Enigme e, SDL_Surface* screen, TTF_Font* font, SDL_Color textColor);
void genererEnigme(Enigme* p, char* nomfichier);
void animerEnigme(Enigme * e);
#endif // ENIGME_H_INCLUDED
