#include <SDL/SDL_image.h>

void InitializeMinimap(Minimap *minimap, SDL_Surface *screen) {
    minimap->miniatureImage = IMG_Load(".jpg");
    minimap->playerImage = IMG_Load(".png");
    minimap->enemyImage = IMG_Load(".png");
    minimap->puzzleImage = IMG_Load(".png");

    if (!minimap->miniatureImage || !minimap->playerImage ||
        !minimap->enemyImage || !minimap->puzzleImage) {
        printf("Failed to load one or more images: %s\n", IMG_GetError());
     
    }

   
    minimap->miniaturePosition.x = ;
    minimap->miniaturePosition.y = ;
    minimap->playerPosition.x = ;
    minimap->playerPosition.y = ;
    minimap->enemyPosition.x = ;
    minimap->enemyPosition.y = ;
    minimap->puzzlePosition.x = ;
    minimap->puzzlePosition.y = ;

    
    SDL_BlitSurface(minimap->miniatureImage, NULL, screen, &minimap->miniaturePosition);
    SDL_BlitSurface(minimap->playerImage, NULL, screen, &minimap->playerPosition);
    SDL_BlitSurface(minimap->enemyImage, NULL, screen, &minimap->enemyPosition);
    SDL_BlitSurface(minimap->puzzleImage, NULL, screen, &minimap->puzzlePosition);

    SDL_Flip(screen);
}


void UpdateMinimap(Minimap *minimap, SDL_Rect playerAbsolutePosition, SDL_Rect camera, int resizingFactor) {
    
    //playerAbsolutePosition: pos player  camera: var concern scrolling  resizingFactor % 9adeh tsagher el entity
    
    int playerXOnMap, playerYOnMap;
    int enemyXOnMap, enemyYOnMap;
    int puzzleXOnMap, puzzleYOnMap;

   
    playerXOnMap = (playerAbsolutePosition.x + camera.x) * resizingFactor / 100;
    playerYOnMap = (playerAbsolutePosition.y + camera.y) * resizingFactor / 100;

   
    enemyXOnMap = (minimap->enemyPosition.x - camera.x) * resizingFactor / 100;
    enemyYOnMap = (minimap->enemyPosition.y - camera.y) * resizingFactor / 100;


    puzzleXOnMap = minimap->puzzlePosition.x * resizingFactor / 100;
    puzzleYOnMap = minimap->puzzlePosition.y * resizingFactor / 100;

    
    minimap->playerPosition.x = playerXOnMap;
    minimap->playerPosition.y = playerYOnMap;

    minimap->enemyPosition.x = enemyXOnMap;
    minimap->enemyPosition.y = enemyYOnMap;

    minimap->puzzlePosition.x = puzzleXOnMap;
    minimap->puzzlePosition.y = puzzleYOnMap;
}

void DisplayMinimap(Minimap *minimap, SDL_Surface *screen) {
    
    //background minimap black
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

	//affiche minimap backgrd
    SDL_BlitSurface(minimap->miniatureImage, NULL, screen, &minimap->miniaturePosition);

    // afficher player
    SDL_BlitSurface(minimap->playerImage, NULL, screen, &minimap->playerPosition);

    //afficher enemy si existe
    if (minimap->enemyImage != NULL) {
        SDL_BlitSurface(minimap->enemyImage, NULL, screen, &minimap->enemyPosition);
    }

    //afficher puzzle si exsiste
    if (minimap->puzzleImage != NULL) {
        SDL_BlitSurface(minimap->puzzleImage, NULL, screen, &minimap->puzzlePosition);
    }

    
    SDL_Flip(screen);
}

void FreeMinimap(Minimap *minimap) {
    SDL_FreeSurface(minimap->miniatureImage);
    minimap->miniatureImage = NULL;

    SDL_FreeSurface(minimap->playerImage);
    minimap->playerImage = NULL;

    SDL_FreeSurface(minimap->enemyImage);
    minimap->enemyImage = NULL;

    SDL_FreeSurface(minimap->puzzleImage);
    minimap->puzzleImage = NULL;
}





