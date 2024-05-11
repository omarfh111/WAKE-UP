prog: enigme.o main.o 
	gcc enigme.o main.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c 
	gcc -c main.c -g 
enigme.o : enigme.c 
	gcc -c enigme.c -g 
