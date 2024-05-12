/**
 * @file main.c
 * @brief This file contains the main function and game loop for the game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"

#define SCREEN_WIDTH 1000 /**< Width of the game window. */
#define SCREEN_HEIGHT 800 /**< Height of the game window. */

/**
 * @brief Main function.
 * 
 * @return 0 on success, 1 on failure.
 */
int main() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return 1;
    }

    // Create the game window
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (screen == NULL) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Initialize background and heart images
    bg background;
    image heart;
    image heart2;
    char background_filename[] = "MAP.png";
    initbg(&background, background_filename);
    imgheart(&heart);
    imgheart2(&heart2);

    // Load background music
    Mix_Music *bgMusic;
    musicLoad1(bgMusic);

    // Load jump sound effect
    Mix_Chunk *jumpSound = NULL;

    // Game loop variables
    int quit = 0;
    int scrollingRight = 0, scrollingLeft = 0, scrollingUp = 0, scrollingDown = 0;
    int splitScreen = 0;
    SDL_Event event;

    // Game loop
    while (!quit) {
        // Event handling
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrollingRight = 1;
                        break;
                    case SDLK_LEFT:
                        scrollingLeft = 1;
                        break;
                    case SDLK_UP:
                        scrollingUp = 1;
                        break;
                    case SDLK_DOWN:
                        scrollingDown = 1;
                        break;
                    case SDLK_s:
                        splitScreen = !splitScreen;
                        break;
                    case SDLK_LCTRL:
                        soundeffect(jumpSound);
                        break;
                }
            } else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_RIGHT:
                        scrollingRight = 0;
                        break;
                    case SDLK_LEFT:
                        scrollingLeft = 0;
                        break;
                    case SDLK_UP:
                        scrollingUp = 0;
                        break;
                    case SDLK_DOWN:
                        scrollingDown = 0;
                        break;
                }
            }
        }

        // Handle scrolling
        if (scrollingRight) {
            scrolling(&background, 0, 10, 0);
        }
        if (scrollingLeft) {
            scrolling(&background, 1, 10, 0);
        }
        if (scrollingUp) {
            scrolling(&background, 2, 0, 10);
        }
        if (scrollingDown) {
            scrolling(&background, 3, 0, 10);
        }

        // Clear screen
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        // Render based on split screen mode
        if (splitScreen) {
            splitscreen(screen, &background);
            afficherheart(&heart, screen);
            afficherheart(&heart2, screen);
        } else {
            afficherbg(&background, screen);
            afficherheart(&heart, screen);
        }

        // Update screen
        SDL_Flip(screen);

        // Delay for smooth animation
        SDL_Delay(10);
    }

    // Free resources and quit SDL
    Mix_FreeMusic(bgMusic);
    if (jumpSound != NULL) {
        Mix_FreeChunk(jumpSound);
    }
    SDL_Quit();

    return 0;
}
