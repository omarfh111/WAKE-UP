/**
 * @file background.h
 * @brief This file contains the declarations of functions and structures related to managing the background, scores, and images in a game.
 */

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "perso.h"

/**
 * @struct bg
 * @brief Structure representing the background.
 */
typedef struct{
    SDL_Rect imgp; /**< Position of the background image. */
    SDL_Rect imgs; /**< Size of the background image. */
    SDL_Surface *img; /**< Pointer to the background image surface. */
    int direction; /**< Direction of scrolling for the background. */
} bg;

/**
 * @struct scoreinfo
 * @brief Structure representing score information.
 */
typedef struct{
    int score; /**< Player's score. */
    int temps; /**< Time elapsed. */
    char playername[20]; /**< Player's name. */
} scoreinfo;

/**
 * @struct imagee
 * @brief Structure representing an image.
 */
typedef struct{
    SDL_Rect imgs; /**< Size of the image. */
    SDL_Rect imgp; /**< Position of the image. */
    SDL_Surface *img; /**< Pointer to the image surface. */
} imagee;

/**
 * @brief Initialize the background.
 * 
 * @param b Pointer to the background structure to initialize.
 */
void initbg(bg *b);

/**
 * @brief Display the background on the screen.
 * 
 * @param b Pointer to the background structure to display.
 * @param screen Pointer to the screen surface.
 */
void afficherbg(bg *b, SDL_Surface *screen);

/**
 * @brief Animate the background.
 * 
 * @param screen Pointer to the screen surface.
 * @param img Pointer to the image surface.
 */
void animerbg(SDL_Surface *screen, SDL_Surface *img);

/**
 * @brief Scroll the background image.
 * 
 * @param b Pointer to the background structure to scroll.
 * @param direction The direction of scrolling.
 * @param dx The amount of horizontal scrolling.
 * @param dy The amount of vertical scrolling.
 */
void scrolling(bg *b, int direction, float dx, float dy);

/**
 * @brief Save the player's score to a file.
 * 
 * @param t The player's score.
 * @param p The player's character.
 * @param scores Array to store top scores.
 * @param filename The filename of the score file.
 * @param playername The player's name.
 */
void savescore(int t, perso p, scoreinfo scores[], char *filename, char *playername);

/**
 * @brief Load the top scores from a file.
 * 
 * @param filename The filename of the score file.
 * @param scores Array to store top scores.
 */
void loadbestscore(char *filename, scoreinfo scores[]);

/**
 * @brief Display the top scores on the screen.
 * 
 * @param screen Pointer to the screen surface.
 * @param t Array containing top scores.
 */
void displayscore(SDL_Surface *screen, scoreinfo t[]);

/**
 * @brief Split the screen and display the background on both halves.
 * 
 * @param screen Pointer to the screen surface.
 * @param b Pointer to the background structure to display.
 */
void splitscreen(SDL_Surface *screen, bg *b);

/**
 * @brief Display an image of a heart on the screen.
 * 
 * @param i Pointer to the image structure to display.
 * @param screen Pointer to the screen surface.
 */
void afficherheart(imagee *i, SDL_Surface *screen);

/**
 * @brief Initialize an image of a heart.
 * 
 * @param i Pointer to the image structure to initialize.
 */
void imgheart(imagee *i);

/**
 * @brief Initialize a mask for collision detection.
 * 
 * @param mask Pointer to the mask structure to initialize.
 */
void initmask(bg *mask);

/**
 * @brief Print the top scores.
 * 
 * @param scores Array containing top scores.
 */
void printBestScores(scoreinfo scores[]);

/**
 * @brief Display the player's score on the screen.
 * 
 * @param screen Pointer to the screen surface.
 * @param font Pointer to the font used for rendering.
 * @param p The player's character.
 */
void displayScore(SDL_Surface *screen, TTF_Font *font, perso p);

#endif
