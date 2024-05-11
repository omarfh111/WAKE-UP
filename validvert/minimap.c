/**
* @file minimap.c
*/

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "minimap.h"


/**
* @brief pour intialiser minimap
* @param minimap variable de structure parametre
* @param screen ecran d'affichage
* @param minimapWidth minimapHeight longeur et largeur du minimap
* @return no return
*/


void InitializeMinimap(Minimap *minimap, SDL_Surface *screen, int minimapWidth, int minimapHeight) {
    minimap->miniatureImage = IMG_Load("back.png");
    minimap->playerImage = IMG_Load("red.png");
    //minimap->enemyImage = IMG_Load("blue.png");
    //minimap->puzzleImage = IMG_Load("yellow.png");

    if (!minimap->miniatureImage || !minimap->playerImage ||
        !minimap->enemyImage || !minimap->puzzleImage) {
        printf("Failed to load one or more images: %s\n", IMG_GetError());
        return; 
    }

    minimap->miniaturePosition.x = 10;
    minimap->miniaturePosition.y = 10;
    minimap->playerPosition.x = minimapWidth / 4;
    minimap->playerPosition.y = minimapHeight / 4;
    minimap->enemyPosition.x = minimapWidth / 2;
    minimap->enemyPosition.y = minimapHeight / 2;
    minimap->puzzlePosition.x = minimapWidth * 3 / 4;
    minimap->puzzlePosition.y = minimapHeight * 3 / 4;
}


/**
* @brief pour faire mise a jour des positions des entites sur minimap
* @param minimap variable de structure parametre
* @param playerAbsolutePosition c'est la position du joueur sur ecran(sure background)
* @param minimapWidth minimapHeight longeur et largeur du minimap
* @param resizingFactor le redefinition de la taille des entites sur minimap selon une valeur defini
* @return no return
*/

void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, int resizingFactor, int screenWidth, int screenHeight) {
    int playerXOnMap, playerYOnMap;
    float scaleFactor = 0.265;

    playerXOnMap = (playerAbsolutePosition.x * minimap->miniaturePosition.w) / screenWidth;
    playerYOnMap = (playerAbsolutePosition.y * minimap->miniaturePosition.h) / screenHeight;
	
    playerXOnMap *= scaleFactor;

    minimap->playerPosition.x = playerXOnMap;
    minimap->playerPosition.y = playerYOnMap;
}




/**
* @brief affichage minimap sur ecran
* @param minimap variable de structure parametre
* @param screen ecran d'affichage
* @return no return
*/

void DisplayMinimap(Minimap *minimap, SDL_Surface *screen) {
    // Set black color as transparent for minimap background
    SDL_SetColorKey(minimap->miniatureImage, SDL_SRCCOLORKEY, SDL_MapRGB(minimap->miniatureImage->format, 0, 0, 0));


    SDL_BlitSurface(minimap->miniatureImage, NULL, screen, &minimap->miniaturePosition);


    SDL_BlitSurface(minimap->playerImage, NULL, screen, &minimap->playerPosition);
/*
    // Blit enemy if it exists
    if (minimap->enemyImage != NULL) {
        SDL_BlitSurface(minimap->enemyImage, NULL, screen, &minimap->enemyPosition);
    }*/

    // Blit puzzle if it exists
   /* if (minimap->puzzleImage != NULL) {
        SDL_BlitSurface(minimap->puzzleImage, NULL, screen, &minimap->puzzlePosition); 
    } */

    SDL_Flip(screen);
}

/**
* @brief liberation 
* @param minimap variable de structure parametre
* @return no return
*/

void FreeMinimap(Minimap *minimap) {
    SDL_FreeSurface(minimap->miniatureImage);
    minimap->miniatureImage = NULL;

    SDL_FreeSurface(minimap->playerImage);
    minimap->playerImage = NULL;

    SDL_FreeSurface(minimap->enemyImage);
    minimap->enemyImage = NULL;

    SDL_FreeSurface(minimap->puzzleImage);
    minimap->puzzleImage = NULL;
}


//de l'atelier
SDL_Color GetPixel(SDL_Surface *pSurface,int x,int y) 
{ SDL_Color color; Uint32 col=0; 
char* pPosition=(char* ) pSurface->pixels; 
pPosition+= (pSurface->pitch * y); 
pPosition+= (pSurface->format->BytesPerPixel *x); 
memcpy(&col ,pPosition ,pSurface->format->BytesPerPixel); 
 SDL_GetRGB(col,pSurface->format, &color.r, &color.g, &color.b);
  return (color);
  }
 
 
/**
* @brief detection collision character avec obstacles horizontale 
* @param backgroundmasque variable contenant la masque des obstacles
* @param posPerso position du personnage sur background
* @return 1 si collision 0 si non collision
*/  
  
