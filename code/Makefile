fichier_o = obj/map.o obj/main.o obj/noeud.o obj/liste.o

all: map.o main.o noeud.o liste.o
	gcc $(fichier_o) -o bin/jeu

map.o: src/map.c
	gcc -c src/map.c -Wall -Iheader -o obj/map.o
	
noeud.o: src/noeud.c
	gcc -c src/noeud.c -Wall -Iheader -o obj/noeud.o
	
liste.o: src/liste.c
	gcc -c src/liste.c -Wall -Iheader -o obj/liste.o

main.o: src/main.c
	gcc -c src/main.c -Wall -Iheader -o obj/main.o
	
clean: 
	rm obj/*.o ; rm bin/jeu
