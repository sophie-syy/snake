#include <stdio.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s Donner le fichier map en arguments \n", argv[0]);
        return 1;
    }

    Map *map = load_map(argv[1]);
    if (map == NULL) {
        return 1;  
    }

    printf("Map chargée (%dx%d) :\n", map->width, map->height);
    print_map(map);
    
    Snake *snake = create_Snake();
    init(snake);

    Bonus* bonus = create_Bonus('x', 1, 1);
    eat_insert(snake, bonus);
    afficherListe(snake->body);
    afficherListe(snake->x);
    afficherListe(snake->y);

    // free_map(map);
    return 0;
}
