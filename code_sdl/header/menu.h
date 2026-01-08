#ifndef MENU_H
#define MENU_H

#include "spawn.h"

/* Codes menu principal */
#define MENU_QUITTER 0
#define MENU_NOUVEAU 1
#define MENU_CHARGER 2

/* Menu principal */
int menu_principal(char *nom_fichier);

/* Menu pendant le jeu */
char menu_jeu(int position);

/* Sauvegarder la partie dans save.txt */
void sauvegarder(Snake *snake, Bonus *bonus, char *nom_map);

/* Charger une partie depuis save.txt */
int charger(Snake **snake, Bonus **bonus, Map **map, char* nom_map);

#endif
