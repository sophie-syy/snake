#include <stdio.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"

void purge(void){
    int c = 0;
    while ((c=getchar())!='\n' && c!= EOF);
}

int main(int argc, char *argv[]) {
    Map *map = load_map(argv[1]);
    Snake *snake = create_Snake();
    Bonus * bonus = init_Bonus(snake, create_Bonus(map, snake), map);
    int x = 0;
    char s;

    if (argc < 2) printf("Usage: %s Donner le fichier map en arguments \n", argv[0]);
    if (map == NULL) return 1;
    init(snake);

    
    while(x!=1){
        /*printf("Vous voulez continué ou une nouvel? (c/n): ");
        scanf("%c", &s);
        purge();

        if(s == 'c'){
            map = load_map(argv[2]);
        }*/


        write_bonus(map, bonus);
        write_snake(map, snake);

        printf("Map chargée (%dx%d) :\n", map->width, map->height);
        print_map(map);
        
        printf("--------------\n");
        
        printf("Snake: \n");
        afficherListe(snake->body, 0);
        afficherListe(snake->x, 1);
        afficherListe(snake->y, 1);

        printf("--------------\n");

        printf("pas = %d \n", bonus->pas);
        
        printf("score = %d \n", snake->score);
        printf("--------------\n");

        map = load_map(argv[1]);

        printf("sens: ");
        scanf("%c", &s);
        purge();

        x = mouvement_snake(snake, s, map, bonus);
        
        bonus = suprime_bonus(map, bonus, snake);
        if(x == 0) bonus->pas += 1;
    }

    printf("--------------\n");
    printf("Perdu!\n");
    printf("score = %d \n", snake->score);

    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);
    return 0;
}
