all: map.o main.o
	gcc obj/map.o obj/main.o -o bin/jeu -lm

main.o: src/main.c header/map.h
	gcc -c src/main.c -Wall -lm
	
map.o: src/map.c header/map.h
	gcc -c src/map.c -Wall -lm
	
clean: 
	rm obj/*.o ; rm bin/jeu
