#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "background.h"
#include "perso.h"
typedef struct {
    SDL_Surface *miniatureImage;
    SDL_Rect miniaturePosition;
    SDL_Surface *playerImage;
    SDL_Rect playerPosition;
    SDL_Surface *enemyImage;
    SDL_Rect enemyPosition;
    SDL_Surface *puzzleImage;
    SDL_Rect puzzlePosition;
}Minimap;

void InitializeMinimap(Minimap *minimap, SDL_Surface *screen, int minimapWidth, int minimapHeight);

void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, int resizingFactor, int screenWidth, int screenHeight);
void DisplayMinimap(Minimap *minimap, SDL_Surface *screen);

void FreeMinimap(Minimap *minimap);

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int CollisionHorizontale(SDL_Surface *backgroundMasque, SDL_Rect posPerso);
int CollisionVerticale(SDL_Surface *backgroundMasque, SDL_Rect posPerso);


void afficherTempsLevel(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font);
//void afficherTempsPuzzle(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font);
void animerMinimap(Minimap *m, SDL_Surface *dotImage1, SDL_Surface *dotImage2);

void sauvegarder(perso p, bg b, char *nomfichier);
void charger(perso *p, bg *b, char *nomfichier);

#endif /* MINIMAP_H */

