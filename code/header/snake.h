#ifndef SNAKE_H
#define SNAKE_H

#include "liste.h"
#include "map.h"

typedef struct {
	int size;
	Liste *body;
	Liste *x;
	Liste *y;
} Snake;

Snake *create_Snake(char c);

void init(Snake *snake);

void mouve_snake(Snake *snake, Map *map);

void eat_insert(Snake *snake,char c);

void what_is_case(const Map *map, int x, int y);

#endif
