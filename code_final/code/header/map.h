#ifndef MAP_H
#define MAP_H
#define LIRE 1024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//structure de map: matrisse, longeur, largeur
typedef struct _map{
    char **data;   
    int width;     
    int height;   
} Map;

Map *load_map(const char *filename); //lire le fichier de carte.txt et remplie la matrisse de la map et ses tailles 

void free_map(Map *map); //libèrer la map

void print_map(Map *map); //affichier la map

#endif
