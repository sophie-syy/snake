#ifndef SPAWN_H
#define SPAWN_H


#include "snake.h"


Bonus* create_Bonus(Map *map, Snake * snake); /* Créer le bonus aléatoire */

Bonus * init_Bonus(Snake * snake, Map *map); /* Initialise le bonus */

void freeBonus(Bonus *bonus); /* Libèrer la mémoire du bonus */

void write_bonus(Map *map, Bonus * bonus); /* Ecrire le bonus sur la carte */

Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake); /* Supprimer le bonus */

#endif
