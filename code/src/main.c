#include <stdio.h>
#include "map.h"

int main() {
    Map *map = load_map("map.txt");

    if (!map) return 1;

    printf("Map chargée (%dx%d)(taille de map largeurxhauteur) :\n", map->width, map->height);

    print_map(map);
    free_map(map);
    return 0;
}
