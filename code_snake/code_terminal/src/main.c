#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include "map.h" 
#include "snake.h"
#include "spawn.h"
#include "menu.h"


int main(void) {
    srand(time(NULL)); 
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char name_map[100]; // Tableau pour le nom du fichier de terrain (maximum 100 caractères)
    strcpy(name_map, "carte.txt"); // name_carte.txt <- "carte.txt"

    int choix = menu_principal(name_map); // choix <- menu_principal(name_map)
    if (choix == MENU_LEAVE) {//si choix est quitter
        printf("Au revoir !\n");
        return 0;
    }

    if (choix == MENU_NEW) { // si choix est nouvel partie
        map = load_map(name_map); // map <- load(name_map)
        if (!map) { printf("Erreur map\n"); return 1; } 
        snake = create_Snake(); 
        init_snake(snake); 
        bonus = init_Bonus(snake, map); 
    }

    if (choix == MENU_LOAD) { //Si choix charger une sauvegarde
        if (!load_save(&snake, &bonus, &map, name_map)) { //Si load_save(l'ancien snake,les bonus,l'ancienne map, nom de la map choisie)
            printf("Erreur chargement\n");
            return 1; 
        }
    }
    
   
    int run = 0, choix2; // run <- 0 et creation de choix2
    while (!run) { // Tant que !run , !run = 1 (True)
        write_bonus(map, bonus); // write_bonus(la map, les bonus)
        write_snake(map, snake);// write_snake(la map, le serpant)
        print_map(map);
        printf("Score : %d\n", snake->score); // Afficher le score
        char c = menu_direc_leave(1);
        if (c == 'q') { // Si c == q (quitter)
            c = menu_direc_leave(2); 
            while(c == 'x'){
                save(snake, bonus, name_map); // save(le serpant,bonus, nom de la map) pour savegardée
                c = menu_direc_leave(2);
            }
            if (c == 'c' || c == 'r') {
                if(c == 'c'){
                    printf("\n");
                    printf(" ------------- Taille de la carte ------------- \n");
                    printf("1. carte%dx%d\n",16,9);
                    printf("2. carte%dx%d\n",27,14);
                    printf("3. carte%dx%d\n",49,18);
                    scanf("%d", &choix2);
                    getchar();

                    
                    if(choix2 == 1){
                        strcpy(name_map, "carte.txt");//carte par defauts 1
                    }
                    if(choix2 == 2){
                        strcpy(name_map, "carte2.txt");//carte par defauts 2
                    }
                    if(choix2 == 3){
                            strcpy(name_map, "carte3.txt");//carte par defauts 3
                    }
                }
                freeSnake(snake); //libérer memoire serpant
                freeBonus(bonus); //libérer memoire bonus
                free_map(map);// libérer memoire carte
                map = load_map(name_map); // map <- load_map(le nom de la carte)
                snake = create_Snake();// snake <- creer le serpant
                init_snake(snake);// initinialisation (le serpant)
                bonus = init_Bonus(snake, map);//bounus <- init_bonus(serpant, la carte)
            }
            if (c == 'q') {
                printf("\n");
                printf("Fin de la partie\n");
                break; 
            }
        }
        else if(c == 'o' || c == 'l' ||c == 'k' ||c == 'm'){ // Les touches de directionnel
            run = mouvement_snake(snake, c, map, bonus);// run <- mouvement_snake(le serpant, caractère, la carte, bonus)
            bonus = delete_bonus(map, bonus, snake); // bonus <- delete_bonus(la carte, le bonus, le serpant)
            if (run == 0) bonus->footsteps++; 
            free_map(map); // lebère memoire carte
            map = load_map(name_map); // map <- load_map(nom de la map)
            if (!map) { printf("Erreur map\n"); break; } 
        }else{
            
        }
        
    }

   
    printf("Perdu ! Score final : %d\n", snake->score); 
    freeSnake(snake); 
    freeBonus(bonus);
    free_map(map);
    return 0;
}
