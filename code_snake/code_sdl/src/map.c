#include "map.h"

/*lire selon le fichier donné, en créant la map au fur et à mesure, et retourner la map*/
Map *load_map(const char *filename) {
    char fullpath[50]; 
    snprintf(fullpath, sizeof(fullpath),"sauvegarde/%s", filename); 
    FILE *file = fopen(fullpath, "r"); 

    if (file == NULL) {
        perror("Erreur d'ouverture de carte.txt");
    }
    Map *map = malloc(sizeof(Map)); 
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
        map->data[map->height] = malloc(map->width + 1);
        strcpy(map->data[map->height], buffer);
        map->height++; 
    }
    fclose(file);
    return map; 
}

// libère memoire allouée de la map
void free_map(Map *map) {
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]); 
    }
    free(map->data); 
    free(map); 
}

// affiche la map sur terminal
void print_map(Map *map) { 

    for (int i = 0; i < map->height; i++) {
        printf("%s\n", map->data[i]); 
    }
}
