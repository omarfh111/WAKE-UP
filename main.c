#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>    
#include "enigme.h"

  



int main()
{   TTF_Init();
    TTF_Font *funt=TTF_OpenFont("MontserratAlternates-Black.otf",24);
    int tempsDebut=SDL_GetTicks();
    int dureeTotale=60*1000;
   SDL_Init(SDL_INIT_VIDEO);
   SDL_Surface *screen=NULL;
    image IMAGE, IMAGE_BTN1, IMAGE_BTN2;
    Mix_Music *music;
    SDL_Event event;
    int boucle = 1;
    enigme e;
    e.numbr=0;
    int input=0;
    int boucleinput=0;
   srand(time(NULL));
	int tb = rand() % 3;
    
   
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) == -1)
    {
        printf("could not initialize SDL: %s.\n ", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    initialiser_imageBACK(&IMAGE);
	initialiser_imageBOUTON1(&IMAGE_BTN1) ; 
	initialiser_imageBOUTON2(&IMAGE_BTN2) ; 
    initialiser_audio(music);

e.f = fopen("enigme.txt", "r");
 if (e.f==NULL)
	{
	printf("NULL");
	fclose(e.f);
	}	else {

fgets(e.question, sizeof(e.question), e.f);

    	fgets(e.r1, sizeof(e.r1), e.f);

    	fgets(e.r2, sizeof(e.r2), e.f);

    	fgets(e.r3, sizeof(e.r3), e.f);

    	fscanf(e.f, "%d", &e.numbr);
printf("\n correct response is : %d \n",e.numbr); 

    	fgets(e.x, sizeof(e.x), e.f); 

}

 srand(time(NULL));
genererEnigme("enigme.txt", &e);
    while (boucle)
    {

        afficher_imageBMP(screen, IMAGE);
        
        afficherEnigme(screen,e,tb);
animate(screen,&e) ;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
 case SDL_KEYDOWN :
           

if (event.key.keysym.sym<=SDLK_a){
input=1;
}

else if (event.key.keysym.sym<=SDLK_b){
input=2;
}

else if (event.key.keysym.sym<=SDLK_c){
input=3;	
}
break;

       case SDL_QUIT:
                    boucle = 0;
                    break;
            }
        }

if (input!=0){   
 if(input==e.numbr){
	boucleinput=1;
	while (boucleinput){
	while (SDL_PollEvent(&event)){

switch (event.type)
            {

case SDL_QUIT:
                    boucleinput=0;
		    input=0;
                    break;



}


}

	
	afficher_imageBTN1(screen,IMAGE_BTN1 ) ;
	SDL_Flip(screen);
}
	
}else{
	boucleinput=-1;
	while (boucleinput==-1){
while (SDL_PollEvent(&event)){

switch (event.type)
            {

case SDL_QUIT:
                    boucleinput=0;
		    input=0;
                    break;



}


}
	afficher_imageBTN2(screen,IMAGE_BTN2 ) ;
        

	SDL_Flip(screen);


}afficherTempsPuzzle(tempsDebut,dureeTotale, screen,funt);
}

}SDL_Flip(screen);



        
    }



liberer_image(IMAGE);
liberer_image(IMAGE_BTN1);
liberer_image(IMAGE_BTN2);
liberer_musique(music);

fclose(e.f);
TTF_Quit();
SDL_Quit();

    return 0;
}
