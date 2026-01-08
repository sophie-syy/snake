#ifndef SPAWN_H
#define SPAWN_H

#include <stdbool.h>
#include "snake.h"


Bonus* create_Bonus(Map *map, Snake * snake);

Bonus * init_Bonus(Snake * snake, Bonus *bonus, Map *map);

void freeBonus(Bonus *bonus);

void write_bonus(Map *map, Bonus * bonus);

Bonus* suprime_bonus(Map *map, Bonus *bonus, Snake * snake);

bool appartient_lettre(char variable);

bool est_Bonus(char variable, int x, int y, Bonus *bonus);

#endif
