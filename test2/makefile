WAKE UP: main.o perso.o background.o enemy.o
	gcc main.o perso.o background.o enemy.o -o WAKEUP -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c background.h
	gcc -c main.c -o main.o -g

perso.o: perso.c
	gcc -c perso.c -o perso.o -g

background.o: background.c background.h
	gcc -c background.c -o background.o -g
	
enemy.o: enemy.c enemy.h
	gcc -c enemy.c -o enemy.o -g 
