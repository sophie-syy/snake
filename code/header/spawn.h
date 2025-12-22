#ifndef SPAWN_H
#define SPAWN_H

#include "spawn.h"

typedef struct {
	char letter;
	int x;
	int y;
} Bonus;

bool have_letter();

Bonus* create_Bonus();

int number_steps();

void delete_bonus();

#endif
