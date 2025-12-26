#ifndef SNAKE_H
#define SNAKE_H

#include "liste.h"
#include "map.h"
#include "spawn.h"

typedef struct _snake{
	int size;
	Liste *body;
	Liste *x;
	Liste *y;
	int score;
} Snake;

Snake* create_Snake();

void init(Snake *snake);

void eat_insert(Snake *snake, Bonus* c);

bool belongs_to_snake(Snake* snake, Bonus* c);

void mouve_snake(Snake *snake, char button);

void what_is_case(const Map *map, int x, int y);

#endif
