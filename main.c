#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h> // Include for printf function
#include "minimap.h"

#define SCREEN_WIDTH 1407
#define SCREEN_HEIGHT 974
#define PLAYER_SPEED 5

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    SDL_WM_SetCaption("Game with Minimap", NULL);

    // Load background and mask images
    SDL_Surface *background = IMG_Load("background.png");
    SDL_Surface *mask = IMG_Load("mask.png");
    if (!background || !mask) {
        printf("Failed to load background or mask image: %s\n", IMG_GetError());
        return 1;
    }

    // Load cube image
    SDL_Surface *cube = IMG_Load("cube.jpg");
    if (!cube) {
        printf("Failed to load cube image: %s\n", IMG_GetError());
        return 1;
    }

    // Initialize minimap
    Minimap minimap;
    InitializeMinimap(&minimap, screen, 200, 150); // Adjust minimapWidth and minimapHeight as needed

    // Initialize SDL_ttf for text rendering
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("arial.ttf", 24); // Adjust font size as needed
    if (!font) {
        printf("Failed to load font: %s\n", TTF_GetError());
        return 1;
    }

    SDL_Rect playerRect = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, cube->w, cube->h };
    SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT }; // Define camera
    int resizingFactor = 25; // Define resizingFactor

    // Timer variables
    int tempsDebut = SDL_GetTicks(); // Start time in milliseconds
    int dureeTotale = 60 * 1000; // Total duration in milliseconds (here, 60 seconds)

    SDL_Event event;
    int quit = 0;
    int upKey = 0, downKey = 0, leftKey = 0, rightKey = 0;

    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
                // Update key states when a key is pressed or released
                if (event.type == SDL_KEYDOWN) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            upKey = 1;
                            break;
                        case SDLK_DOWN:
                            downKey = 1;
                            break;
                        case SDLK_LEFT:
                            leftKey = 1;
                            break;
                        case SDLK_RIGHT:
                            rightKey = 1;
                            break;
                    }
                } else if (event.type == SDL_KEYUP) {
                    switch (event.key.keysym.sym) {
                        case SDLK_UP:
                            upKey = 0;
                            break;
                        case SDLK_DOWN:
                            downKey = 0;
                            break;
                        case SDLK_LEFT:
                            leftKey = 0;
                            break;
                        case SDLK_RIGHT:
                            rightKey = 0;
                            break;
                    }
                }
            }
        }

        // Store the player's current position for potential rollback
        SDL_Rect prevPlayerRect = playerRect;

        // Move the cube based on key states with collision checks using the mask
        if (upKey && playerRect.y > 0) {
            playerRect.y -= PLAYER_SPEED;
            if (CollisionParfaite(mask, playerRect)) {
                playerRect = prevPlayerRect;
            }
        }
        if (downKey && playerRect.y + playerRect.h < SCREEN_HEIGHT) {
            playerRect.y += PLAYER_SPEED;
            if (CollisionParfaite(mask, playerRect)) {
                playerRect = prevPlayerRect;
            }
        }
        if (leftKey && playerRect.x > 0) {
            playerRect.x -= PLAYER_SPEED;
            if (CollisionParfaite(mask, playerRect)) {
                playerRect = prevPlayerRect;
            }
        }
        if (rightKey && playerRect.x + playerRect.w < SCREEN_WIDTH) {
            playerRect.x += PLAYER_SPEED;
            if (CollisionParfaite(mask, playerRect)) {
                playerRect = prevPlayerRect;
            }
        }

        SDL_BlitSurface(background, NULL, screen, NULL); // Blit background
        SDL_BlitSurface(cube, NULL, screen, &playerRect); // Blit cube

        // Update and display minimap
        UpdateMinimap(&minimap, playerRect, resizingFactor, SCREEN_WIDTH, SCREEN_HEIGHT);
        DisplayMinimap(&minimap, screen);

        // Display timer
        afficherTempsLevel(tempsDebut, dureeTotale, screen, font);

        SDL_Flip(screen);
    }

    // Free resources
    SDL_FreeSurface(background);
    SDL_FreeSurface(mask);
    SDL_FreeSurface(cube);
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}

