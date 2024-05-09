#include "boundingbox.h"

int in_bounds(SDL_Rect x1,SDL_Rect x2)//louken x1 f west l x2
{
return(x1.x>=x2.x)&&(x1.x<=x2.x+x2.w)&&((x1.y>=x2.y)&&(x1.y<=x2.y+x2.h)||((x1.y<=x2.y)&&(x1.y+x2.h>=x2.y)));
}
int collision(SDL_Rect x1,SDL_Rect x2)//ken fama collision bin x1 w x2
{
return in_bounds(x1,x2)||in_bounds(x2,x1);
}

int collisiontrigo(SDL_Rect rect1, SDL_Rect rect2) {
    if (rect1.x + rect1.w == rect2.x || rect2.x + rect2.w == rect1.x) {
        if (rect1.y + rect1.h >= rect2.y && rect2.y + rect2.h >= rect1.y) {
            return 1;
        }
    } else if (rect1.y + rect1.h == rect2.y || rect2.y + rect2.h == rect1.y) {
        if (rect1.x + rect1.w >= rect2.x && rect2.x + rect2.w >= rect1.x) {
            return 1;
        }
    }
    
    return 0; 
}

