#ifndef HEART_H
typedef struct
{
    SDL_Rect pos; 
    SDL_Rect size;        
    SDL_Surface *img;     // Pointer to the image.
} heart;
void inith(heart *h);
int collisionBB2(SDL_Rect player, SDL_Rect heart);
void drawh(SDL_Surface *screen, heart h);
#endif
