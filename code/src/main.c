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
    Bonus * bonus = create_Bonus(map, snake);
    int x = 0;
    char s = 'l';

    if (argc < 2) printf("Usage: %s Donner le fichier map en arguments \n", argv[0]);
    if (map == NULL) return 1;
    init(snake);

    
    while(x!=1){
        write_bonus(map, bonus);
        write_snake(map, snake);
        printf("Map chargée (%dx%d) :\n", map->width, map->height);
        print_map(map);
        
        
        afficherListe(snake->body, 0);
        afficherListe(snake->x, 1);
        afficherListe(snake->y, 1);
        printf("pas = %d \n", bonus->pas);
        printf("%c %d %d \n", bonus->letter, bonus->x, bonus->y);

        map = load_map(argv[1]);
        printf("sens: \n");
        scanf("%c", &s);
        purge();

        x = mouvement_snake(snake, s, map, bonus);
        
        printf("x = %d\n", x);
        bonus = suprime_bonus(map, bonus, snake);
        if(x == 0) bonus->pas += 1;
    }
    printf("Perdu!\n");
    printf("score = %d \n", snake->score);
    free_map(map);
    return 0;
}
