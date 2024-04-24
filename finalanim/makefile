WAKE UP: main.o perso.o background.o enemy.o minimap.o
	gcc main.o perso.o background.o enemy.o minimap.o -o WAKEUP -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g

main.o: main.c background.h perso.h enemy.h minimap.h
	gcc -c main.c -o main.o -g

perso.o: perso.c
	gcc -c perso.c -o perso.o -g

background.o: background.c background.h
	gcc -c background.c -o background.o -g
	
enemy.o: enemy.c enemy.h
	gcc -c enemy.c -o enemy.o -g 

minimap.o:minimap.c minimap.h
	gcc -c minimap.c -o minimap.o -g
