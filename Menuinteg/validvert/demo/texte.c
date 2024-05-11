#include "texte.h"


void inittext2(Text *A)
{
  A->position.x=90;
  A->position.y=20;
//couleur
  A->textColor.r=255;
  A->textColor.g=0;
  A->textColor.b=0;


 A->font = TTF_OpenFont("aAttackGraffiti.ttf" ,30);
}
void inittext3(Text *A)
{
  A->position.x=720;
  A->position.y=800;
//couleur
  A->textColor.r=255;
  A->textColor.g=0;
  A->textColor.b=0;


 A->font = TTF_OpenFont("aAttackGraffiti.ttf" ,30);
}
void inittext4(Text *A)
{
  A->position.x=750;
  A->position.y=870;
//couleur
  A->textColor.r=255;
  A->textColor.g=0;
  A->textColor.b=0;


 A->font = TTF_OpenFont("aAttackGraffiti.ttf" ,30);
}
void inittext5(Text *A)
{
  A->position.x=550;
  A->position.y=100;
//couleur
  A->textColor.r=0;
  A->textColor.g=0;
  A->textColor.b=0;


 A->font = TTF_OpenFont("AVENGEANCE HEROIC AVENGER.ttf" ,70);
}
void freetext(Text A)
{
	SDL_FreeSurface(A.surfaceTexte);
}

void displaytext2(Text t2,SDL_Surface *screen)
{
	t2.surfaceTexte = TTF_RenderText_Solid(t2.font,"Press H to back to home " , t2.textColor );
	SDL_BlitSurface(t2.surfaceTexte, NULL, screen,&t2.position);
}

void displaytext3(Text t3,SDL_Surface *screen)
{
	t3.surfaceTexte = TTF_RenderText_Solid(t3.font," Press F to mode full screen " , t3.textColor );
	SDL_BlitSurface(t3.surfaceTexte, NULL, screen,&t3.position);
}

void displaytext4(Text t4,SDL_Surface *screen)
{
	t4.surfaceTexte = TTF_RenderText_Solid(t4.font," Press N to normal mode" , t4.textColor );
	SDL_BlitSurface(t4.surfaceTexte, NULL, screen,&t4.position);
}

void displaytext5(Text t5,SDL_Surface *screen)
{
	t5.surfaceTexte = TTF_RenderText_Solid(t5.font,"Welcome to the dream" , t5.textColor );
	SDL_BlitSurface(t5.surfaceTexte, NULL, screen,&t5.position);
}
