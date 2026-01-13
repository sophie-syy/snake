#ifndef SPAWN_H
#define SPAWN_H


#include "snake.h"


Bonus* create_Bonus(Map *map, Snake * snake); /*créer le bonus aléatoire*/

Bonus * init_Bonus(Snake * snake, Map *map); /*initialiser le bonus*/

void freeBonus(Bonus *bonus); /*libèrer le bonus*/

void write_bonus(Map *map, Bonus * bonus); /*Ecrire le bonus sur la map*/

Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake); /*suprimer le bonus*/



#endif
