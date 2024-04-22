#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "constants.h"
#include "enemy.h"

void initEnemy(enemy *e)
{
    e->img = IMG_Load("s.png");
    if (e->img == NULL)
    {
        printf("Error loading enemy image: %s\n", SDL_GetError());
    }
    e->direction = 1;
    e->speed = 1;
    e->max_steps = 300;
    e->idle_time = 2500;
    e->x = (SCREEN_W / 2 - (e->img->w / 4) - 96 / 2) -200; // screen width - (width of img / sprite size) - (width of sprite / 2)
    e->y = (SCREEN_H / 2 - (e->img->h / 4) - 96 / 2) + 200; // screen height - (height of img / sprite size) - (height of sprite / 2)

    e->img_size.x = 0;
    e->img_size.y = 0;
    e->img_size.w = (e->img->w) / 4; // (width of img / sprite frames) :576/6 =96px
    e->img_size.h = (e->img->h) / 4; // (height of img / sprite frames) := 288/3= 96px
    e->img_pos.x = e->x;
    e->img_pos.y = e->y;

    e->current_state = WAITING;
    e->vision_range = 100;
}


void drawEnemy(SDL_Surface *screen, enemy e)
{
    SDL_BlitSurface(e.img, &(e.img_size), screen, &(e.img_pos));
}

/*
 (0 = idle, 1 = right, 2 = left).
 */
 
void animateEnemy(enemy *e, int direction) //! added new parameter dont forget
{
    static int frame = 0;
    int row = 0;
    if (direction == 1)
    {
        row = 1;
    }
    else if (direction == 2)
    {
        row = 2;
    }
    else if (direction == 0)
    {
        row = 0;
    }
    e->img_size.x = frame * e->img_size.w;
    e->img_size.y = row * e->img_size.h;

    Uint32 current_time = SDL_GetTicks();
    static Uint32 last_time = 0;
    Uint32 delta_time = current_time - last_time;
    if (delta_time >= 100)
    {
        frame++;
        if (frame >= 4)
        {
            frame = 0;
        }
        last_time = current_time;
    }
}

/*
 * This function updates the enemy's image position based on its direction and speed.
 * It also calls the animateEnemy function to update the animation frame.
 
 */
void moveEnemy(enemy *e)
{
    if (e->direction == 1)
    { // move right
        animateEnemy(e, 1);
        e->img_pos.x += e->speed;
        if (e->img_pos.x >= e->x + e->max_steps)
        {
            e->img_pos.x = e->x + e->max_steps;
            e->direction = 0;
            e->idle_time = SDL_GetTicks() + rand() % 2500 + 500;
        }
    }
    else if (e->direction == 2)
    { // move left
        animateEnemy(e, 2);
        e->img_pos.x -= e->speed;
        if (e->img_pos.x <= e->x)
        {
            e->img_pos.x = e->x;
            e->direction = 0;
            e->idle_time = SDL_GetTicks() + rand() % 2500 + 500;
        }
    }
    else if (e->direction == 0)
    { // idle
        animateEnemy(e, 0);
        Uint32 current_time = SDL_GetTicks();
        if (current_time >= e->idle_time)
        { // check if idle time is over
            if (e->img_pos.x == e->x)
            {
                e->direction = 1;
            }
            else if (e->img_pos.x == e->x + e->max_steps)
            {
                e->direction = 2;
            }
        }
    }
}

/*
 * Checks for collision between two bounding boxes.
 * This function determines whether there is a collision between the player's bounding box and the enemy's bounding box.
 * It returns 1 if there is a collision, and 0 otherwise.
 * @param player The bounding box of the player.
 * @param enemy The bounding box of the enemy.
 */
int collisionBB(SDL_Rect player, SDL_Rect enemyy, enemy *e)
{
    int collision = 0;
    if ((player.x + player.w < enemyy.x) || (player.x > enemyy.x + enemyy.w) || (player.y + player.h < enemyy.y) || (player.y > enemyy.y + enemyy.h))
    {
        collision = 0;
    }
    else
    {
        collision = 1;
        e->current_state = ATTACKING; // Set the enemy's current_state to ATTACKING
    }
    return collision;
}

/*
 * Calculates the distance between two SDL_Rect objects based on their x-coordinates.
 * @param player The SDL_Rect object representing the player's position.
 * @param enemy The SDL_Rect object representing the enemy's position.
 * @return The distance between the player and the enemy along the x-axis.
 */
float distance(SDL_Rect player, SDL_Rect enemy)
{
    int distanceX = abs(enemy.x - player.x);
    return distanceX;
}

/*
 * Updates the state of an enemy based on the distance between the enemy and the player.
 *
 * @param e A pointer to the enemy object to update.
 * @param distEP The distance between the enemy and the player along the x-axis.
 */
void updateEnemyState(enemy *e, int distEP)
{
    if (distEP <= e->vision_range)
    {
        e->current_state = FOLLOWING;
    }
    else
    {
        e->current_state = WAITING;
    }
}

/*
 * Updates the position and behavior of an enemy based on the player's position and the enemy's state.
 *
 * @param e A pointer to the enemy object to update.
 * @param posPlayer The SDL_Rect object representing the player's position.
 */
void updateEnemy(enemy *e, SDL_Rect posPlayer)
{
    int distEP = distance(posPlayer, (SDL_Rect){e->img_pos.x, e->img_pos.y, e->img_size.w, e->img_size.h});
    updateEnemyState(e, distEP);

    switch (e->current_state)
    {
    case WAITING:
        moveEnemy(e);
        break;
    case FOLLOWING:
        if (distEP <= e->vision_range)
        {
            if (e->img_pos.x > posPlayer.x)
            {
                animateEnemy(e, 2);
                e->img_pos.x -= e->speed;
            }
            else if (e->img_pos.x < posPlayer.x)
            {
                animateEnemy(e, 1);
                e->img_pos.x += e->speed;
            }
        }
        else
        {
            e->current_state = WAITING;
        }
        break;
    case ATTACKING:
        if (!collisionBB(posPlayer, (SDL_Rect){e->img_pos.x, e->img_pos.y, e->img_size.w, e->img_size.h}, e))
        {
            e->current_state = FOLLOWING;
            break;
        }
        else
        {
            animateEnemy(e, 0);
            e->current_state = WAITING;
            e->img_pos.x = e->x;
            e->direction = 0;
            e->idle_time = SDL_GetTicks() + rand() % 1500 + 500;
            moveEnemy(e);
            break;
        }
    }
}
