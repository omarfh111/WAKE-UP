#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "heart.h"
void inith(heart *h)
{ h->img = IMG_Load("h.png");
if (h->img == NULL)
    {
        printf("Error loading enemy image: %s\n", SDL_GetError());
    }
     h->pos.x = 375;
     h->pos.y = 555;
     h->size.x = 0;
     h->size.y = 0;
     h->size.w = (h->img->w);
     h->size.h = (h->img->h);
     }
    
int collisionBB2(SDL_Rect player, SDL_Rect heart) {
    int collision = 0;
    if ((player.x + player.w > heart.x) && (player.x < heart.x + heart.w) &&
        (player.y + player.h > heart.y) && (player.y < heart.y + heart.h)) {
        collision = 1;
    }
    return collision;
}


void drawh(SDL_Surface *screen, heart h)
{
    SDL_BlitSurface(h.img,NULL, screen, &(h.pos));
}
    /* c1=collisionBB2(p1.pos,h.pos);
		    if (c==1){
           		 p1.vie += 10;
           		 p1.score += 10;
           		 free(&h);
              		  }
		   */
