prog: main.o perso.o
	gcc main.o perso.o -o prog -lSDL -lSDL_image -g -lSDL_ttf  
main.o: main.c
	gcc -c main.c -g
perso.o: perso.c
	gcc -c perso.c -g
