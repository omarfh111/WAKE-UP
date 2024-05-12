#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include "background.h"



void initbg(bg *b, char *filename) {
b->img = IMG_Load(filename);
b->imgp.x = 0;
b->imgp.y = 0;
b->imgs.x = 0;
b->imgs.y = 200;
b->imgs.w = 1000;
b->imgs.h = 800;
}



void imgheart(image *i){
i->img= IMG_Load("heart2");
i->imgp.x=0;
i->imgp.y=0;
i->imgs.x=50;
i->imgs.y=50;
i->imgs.w=100;
i->imgs.h=100;
}



void imgheart2(image *i){
i->img= IMG_Load("heart2");
i->imgp.x=500;
i->imgp.y=0;
i->imgs.x=50;
i->imgs.y=50;
i->imgs.w=100;
i->imgs.h=100;
}



void afficherheart(image *i, SDL_Surface *screen){
SDL_BlitSurface(i->img, &i->imgs, screen, &i->imgp);
}



void afficherbg(bg *b, SDL_Surface *screen)
{
SDL_BlitSurface(b->img, &b->imgs, screen, &b->imgp);
}



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



/*
void backgroundAnimate(SDL_Surface *screen, image *img)
{
int frame = 0;
Uint32 last_time = 0;
Uint32 current_time = SDL_GetTicks();
if (current_time > last_time + 200)
{+
frame++;
if (frame >= 5)
{
frame = 0;
}
img->img_size.x = frame * (img->img->w / 5);
last_time = current_time;
}
}
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
void savescore(scoreinfo s,char *filename){
FILE *score;
score=fopen(filename,"a");
if(score==NULL){
printf("erreur fichier");
return;
}
else
fprintf(score,"playername:%s score:%d temps:%d\n",s.playername,s.score,s.temps);
fclose(score);
}



void loadbestscore(char *filename, scoreinfo scores[]){
FILE *score=fopen(filename,"r");
if (score==NULL)
{
printf("erreur fichier");
return;
}
else{
scoreinfo s;
int i,j;
for(i=0;i<=3;i++){
scores[i]=s;
}
fclose(score);
for(i=0;i<2;i++){
for(j=i+1;j<3;j++)
{
if((scores[j].score>scores[i].score) ||(scores[j].score==scores[i].score)&&(scores[j].temps<scores[i].temps)){
scoreinfo x;
x=scores[i];
scores[i]=scores[j];
scores[j]=x;
}
}
}
}
}




