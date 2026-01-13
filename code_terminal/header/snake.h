#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "liste.h" //pour utiliser liste et ses fonctions
#include "map.h" //pour utiliser map et autre bibliothèque incluse dans dans ses 2 fichier .h
#define NB_VOWEL 6 //nombre de voyelle

//structure de snake: taille, corps, les coordonnées x et y du corps, et le score
typedef struct _snake{
	int size;
	Liste *body;
	Liste *x;
	Liste *y;
	int score;
} Snake;

//structure de bonus: la lettre, le coordonée x et y de la lettre, et le nombre de pas du serpent
typedef struct _bonus{
	char letter;
	int x;
	int y;
	int footsteps;
} Bonus;


Snake* create_Snake(); /*Créer le serpent tout vide (réserver des places)*/

void freeSnake(Snake *snake); /*Libèrer le serpent*/

void init_snake(Snake *snake); /*Initialiser le serpent */

void write_snake(Map *map, Snake *snake); /*Écrire le serpent dans la map*/

void delete_queue(Snake *snake); /*Suprimer que le coordonnée de la queue*/

bool is_Bonus(Bonus *bonus, int x, int y); /*Booléen pour dire si la case du coordonnée x et y de la map est un bonus ou pas*/

bool belongs_vowel(Bonus *bonus); /*Booléen pour dire si le bonus est une voyelle ou pas*/

void eat_insert(Snake *snake, Bonus* bonus, Map *map); /*Manger le bonus*/

bool belongs_snake(Snake* snake, int x, int y);/*Booléen pour dire si la case du coordonnée x et y de la map est le corps du serpent ou pas*/

int case_next(Map *map, int x, int y, Bonus *bonus, Snake *snake); /*Voir la case du coordonnée x et y*/

int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus); /*définir le mouvement du serpent selon le touche entrée(boutton)*/


#endif
