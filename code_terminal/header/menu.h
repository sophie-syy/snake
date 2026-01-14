#ifndef MENU_H
#define MENU_H

#include "spawn.h"

/* Codes menu principal */
#define MENU_LEAVE 0 // - MENU_LEAVE: quitter le programme
#define MENU_NEW 1 // - MENU_NEW: lancer une nouvelle partie
#define MENU_LOAD 2 // - MENU_LOAD: charger une partie qui est sauvegardée

void purge(void); /* Vider un scanf de '\n', pour éviter des lectures incorrectes.*/

int menu_principal(char *nom_fichier); /* Affiche le menu principal du jeu et met à jour le nom du fichier de carte si nécessaire */

char menu_direc_leave(int position); /* Affiche le menu pendant le jeu */
// position : option actuellement sélectionnée

void save(Snake *snake, Bonus *bonus, char *nom_map); /* Sauvegarder l'état actuel de la partie dans le fichier "save.txt":
snake: - position et état du snake
bonus: - bonus présents
nom_map: -nom de la carte utilisée */

int load_save(Snake **snake, Bonus **bonus, Map **map, char* nom_map); 
/* Charge une partie depuis le fichier "save.txt" (initialise: snake, bonus et la carte + met à jour le nom de la carte)*/

#endif
