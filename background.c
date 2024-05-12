#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"
#include "perso.h"
#include <string.h>
void initbg(bg *b){
b->img= IMG_Load("screen1.jpg");
b->imgp.x=0;
b->imgp.y=0;
b->imgs.x=0;
b->imgs.y=200;
b->imgs.w=1000;
b->imgs.h=800;
}

void initmask(bg *b)
{
b->img= IMG_Load("mask.png");
b->imgp.x=0;
b->imgp.y=0;
b->imgs.x=0;
b->imgs.y=200;
b->imgs.w=1000;
b->imgs.h=800;
}


void afficherbg(bg *b, SDL_Surface *screen){
SDL_BlitSurface(b->img, &b->imgs, screen, &b->imgp);

}
void scrolling(bg *b, int direction, float dx, float dy)
{
if (direction == 0)
{
b->imgs.x = dx;
if (b->imgs.x + b->imgs.w > b->img->w)
{
b->imgs.x = b->img->w - b->imgs.w;
}
}
else if (direction == 1)
{
b->imgs.x = dx;
if (b->imgs.x < 0)
{
b->imgs.x = 0;
}
}
else if (direction == 2)
{
b->imgs.y = dy;
if (b->imgs.y < 0)
{
b->imgs.y = 0;
}
}
else if (direction == 3)
{

b->imgs.y = dy;
if (b->imgs.y + b->imgs.h > b->img->h)
{
b->imgs.y = b->img->h - b->imgs.h;
}
}
}
void splitscreen(SDL_Surface *screen, bg *b) 
{
int screen_width = screen->w / 2;
int screen_height = screen->h;
SDL_Rect screen1_rect = {0, 0, screen_width, screen_height};
SDL_Rect screen2_rect = {screen_width, 0, screen_width, screen_height};
SDL_BlitSurface(b->img, &(b->imgs), screen, &screen1_rect);
SDL_BlitSurface(b->img, &(b->imgs), screen, &screen2_rect);
}
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

void loadbestscore(char *filename, scoreinfo scores[]) {
FILE *score = fopen(filename, "r");
if (score == NULL) {
printf("Error opening file");
return;
} 
else {
int i;
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
void printBestScores(scoreinfo scores[]) {
printf("Top 3 scores:\n");
for (int i = 0; i < 3; i++) {
printf("%d. Player: %s - Score: %d - Time: %d\n", i + 1, scores[i].playername, scores[i].score, scores[i].temps);
}
}
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





