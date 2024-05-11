#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"
#define SCREEN_W 1938
#define SCREEN_H 1115
void initBackground(image *Backg,char name[])
{
	Backg->img=IMG_Load(name);
	if(Backg->img==NULL)
		{
			printf("Unable to load image %s\n", SDL_GetError());
			return;
		}
	Backg->pos1.x=0;
	Backg->pos1.y=0;
	Backg->pos2.x=0;
	Backg->pos2.y=0;
	Backg->pos2.w=(SCREEN_W);
	Backg->pos2.h=(SCREEN_H);
}
void initBackgroundwindow(image *Backg,char name[])
{
	Backg->img=IMG_Load(name);
	if(Backg->img==NULL)
		{
			printf("Unable to load image %s\n", SDL_GetError());
			return;
		}
	Backg->pos1.x=483;
	Backg->pos1.y=50;
	Backg->pos2.x=0;
	Backg->pos2.y=0;
	Backg->pos2.w=(SCREEN_W);
	Backg->pos2.h=(SCREEN_H);
}
void initbouton(image *B,char name[],int x,int y)
{
	B->img=IMG_Load(name);
	if(B->img==NULL)
		{
			printf("Unable to load image %s\n", SDL_GetError());
			return;
		}
	B->pos1.x=x;
	B->pos1.y=y;
	B->pos2.x=0;
	B->pos2.y=0;
	B->pos2.w=(SCREEN_W);
	B->pos2.h=(SCREEN_H);
	//B->state=0;
}

void liberer(image A)
{
	SDL_FreeSurface(A.img);
}

void afficher (image p,SDL_Surface *screen)
{
	SDL_BlitSurface(p.img,&p.pos2,screen,&p.pos1);
}
