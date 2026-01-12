#ifndef MENU_H
#define MENU_H

#include "spawn.h"

/* Codes menu principal */
#define MENU_LEAVE 0
#define MENU_NEW 1
#define MENU_LOAD 2

void purge(void);/*vider un scanf de '\n'*/

int menu_principal(char *nom_fichier);/* Menu principal */

char menu_direc_leave(int position);/* Menu pendant le jeu */

void save(Snake *snake, Bonus *bonus, char *nom_map);/* Sauvegarder la partie dans save.txt */

int load_save(Snake **snake, Bonus **bonus, Map **map, char* nom_map);/* Charger une partie depuis save.txt */

#endif
