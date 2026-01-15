#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "liste.h" 
#include "map.h" 

#define NB_VOWEL 6 

//structure de snake: taille, corps, les coordonnées x et y du corps, et le score
typedef struct _snake{
	int size; 
	Liste *body; 
	Liste *x; 
	Liste *y; 
	int score; 
} Snake;

// Structure de bonus:
typedef struct _bonus{ 
	char letter; 
	int x; 
	int y; 
	int footsteps; 
} Bonus;


Snake* create_Snake(); 

void freeSnake(Snake *snake); 

void init_snake(Snake *snake); 

void write_snake(Map *map, Snake *snake); 

void delete_queue(Snake *snake); 

bool is_Bonus(Bonus *bonus, int x, int y); 

bool belongs_vowel(Bonus *bonus); 

void eat_insert(Snake *snake, Bonus* bonus, Map *map); 

bool belongs_snake(Snake* snake, int x, int y); 
int case_next(Map *map, int x, int y, Bonus *bonus, Snake *snake); 

int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus); 

#endif
