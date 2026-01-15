#ifndef MAP_H
#define MAP_H
#define LIRE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure représentant une carte (la grille):
typedef struct _map{ 
    char **data; 
    int width; 
    int height; 
} Map;

Map *load_map(const char *filename); 

void free_map(Map *map); 
void print_map(Map *map); 

#endif
