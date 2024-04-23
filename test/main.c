#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h> // Include SDL_ttf for text rendering
#include "perso.h"
#include "background.h"
#include "enemy.h"
#include "constants.h"
#include "minimap.h"

int main() {
    bg bg;
    Minimap minimap;
    perso p1;
    enemy e;
    int q = 1;
    int scrollLeft = 0; // Flag for left scrolling
    int scrollRight = 0; // Flag for right scrolling
    int scrollX = 0;
    int levelWidth = 5760; // Width of the level
    int levelHeight = 800; // Height of the level
    int screenWidth = 1000; // Assuming a screen width of 1000 pixels
int screenHeight = 800;

    SDL_PumpEvents();
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    SDL_Surface *screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE);
    TTF_Font *font = TTF_OpenFont("fonts/score.ttf", 25); // Load your font here
    if (!font) {
        fprintf(stderr, "Error loading font: %s\n", TTF_GetError());
        return 1;
    }

    init_perso(&p1);
    initEnemy(&e);
    SDL_Event event;
    initbg(&bg);
    InitializeMinimap(&minimap, screen, 200, 150);
    
    SDL_Surface *backgroundMask = IMG_Load("mask.png");
    

    int tempsDebut = SDL_GetTicks(); // Start time

    while (q) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                q = 0;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 1; // Set left scroll flag when left arrow is pressed
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 1; // Set right scroll flag when right arrow is pressed
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        scrollLeft = 0; // Clear left scroll flag when left arrow is released
                        break;
                    case SDLK_RIGHT:
                        scrollRight = 0; // Clear right scroll flag when right arrow is released
                        break;
                }
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        if (scrollLeft) {
            scrolling(&bg, 1, p1.pos.x, 0, 0.01); // Scroll left continuously
            scrollX -= 5; // Adjust scrollX based on scrolling
        }
        if (scrollRight) {
            scrolling(&bg, 0, p1.pos.x, 0, 0.01); // Scroll right continuously
            scrollX += 5; // Adjust scrollX based on scrolling
        }

        // Display background
        afficherbg(&bg, screen);
        //SDL_Rect maskRect = { 0, bg.imgs.h, 0, 0 }; // Position the mask below the background
	//SDL_BlitSurface(backgroundMask, NULL, screen, &bg.imgp);
        SDL_PumpEvents();
        SDL_Delay(60);
        afficher_perso(p1, screen);
        afficher_score_vie(p1, screen, 0);
        animer_perso(&p1);
        drawEnemy(screen, e);
        move_perso(&p1);
        saut_perso(&p1);
        player_limite(&p1, screen);
        updateEnemy(&e, p1.pos);

        // Check for collision with enemy
        if (collisionBB(p1.pos, e.img_pos, &e)) {
            p1.vie -= 10;
        }

        // Check for collision with obstacles using the minimap
        
        /* if (CollisionParfaite(backgroundMask, p1.pos)) {
    // Collision detected, stop the player
    p1.speed = 0;
}  */
        
        int playerXOnScreen = bg.imgs.x;
        int playerYOnScreen = bg.imgs.y;
        int playerXOnMap = (playerXOnScreen * minimap.miniaturePosition.w) / screen->w;
        int playerYOnMap = (playerYOnScreen * minimap.miniaturePosition.h) / screen->h;

        // Update the minimap with the calculated player position
        minimap.playerPosition.x = playerXOnMap;
        minimap.playerPosition.y = playerYOnMap;

        // Update the minimap with the scrolling offset
UpdateMinimap(&minimap, bg.imgs, 1000, levelWidth);













        DisplayMinimap(&minimap, screen); // Display minimap

        // Display timer
        afficherTempsLevel(tempsDebut, 120, screen, font); // 120 seconds as an example

        SDL_Flip(screen);

        printf("Position du personnage (x): %d\n", bg.imgs.x);
        if (p1.score <= 0) {
            printf("Game Over\n");
            q = 0;
        }

        // Delay to control frame rate
        SDL_Delay(10);
    }

    FreeMinimap(&minimap);
    SDL_Quit();
    TTF_CloseFont(font); // Close the font after use

    return 0;
}