int CollisionHorizontale(SDL_Surface *backgroundMasque, SDL_Rect posPerso) {
    // Coordinates of the 8 points around the character
    int pointsX[] = { posPerso.x, posPerso.x + posPerso.w / 2, posPerso.x + posPerso.w,
                      posPerso.x, posPerso.x, posPerso.x + posPerso.w / 2,
                      posPerso.x + posPerso.w, posPerso.x + posPerso.w };
    int pointsY[] = { posPerso.y, posPerso.y, posPerso.y,
                      posPerso.y + posPerso.h / 2, posPerso.y + posPerso.h,
                      posPerso.y + posPerso.h, posPerso.y + posPerso.h,
                      posPerso.y + posPerso.h / 2 };

    for (int i = 0; i < 8; i++) {
        SDL_Color color = GetPixel(backgroundMasque, pointsX[i], pointsY[i]);

        if (color.r == 233 && color.g == 230 && color.b == 32) {
            return 1; 
        }
    }

    return 0; 
}
/**
* @brief detection collision character avec obstacles vertical 
* @param backgroundmasque variable contenant la masque des obstacles
* @param posPerso position du personnage sur background
* @return 1 si collision 0 si non collision
*/ 

int CollisionVerticale(SDL_Surface *backgroundMasque, SDL_Rect posPerso) {

    int pointsX[] = { posPerso.x, posPerso.x + posPerso.w / 2, posPerso.x + posPerso.w,
                      posPerso.x, posPerso.x, posPerso.x + posPerso.w / 2,
                      posPerso.x + posPerso.w, posPerso.x + posPerso.w };
    int pointsY[] = { posPerso.y, posPerso.y, posPerso.y,
                      posPerso.y + posPerso.h / 2, posPerso.y + posPerso.h,
                      posPerso.y + posPerso.h, posPerso.y + posPerso.h,
                      posPerso.y + posPerso.h / 2 };

    for (int i = 0; i < 8; i++) {
        SDL_Color color = GetPixel(backgroundMasque, pointsX[i], pointsY[i]);

        if (color.r == 142 && color.g == 74 && color.b == 157) {
            return 1; 
        }
    }
    return 0; 
}

/**
* @brief affichage de temps du niveau
* @param tempsDebut le moment du lancement de l'enigme
* @param dureeTotale duree de l'enigme
* @param screen ecran d'affichage
* @param font font du texte du temps
* @return no return
*/ 

void afficherTempsLevel(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font) {
    int temps_ecoule = (SDL_GetTicks() - tempsDebut) / 1000; 
    int temps_restant = (dureeTotale / 1000) - temps_ecoule; 

    char tempsText[100];
    
    if (temps_restant <= 0) {
        sprintf(tempsText, "Level Time: %d seconds, time is up", temps_ecoule);
    } else {
        sprintf(tempsText, "Level Time: %d seconds||Remaining Time: %d seconds", temps_ecoule, temps_restant);
    }
    
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, tempsText, textColor);
    SDL_Rect textRect = { 10, 10, 0, 0 }; 
    
    SDL_BlitSurface(textSurface, NULL, screen, &textRect); 
    SDL_FreeSurface(textSurface); 
}

/**
* @brief affichage de temps du niveau
* @param tempsDebut le moment du lancement du niveau
* @param dureeTotale duree du niveau
* @param screen ecran d'affichage
* @param font font du texte du temps
* @return no return
*/ 
void afficherTempsPuzzle(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font) {
    int temps_ecoule = (SDL_GetTicks() - tempsDebut) / 1000; 
    int temps_restant = dureeTotale - temps_ecoule;
    char tempsText[100];
    
    if (temps_restant <= 0) {
        sprintf(tempsText, "Puzzle Time: %d seconds", temps_ecoule);
    } else {
        sprintf(tempsText, "Remaining Puzzle Time: %d seconds", temps_restant);
    }
    
    SDL_Color textColor = { 255, 255, 255 }; 
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, tempsText, textColor);
    SDL_Rect textRect = { 10, 50, 0, 0 }; 
    
    SDL_BlitSurface(textSurface, NULL, screen, &textRect); 
    SDL_FreeSurface(textSurface); 
}



/**
* @brief animation minimap
* @param m variable de type minimap
* @param dotImage1 image 1 pour animation de l'enigme
* @param dotImage2 image 2 pour animation de l'enigme
* @return no return
*/ 
void animerMinimap(Minimap *m, SDL_Surface *dotImage1, SDL_Surface *dotImage2) {

    SDL_Rect dotRect = { 900, 100, dotImage1->w, dotImage1->h };
    int animationDelay = 100; 

    int blink = 0;

    while (1) {
        // Clear the area where the dot will be drawn
        SDL_FillRect(m->miniatureImage, &dotRect, SDL_MapRGB(m->miniatureImage->format, 0, 0, 0));

        if (blink == 0) {
            SDL_BlitSurface(dotImage1, NULL, m->miniatureImage, &dotRect);
            blink = 1;
        } else {
    
            
            SDL_BlitSurface(dotImage2, NULL, m->miniatureImage, &dotRect);
            blink = 0;
        }
        SDL_Flip(m->miniatureImage);
        SDL_Delay(animationDelay);
    }
}


