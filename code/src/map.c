#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"

Map *load_map(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Erreur d'ouverture de map.txt");
        return NULL;
    }

    Map *map = malloc(sizeof(Map));
    if (map == NULL) {
        perror("Erreur d'allocation mémoire pour la carte");
        fclose(file);
        return NULL;
    }

    map->data = NULL;
    map->width = 0;
    map->height = 0;

    char buffer[1024];

    while (fgets(buffer, sizeof(buffer), file)) {
        int len = strlen(buffer);

        if (buffer[len - 1] == '\n')  
            buffer[len - 1] = '\0';

        if (map->width == 0)
            map->width = strlen(buffer); 

        map->data = realloc(map->data, sizeof(char *) * (map->height + 1));
        if (map->data == NULL) {
            perror("Erreur de réallocation mémoire pour les données de la carte");
            free(map);
            fclose(file);
            return NULL;
        }

        
        map->data[map->height] = malloc(map->width + 1);
        if (map->data[map->height] == NULL) {
            perror("Erreur d'allocation mémoire pour une ligne de la carte");
            free(map->data);
            free(map);
            fclose(file);
            return NULL;
        }

        strcpy(map->data[map->height], buffer);
        map->height++;
    }

    fclose(file);
    return map;
}

void print_map(Map *map) {
    for (int i = 0; i < map->height; i++) {
        printf("%s\n", map->data[i]);
    }
}

void free_map(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]); 
    }

    free(map->data); 
    free(map);        
}
