#include <stdio.h>
#include <stdlib.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"
#include "menu.h"


int main(void) {
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char nom_map[100] = "carte.txt";

    int choix = menu_principal(nom_map);

    if (choix == MENU_QUITTER) {
        printf("Au revoir !\n");
        return 0;
    }

    if (choix == MENU_NOUVEAU) {
        printf("fichier %s\n",nom_map);
        map = load_map(nom_map);
        if (!map) { printf("Erreur map\n"); return 1; }

        snake = create_Snake();
        init(snake);

        bonus = create_Bonus(map, snake);
        bonus = init_Bonus(snake, bonus, map);
    }

    if (choix == MENU_CHARGER) {
        if (!charger(&snake, &bonus, &map, nom_map)) {
            printf("Erreur chargement\n");
            return 1;
        }
    }
    
    int fin = 0;
    while (!fin) {
        write_bonus(map, bonus);
        write_snake(map, snake);
        printf("carte %dx%d\n", map->height, map->width);
        print_map(map);

        printf("Score : %d\n", snake->score);

        char c = menu_jeu();

        if (c == 'x') {
            sauvegarder(snake, bonus, nom_map);
            continue;
        }
        if (c == 'q') {
            printf("Fin de la partie\n");
            break;
        }

        fin = mouvement_snake(snake, c, map, bonus);

        bonus = suprime_bonus(map, bonus, snake);
        if (!fin) bonus->pas++;

        free_map(map);
        map = load_map(nom_map);
        if (!map) { printf("Erreur map\n"); break; }
    }

    printf("Perdu ! Score final : %d\n", snake->score);

    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);

    return 0;
}
