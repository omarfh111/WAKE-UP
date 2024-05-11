
/**
* @file minimap.h
*/
#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
/**
* @struct Minimap
* @brief structure for minimap
*/

typedef struct {
    SDL_Surface *miniatureImage;   /*!< image du minimap*/
    SDL_Rect miniaturePosition;     /*!< position du minimap*/
    SDL_Surface *playerImage;		/*!< image du joueur sur minimap*/
    SDL_Rect playerPosition;		/*!< position du joueur sur minimap*/
    SDL_Surface *enemyImage;		/*!< image du joueur sur minimap*/
    SDL_Rect enemyPosition;		/*! <position enemy sure minimap*/
    SDL_Surface *puzzleImage;		/*!< image du puzzle sur minimap*/
    SDL_Rect puzzlePosition;		/*! <position puzzle sure minimap*/
}Minimap;

void InitializeMinimap(Minimap *minimap, SDL_Surface *screen, int minimapWidth, int minimapHeight);

void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, int resizingFactor, int screenWidth, int screenHeight);
void DisplayMinimap(Minimap *minimap, SDL_Surface *screen);

void FreeMinimap(Minimap *minimap);

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int CollisionHorizontale(SDL_Surface *backgroundMasque, SDL_Rect posPerso);
int CollisionVerticale(SDL_Surface *backgroundMasque, SDL_Rect posPerso);


void afficherTempsLevel(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font);
void afficherTempsPuzzle(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font);
void animerMinimap(Minimap *m, SDL_Surface *dotImage1, SDL_Surface *dotImage2);

#endif /* MINIMAP_H */

