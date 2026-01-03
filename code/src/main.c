#include <stdio.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"


int main(int argc, char *argv[]) {
    Map *map = load_map(argv[1]);
    Snake *snake = create_Snake();
    Bonus * bonus = create_Bonus(map);
    int score = 0, x = 0;
    char s;

    if (argc < 2) printf("Usage: %s Donner le fichier map en arguments \n", argv[0]);
    if (map == NULL) return 1;
    init(snake);


    while(x!=1){
        write_snake(map, snake);
        write_bonus(map, bonus);
        printf("Map chargée (%dx%d) :\n", map->width, map->height);
        print_map(map);
        
        
        afficherListe(snake->body, 0);
        afficherListe(snake->x, 1);
        afficherListe(snake->y, 1);
        printf("%d", bonus->pas);

        map = load_map(argv[1]);
        printf("sens: ");
        scanf("%c", &s);

    
        x = mouvement_snake(snake, s, map);
        bonus = suprime_bonus(map, bonus);
        if(x == 0) bonus->pas += 1;
    }
    printf("Perdu!");
    free_map(map);
    return 0;
}
