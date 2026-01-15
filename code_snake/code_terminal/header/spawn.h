#ifndef SPAWN_H
#define SPAWN_H


#include "snake.h"


Bonus* create_Bonus(Map *map, Snake * snake); 

Bonus * init_Bonus(Snake * snake, Map *map); 

void freeBonus(Bonus *bonus);

void write_bonus(Map *map, Bonus * bonus); 

Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake); 

#endif
