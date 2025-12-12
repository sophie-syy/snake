#include <stdio.h>
#include "map.h"
#include "snake.h"

int main(int argc, char *argv[]) {
    char c;
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
    
    printf("à quoi veux tu que ressemble ton serpant au debut, donne un carractère(a,b,c,o.....)");
    scanf("%c,&c")
    Snake *snake = creeSnake(c);

    while true {

    }
    // free_map(map);
    return 0;
}
