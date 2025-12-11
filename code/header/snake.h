#ifndef SNAKE_H
#define SNAKE_H

#include "liste.h"
#include "map.h"

typedef struct {
	Liste * snake;
	int size;
} Snake;

void init_position(Liste* l);

void mouvement_snake(Liste *l);

void eat_insert(char c);

void caseVide();

void eat();
 

#endif
