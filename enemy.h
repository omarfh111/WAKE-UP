#ifndef ENEMY_H

typedef enum
{
    WAITING,
    FOLLOWING,
    ATTACKING,
} states;

typedef struct
{
    SDL_Rect img_pos;     
    SDL_Rect img_size;   
    SDL_Surface *img;     // Pointer to the image.
    int direction;        //0 for idle, 1 for right, 2 for left
    float speed;          
    int max_steps;        
    int idle_time;        //Time when the enemy started idling.
    int x;               
    int y;                
    states current_state; 
    int vision_range;   
} enemy;

void initEnemy(enemy *e);
void drawEnemy(SDL_Surface *screen, enemy e);
void animateEnemy(enemy *e, int direction);
void moveEnemy(enemy *e);
int collisionBB(SDL_Rect player, SDL_Rect enemyy, enemy *e);
void updateEnemy(enemy *e, SDL_Rect posPlayer);
float distance(SDL_Rect player, SDL_Rect enemy);
void updateEnemyState(enemy *e, int distEP);


#endif
