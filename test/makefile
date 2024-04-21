prog: main.o perso.o background.o
	gcc main.o perso.o background.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c background.h
	gcc -c main.c -o main.o -g

perso.o: perso.c
	gcc -c perso.c -o perso.o -g

background.o: background.c background.h
	gcc -c background.c -o background.o -g
