prog: main.o enemy.o
	gcc main.o enemy.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c enemy.h
	gcc -c main.c -o main.o -g

enemy.o: enemy.c enemy.h
	gcc -c enemy.c -o enemy.o -g


