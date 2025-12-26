#ifndef SPAWN_H
#define SPAWN_H

#include "spawn.h"
#include <stdbool.h>

typedef struct _bonus{
	char letter;
	int x;
	int y;
} Bonus;

bool have_letter();

Bonus* create_Bonus();

int number_steps();

void delete_bonus();

#endif
