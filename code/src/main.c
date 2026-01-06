#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    
    int fin = 0, choix2;
    while (!fin) {
        write_bonus(map, bonus);
        write_snake(map, snake);
        printf("carte %dx%d\n", map->height, map->width);
        print_map(map);
        afficherListe(snake->body, 2);
        afficherListe(snake->x, 1);
        afficherListe(snake->y, 1);

        printf("Score : %d\n", snake->score);

        char c = menu_jeu(1);

        if (c == 'q') {
            c = menu_jeu(2);
            while(c == 'x' || c == 'c'){
                if (c == 'x') {
                    sauvegarder(snake, bonus, nom_map);
                }
                if (c == 'c') {
                    printf("Taille de la carte : \n");
                    printf("1. carte%dx%d\n",16,9);
                    printf("2. carte%dx%d\n",27,14);
                    printf("3. carte%dx%d\n",49,18);
                    scanf("%d", &choix2);
                    getchar();

                    if(choix2 == 1){
                        strcpy(nom_map, "carte.txt");
                    }
                    if(choix2 == 2){
                        strcpy(nom_map, "carte2.txt");
                    }
                    if(choix2 == 3){
                        strcpy(nom_map, "carte3.txt");
                    }
                }
                c = menu_jeu(2);
            }
            if (c == 'r') {
                freeSnake(snake);
                freeBonus(bonus);
                free_map(map);

                map = load_map(nom_map);
                snake = create_Snake();
                init(snake);
                bonus = init_Bonus(snake, create_Bonus(map, snake), map);
            }
            if (c == 'q') {
                printf("Fin de la partie\n");
                break;
            }
        }
        if(c == 'o' || c == 'l' ||c == 'k' ||c == 'm'){
                fin = mouvement_snake(snake, c, map, bonus);

                bonus = suprime_bonus(map, bonus, snake);
                if (!fin) bonus->pas++;

                free_map(map);
                map = load_map(nom_map);
                if (!map) { printf("Erreur map\n"); break; }
            }
        
    }

    printf("Perdu ! Score final : %d\n", snake->score);

    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);

    return 0;
}
