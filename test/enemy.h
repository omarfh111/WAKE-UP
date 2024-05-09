/**
 * @file enemy.h
 * @brief Header file containing the definition of the enemy structure and functions for manipulating it.
 * @author SASSI FATMA
 */
#ifndef ENEMY_H
 /**
 * @brief Enumeration of states an enemy can be in.
 */
 
typedef enum
{
    WAITING,//!< Enemy is idle.
    FOLLOWING,//!< Enemy is following the player.
    ATTACKING, //!< Enemy is attacking the player.
} states;

/**
 * @brief Structure representing an enemy.
 *
 * The enemy structure contains information about the enemy's position, size, sprite image,
 * direction of movement, speed, maximum steps before changing direction, idle time, grid position,
 * current state, and range of vision.
 */
 
typedef struct
{
    SDL_Rect img_pos;     //!< Position of the sprite on the screen.  
    SDL_Rect img_size;    //!< Size of the sprite.
    SDL_Surface *img;     // Pointer to the image.
    int direction;        //0 for idle, 1 for right, 2 for left
    float speed;          //!< Steps per frame.
    int max_steps;        //!< Maximum number of steps before changing direction.
    int idle_time;        //Time when the enemy started idling.
    int x;                //!< Position of the enemy in the grid (screen coordinates).
    int y;                //!< Position of the enemy in the grid (screen coordinates).
    states current_state;  //!< Current state of the enemy.
    int vision_range;     //!< Range of vision of the enemy.
} enemy;

/**
 * @brief Initializes an enemy.
 *
 * This function initializes the enemy structure by loading the sprite image, setting the direction, speed, maximum steps,
 * idle time, and initial positions.
 *
 * @param e Pointer to the enemy structure.
 */
void initEnemy(enemy *e);

/**
 * @brief Draws the enemy on the screen.
 *
 * This function draws the enemy sprite on the given screen surface at its current position.
 *
 * @param screen Pointer to the screen surface.
 * @param e The enemy structure.
 */
void drawEnemy(SDL_Surface *screen, enemy e);

/**
 * @brief Animates the enemy sprite.
 *
 * This function updates the sprite frame of the enemy based on the given direction.
 *
 * @param e Pointer to the enemy structure.
 * @param direction The direction of movement (0 for idle, 1 for right, 2 for left).
 */
void animateEnemy(enemy *e, int direction);

/**
 * @brief Moves the enemy.
 *
 * This function moves the enemy based on its current direction and updates the sprite animation accordingly.
 *
 * @param e Pointer to the enemy structure.
 */
void moveEnemy(enemy *e);

/**
 * @brief Checks for collision between two bounding boxes.
 *
 * This function determines whether there is a collision between the player's bounding box and the enemy's bounding box.
 * It returns 1 if there is a collision, and 0 otherwise.
 *
 * @param player The bounding box of the player.
 * @param enemyy The bounding box of the enemy.
 * @param e Pointer to the enemy structure.
 * @return 1 if there is a collision, 0 otherwise.
 */
int collisionBB(SDL_Rect player, SDL_Rect enemyy, enemy *e);

/**
 * @brief Updates the state and position of an enemy based on the position of the player.
 *
 * @param e Pointer to the enemy to update.
 * @param posPlayer SDL_Rect representing the position and size of the player.
 */
void updateEnemy(enemy *e, SDL_Rect posPlayer);

/**
 * @brief Calculates and returns the horizontal distance between two SDL_Rects.
 *
 * @param player The first SDL_Rect.
 * @param enemy The second SDL_Rect.
 * @return The horizontal distance between the two SDL_Rects.
 */

float distance(SDL_Rect player, SDL_Rect enemy);

/**
 * @brief Updates the state of an enemy based on the distance between the enemy and the player.
 *
 * @param e Pointer to the enemy to update.
 * @param distEP The horizontal distance between the enemy and the player.
 */

void updateEnemyState(enemy *e, int distEP);


#endif
