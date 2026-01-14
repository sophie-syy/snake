#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "liste.h" // Permet d'utiliser le type Liste et les fonctions associées
#include "map.h" // Permet d'utiliser le type Map et les fonctions associées

#define NB_VOWEL 6 //nombre de voyelle

//structure de snake: taille, corps, les coordonnées x et y du corps, et le score
typedef struct _snake{
	int size; // - size  : taille du serpent
	Liste *body; // - body  : liste représentant le corps
	Liste *x; // Cordonnées x
	Liste *y; // Cordonnées y
	int score; // - score: score actuel du joueur
} Snake;

// Structure de bonus:
typedef struct _bonus{ 
	char letter; // Les lettres
	int x; // Cordonnés x de la lettre
	int y; // Cordonnés y de la lettre
	int footsteps; // Le nombre de pas du serpent
} Bonus;


Snake* create_Snake(); /*Créer le serpent (vide + réserver des places) */

void freeSnake(Snake *snake); /* Libèrer la mémoire du serpent */

void init_snake(Snake *snake); /* Initialiser le serpent */

void write_snake(Map *map, Snake *snake); /* Écrire le serpent dans la carte */

void delete_queue(Snake *snake); /* Supprimer que les coordonnées de la queue */

bool is_Bonus(Bonus *bonus, int x, int y); /* Booléen pour dire si la case du coordonnée x et y de la carte est un bonus ou non */

bool belongs_vowel(Bonus *bonus); /* Booléen pour dire si le bonus est une voyelle ou pas */

void eat_insert(Snake *snake, Bonus* bonus, Map *map); /* Manger le bonus */

bool belongs_snake(Snake* snake, int x, int y); /* Booléen pour dire si la case du coordonnée x et y de la carte est le corps du serpent ou non */

int case_next(Map *map, int x, int y, Bonus *bonus, Snake *snake); /* Voir la case du coordonnée x et y*/

int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus); /* Définir le mouvement du serpent selon le touche entrée(boutton)*/


#endif
