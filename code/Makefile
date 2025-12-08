all: map.o main.o
	gcc obj/map.o obj/main.o -o bin/jeu -lm

map.o: src/map.c
	gcc -c src/map.c -Wall -Iheader -o obj/map.o

main.o: src/main.c
	gcc -c src/main.c -Wall -Iheader -o obj/main.o
	
clean: 
	rm obj/*.o ; rm bin/jeu
