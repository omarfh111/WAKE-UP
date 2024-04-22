prog:minimap.o main.o
	gcc main.c minimap.c -o prog -g -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
main.o:main.c minimap.h
	gcc -c main.c -o main.o -g

minimap.o:minimap.c minimap.h
	gcc -c minimap.c -o minimap.o -g

