#include <stdio.h>
#include "map.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s Donner le fichier map en commentaire \n", argv[0]);
        return 1;
    }

    Map *map = load_map(argv[1]);
    if (map == NULL) {
        return 1;  
    }

    printf("Map chargée (%dx%d) :\n", map->width, map->height);

    print_map(map);
    free_map(map);
    return 0;
}
