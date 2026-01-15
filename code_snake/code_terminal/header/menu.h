#ifndef MENU_H
#define MENU_H

#include "spawn.h"

/* Codes menu principal */
#define MENU_LEAVE 0 
#define MENU_NEW 1 
#define MENU_LOAD 2 
void purge(void); 

int menu_principal(char *nom_fichier); 

char menu_direc_leave(int position); 
void save(Snake *snake, Bonus *bonus, char *nom_map); 


int load_save(Snake **snake, Bonus **bonus, Map **map, char* nom_map); 

#endif
