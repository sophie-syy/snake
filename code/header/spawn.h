#ifndef SPAWN_H
#define SPAWN_H

#include <stdbool.h>

typedef struct _bonus{
	char letter;
	int x;
	int y;
} Bonus;

Bonus* create_Bonus(char letter, int x, int y);

void freeBonus(Bonus *bonus);

bool have_letter();

int number_steps();

void delete_bonus();

#endif
