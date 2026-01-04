#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "liste.h"
#include "map.h"


typedef struct _snake{
	int size;
	Liste *body;
	Liste *x;
	Liste *y;
	int score;
} Snake;

typedef struct _bonus{
	char letter;
	int x;
	int y;
	int pas;
} Bonus;


Snake* create_Snake();

void freeSnake(Snake *snake);

void init(Snake *snake);

void write_snake(Map *map, Snake *snake);

void suprime_queue(Snake *snake);

bool estBonus(Bonus *bonus, int x, int y);

int what_is_case(const Map *map, int x, int y, Bonus *bonus);

int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus);


#endif
