#ifndef MAP_H
#define MAP_H
#define LIRE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure représentant une carte (la grille):
typedef struct _map{ 
    char **data; // - data: tableau de lignes (chaînes de caractères), chaque ligne représente une rangée de la carte  
    int width; // - width: largeur de la carte (nombre de colonnes)
    int height; // - height: hauteur de la carte (nombre de lignes)
} Map;

Map *load_map(const char *filename); /* Lire le fichier de carte.txt et remplie la grille de la carte et initialise width et height */

void free_map(Map *map); /* Libère toute la mémoire associée à la carte (lignes + structure Map). */

void print_map(Map *map); /* affichier la carte dans la console */

#endif
