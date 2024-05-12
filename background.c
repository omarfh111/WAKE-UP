/**
 * @file main.c
 * @brief This file contains the implementation of various functions for managing background images, music, sound effects, and scoring in a game.
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include "perso.h"

/**
 * @brief Initialize the background.
 * 
 * @param b Pointer to the background structure to initialize.
 * @param filename The filename of the image to load for the background.
 */
void initbg(bg *b, char *filename) {
    b->img = IMG_Load(filename);
    b->imgp.x = 0;
    b->imgp.y = 0;
    b->imgs.x = 0;
    b->imgs.y = 200;
    b->imgs.w = 1000;
    b->imgs.h = 800;
}

/**
 * @brief Initialize an image of a heart.
 * 
 * @param i Pointer to the image structure to initialize.
 */
void imgheart(image *i){
    i->img= IMG_Load("heart2");
    i->imgp.x=0;
    i->imgp.y=0;
    i->imgs.x=50;
    i->imgs.y=50;
    i->imgs.w=100;
    i->imgs.h=100;
}

/**
 * @brief Initialize a second image of a heart.
 * 
 * @param i Pointer to the image structure to initialize.
 */
void imgheart2(image *i){
    i->img= IMG_Load("heart2");
    i->imgp.x=500;
    i->imgp.y=0;
    i->imgs.x=50;
    i->imgs.y=50;
    i->imgs.w=100;
    i->imgs.h=100;
}

/**
 * @brief Display an image on the screen.
 * 
 * @param i Pointer to the image structure to display.
 * @param screen Pointer to the screen surface.
 */
void afficherheart(image *i, SDL_Surface *screen){
    SDL_BlitSurface(i->img, &i->imgs, screen, &i->imgp);
}

/**
 * @brief Display the background on the screen.
 * 
 * @param b Pointer to the background structure to display.
 * @param screen Pointer to the screen surface.
 */
void afficherbg(bg *b, SDL_Surface *screen)
{
    SDL_BlitSurface(b->img, &b->imgs, screen, &b->imgp);
}

/**
 * @brief Load and play background music.
 * 
 * @param music Pointer to the Mix_Music structure to load and play music.
 */
void musicLoad1(Mix_Music *music)
{
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
    {
        printf("%s", Mix_GetError());
    }
    music = Mix_LoadMUS("mgs.mp3");
    if (music == NULL)
    {
        printf("unable to load music Error: %s.\n", Mix_GetError());
        return;
    }
    Mix_PlayMusic(music, -1);
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
}

/**
 * @brief Load and play a sound effect.
 * 
 * @param sound Pointer to the Mix_Chunk structure to load and play a sound effect.
 */
void soundeffect(Mix_Chunk *sound) {
    if (Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 1024) == -1) {
        printf("%s\n", Mix_GetError());
        return;
    }
    sound = Mix_LoadWAV("jumpf.wav");
    if (sound == NULL) {
        printf("Unable to load sound effect. Error: %s\n", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(sound, MIX_MAX_VOLUME / 2);
    Mix_PlayChannel(-1, sound, 0); 
}

/**
 * @brief Scroll the background image.
 * 
 * @param b Pointer to the background structure to scroll.
 * @param direction The direction of scrolling (0: right, 1: left, 2: up, 3: down).
 * @param dx The amount of horizontal scrolling.
 * @param dy The amount of vertical scrolling.
 */
void scrolling(bg *b, int direction, int dx, int dy)
{
    if (direction == 0) 
    {
        b->imgs.x += dx;
        if (b->imgs.x + b->imgs.w > b->img->w) 
        {
            b->imgs.x = b->img->w - b->imgs.w;
        }
    }
    else if (direction == 1) 
    {
        b->imgs.x -= dx;
        if (b->imgs.x < 0) 
        {
            b->imgs.x = 0;
        }
    }
    else if (direction == 2) 
    {
        b->imgs.y -= dy;
        if (b->imgs.y < 0) 
        {
            b->imgs.y = 0;
        }
    }
    else if (direction == 3) 
    {
        b->imgs.y += dy;
        if (b->imgs.y + b->imgs.h > b->img->h) 
        {
            b->imgs.y = b->img->h - b->imgs.h;
        }
    }
}

/**
 * @brief Split the screen and display the background on both halves.
 * 
 * @param screen Pointer to the screen surface.
 * @param b Pointer to the background structure to display.
 */
void splitscreen(SDL_Surface *screen, bg *b) 
{
    int screen_width = screen->w / 2;
    int screen_height = screen->h;
    SDL_Rect screen1_rect = {0, 0, screen_width, screen_height};
    SDL_Rect screen2_rect = {screen_width, 0, screen_width, screen_height};
    SDL_BlitSurface(b->img, &(b->imgs), screen, &screen1_rect);
    SDL_BlitSurface(b->img, &(b->imgs), screen, &screen2_rect);
}

/**
 * @brief Save the player's score to a file.
 * 
 * @param t The player's score.
 * @param p The player's character.
 * @param scores Array to store top scores.
 * @param filename The filename of the score file.
 * @param playername The player's name.
 */
void savescore(int t, perso p, scoreinfo scores[], char *filename, char *playername) {
    FILE *score;
    score = fopen(filename, "a");
    if (score == NULL) {
        printf("erreur fichier");
        return;
    } 
    else {
        scoreinfo s;
        s.score = p.score;
        s.temps = t;
        strcpy(s.playername, playername);
        fprintf(score, "playername:%s score:%d temps:%d\n", s.playername, s.score, s.temps);
        fclose(score);
    }
}

/**
 * @brief Load the top scores from a file.
 * 
 * @param filename The filename of the score file.
 * @param scores Array to store top scores.
 */
void loadbestscore(char *filename, scoreinfo scores[]) {
    FILE *score = fopen(filename, "r");
    if (score == NULL) {
        printf("Error opening file");
        return;
    } 
    else {
        int i;
        for (i = 0; i < 10; i++) {
            fscanf(score, "playername:%s score:%d temps:%d\n", scores[i].playername, &scores[i].score, &scores[i].temps);
        }
        fclose(score);
        for (i = 0; i < 2; i++) {
            for (int j = i + 1; j < 3; j++) {
                if ((scores[j].score > scores[i].score) || (scores[j].score == scores[i].score && scores[j].temps < scores[i].temps)) {
                    scoreinfo x = scores[i];
                    scores[i] = scores[j];
                    scores[j] = x;
                }
            }
        }
    }
}

/**
 * @brief Print the top scores.
 * 
 * @param scores Array containing top scores.
 */
void printBestScores(scoreinfo scores[]) {
    printf("Top 3 scores:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d. Player: %s - Score: %d - Time: %d\n", i + 1, scores[i].playername, scores[i].score, scores[i].temps);
    }
}

/**
 * @brief Display the player's score on the screen.
 * 
 * @param screen Pointer to the screen surface.
 * @param font Pointer to the font used for rendering.
 * @param p The player's character.
 */
void displayScore(SDL_Surface *screen, TTF_Font *font, perso p) {
    SDL_Color textColor = {255, 255, 255};
    char scoreText[20];
    sprintf(scoreText, "Score: %d", p.score);
    SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreText, textColor);
    SDL_Rect scorePosition;
    scorePosition.x = 900 - scoreSurface->w - 10; // Adjusted for bottom right corner
    scorePosition.y = 50 - scoreSurface->h - 10; // Adjusted for bottom right corner
    SDL_BlitSurface(scoreSurface, NULL, screen, &scorePosition);
    SDL_FreeSurface(scoreSurface);
}
