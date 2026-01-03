#ifndef SPAWN_H
#define SPAWN_H

#include <stdbool.h>
#include "snake.h"


typedef struct _bonus{
	char letter;
	int x;
	int y;
	int pas;
} Bonus;

Bonus* create_Bonus(Map *map, Snake * snake);

bool check_bonus(Snake * snake, Bonus *bonus);

void freeBonus(Bonus *bonus);

void write_bonus(Map *map, Bonus * bonus);

Bonus* suprime_bonus(Map *map, Bonus *bonus, Snake * snake);

#endif
