#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include "minimap.h"

void InitializeMinimap(Minimap *minimap, SDL_Surface *screen, int minimapWidth, int minimapHeight) {
    minimap->miniatureImage = IMG_Load("mini.png");
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




void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, int resizingFactor, int screenWidth, int screenHeight) {
    int playerXOnMap, playerYOnMap;
    float scaleFactor = 0.265;


    playerXOnMap = (playerAbsolutePosition.x * minimap->miniaturePosition.w) / screenWidth;
    playerYOnMap = (playerAbsolutePosition.y * minimap->miniaturePosition.h) / screenHeight;
	
	playerXOnMap *= scaleFactor;

    minimap->playerPosition.x = playerXOnMap;
    minimap->playerPosition.y = playerYOnMap;
}









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
  
  
int CollisionHorizontale(SDL_Surface *backgroundMasque, SDL_Rect posPerso) {

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
            return 1; // Collision detected
        }
    }

    return 0; // No collision detected
}

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
            return 1; // Collision detected
        }
    }

    return 0; // No collision detected
}



void afficherTempsLevel(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font) {
    int temps_ecoule = (SDL_GetTicks() - tempsDebut) / 1000; // Elapsed time in seconds
    int temps_restant = (dureeTotale / 1000) - temps_ecoule; // Remaining time in seconds

    char tempsText[100];
    
    if (temps_restant <= 0) {
        sprintf(tempsText, "Level Time: %d seconds", temps_ecoule);
    } else {
        sprintf(tempsText, "Level Time: %d seconds\nRemaining Time: %d seconds", temps_ecoule, temps_restant);
    }
    
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, tempsText, textColor);
    SDL_Rect textRect = { 10, 10, 0, 0 }; // Position to render the text
    
    SDL_BlitSurface(textSurface, NULL, screen, &textRect); // Blit text onto the screen
    SDL_FreeSurface(textSurface); // Free the text surface
}





// Function to calculate and display the remaining time for a puzzle
void afficherTempsPuzzle(int tempsDebut, int dureeTotale, SDL_Surface *screen, TTF_Font *font) {
    int temps_ecoule = (SDL_GetTicks() - tempsDebut) / 1000; 
    int temps_restant = dureeTotale - temps_ecoule;
    char tempsText[100];
    
    if (temps_restant <= 0) {
        sprintf(tempsText, "Puzzle Time: %d seconds", temps_ecoule);
    } else {
        sprintf(tempsText, "Remaining Puzzle Time: %d seconds", temps_restant);
    }
    
    SDL_Color textColor = { 255, 255, 255 }; // White color
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, tempsText, textColor);
    SDL_Rect textRect = { 10, 50, 0, 0 }; // Position to render the text
    
    SDL_BlitSurface(textSurface, NULL, screen, &textRect); // Blit text onto the screen
    SDL_FreeSurface(textSurface); // Free the text surface
}

void animerMinimap(Minimap *m, SDL_Surface *dotImage1, SDL_Surface *dotImage2) {
    // Coordinates of the blinking dot
    SDL_Rect dotRect = { 900, 100, dotImage1->w, dotImage1->h };
    int animationDelay = 100; // Adjust as needed for blinking speed

    // Variable to switch between images for blinking effect
    int blink = 0;

    // Animation loop
    while (1) {
        // Clear the area where the dot will be drawn
        SDL_FillRect(m->miniatureImage, &dotRect, SDL_MapRGB(m->miniatureImage->format, 0, 0, 0));

        // Draw the blinking dot based on the blink variable
        if (blink == 0) {
            SDL_BlitSurface(dotImage1, NULL, m->miniatureImage, &dotRect);
            blink = 1;
        } else {
            SDL_BlitSurface(dotImage2, NULL, m->miniatureImage, &dotRect);
            blink = 0;
        }

        // Update the minimap surface
        SDL_Flip(m->miniatureImage);

        // Delay for the animation
        SDL_Delay(animationDelay);
    }
}



