WAKEUP: main.o perso.o background.o enemy.o heart.o boundingbox.o
	gcc main.o perso.o background.o enemy.o heart.o boundingbox.o -o WAKEUP -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c background.h perso.h enemy.h
	gcc -c main.c -o main.o -g

perso.o: perso.c perso.h
	gcc -c perso.c -o perso.o -g

background.o: background.c background.h
	gcc -c background.c -o background.o -g

enemy.o: enemy.c enemy.h
	gcc -c enemy.c -o enemy.o -g	
	
heart.o: heart.c heart.h
	gcc -c heart.c -o heart.o -g	

boundingbox.o: boundingbox.c boundingbox.h
	gcc -c boundingbox.c -o boundingbox.o -g	
