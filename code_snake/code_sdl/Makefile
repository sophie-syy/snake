fichier_o = obj/map.o obj/main.o obj/noeud.o obj/liste.o obj/snake.o obj/spawn.o

all: map.o main.o noeud.o liste.o snake.o spawn.o 
	gcc $(fichier_o) -o bin/jeu -lSDL2 -lSDL2_ttf -lm `sdl2-config --cflags --libs`

map.o: src/map.c
	gcc -c src/map.c -Wall -Iheader -o obj/map.o
	
noeud.o: src/noeud.c
	gcc -c src/noeud.c -Wall -Iheader -o obj/noeud.o
	
liste.o: src/liste.c
	gcc -c src/liste.c -Wall -Iheader -o obj/liste.o

snake.o: src/snake.c
	gcc -c src/snake.c -Wall -Iheader -o obj/snake.o

spawn.o: src/spawn.c
	gcc -c src/spawn.c -Wall -Iheader -o obj/spawn.o

	
main.o: src/main.c
	gcc -c src/main.c -Wall -Iheader -o obj/main.o -lSDL2 -lSDL2_ttf -lm `sdl2-config --cflags --libs` 

clean: 
	rm obj/*.o ; rm bin/jeu

