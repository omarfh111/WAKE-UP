#ifndef MINIMAP_H
#define MINIMAP_H

#include <SDL/SDL.h>

typedef struct {
    SDL_Surface *miniatureImage;
    SDL_Rect miniaturePosition;
    SDL_Surface *playerImage;
    SDL_Rect playerPosition;
    SDL_Surface *enemyImage;
    SDL_Rect enemyPosition;
    SDL_Surface *puzzleImage;
    SDL_Rect puzzlePosition;
} Minimap;

void InitializeMinimap(Minimap *minimap, SDL_Surface *miniatureImage, SDL_Rect miniaturePosition,
                       SDL_Surface *playerImage, SDL_Rect playerPosition,
                       SDL_Surface *enemyImage, SDL_Rect enemyPosition,
                       SDL_Surface *puzzleImage, SDL_Rect puzzlePosition);

void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, SDL_Rect camera,
                   int resizingFactor);

void DisplayMinimap(Minimap *minimap, SDL_Surface *screen);

void FreeMinimap(Minimap *minimap);

SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y);
int CollisionParfaite(SDL_Surface *backgroundMasque, SDL_Rect posPerso);

void affichertemps(int temps);

#endif /* MINIMAP_H */

