prog:fonctions.o main.o
	gcc background.o main.o -o prog -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
main.o:main.c background.h
	gcc -c main.c main.o -g
fonctions.o:background.c background.h
	gcc -c background.c -o background.o -g
