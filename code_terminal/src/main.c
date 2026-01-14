/* Fichier principal du jeu de serpent */

#include <stdio.h> // Pour écrire et lire
#include <stdlib.h> // Pour les réserves et libéres d'espace et aléatoire
#include <string.h> // Pour les fonctions str: strlen(), strcpy()
#include <time.h> // Pour utiliser time()

// Pour utiliser tous les fonctions qu'on à créer pour le jeu: map, serpent, bonus et menu
#include "map.h" 
#include "snake.h"
#include "spawn.h"
#include "menu.h"


int main(void) {
    // Initialisation des données 
    srand(time(NULL)); // Initialise le nombre de secondes écoulées depuis l'époque
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char name_map[100]; // Tableau pour le nom du fichier de terrain (maximum 100 caractères)
    strcpy(name_map, "carte.txt"); // Initialise la carte.txt

    int choix = menu_principal(name_map); // Faire le choix
    // Et selon le choix: partir, jouer, jouer et le sauvegarde
    if (choix == MENU_LEAVE) {
        printf("Au revoir !\n");
        return 0;
    }

    if (choix == MENU_NEW) {
        map = load_map(name_map); // Charger la carte
        if (!map) { printf("Erreur map\n"); return 1; } // Tester si vide

        snake = create_Snake(); // Créer le sepent
        init_snake(snake); // Initialiser à 'z'
        bonus = init_Bonus(snake, map); // Créer le bonus
    }

    if (choix == MENU_LOAD) {
        // Charger le sauvegarde, si il rentre, c'est qu'il y a un erreur
        if (!load_save(&snake, &bonus, &map, name_map)) {
            printf("Erreur chargement\n");
            return 1;
        }
    }
    
    // Tantque le jeu roule, il mettre à jour
    int run = 0, choix2;
    while (!run) {
        // Charger le bonus, le serpent et affiche la carte
        write_bonus(map, bonus);
        write_snake(map, snake);
        print_map(map);

        printf("Score : %d\n", snake->score); // Afficher le score

        char c = menu_direc_leave(1); // Affiche la demande du sens

        // Quitter
        if (c == 'q') {
            c = menu_direc_leave(2); // Demande d'affirmation de quitter

            // Sauvegarde et relance la demande d'affirmation de quitter
            while(c == 'x'){
                save(snake, bonus, name_map);
                c = menu_direc_leave(2);
            }

            // Choisir la carte ou rejouer le jeu
            if (c == 'c' || c == 'r') {
                if(c == 'c'){
                    printf("\n");
                    printf(" ------------- Taille de la carte ------------- \n");
                    printf("1. carte%dx%d\n",16,9);
                    printf("2. carte%dx%d\n",27,14);
                    printf("3. carte%dx%d\n",49,18);
                    scanf("%d", &choix2);
                    getchar();

                    // Change le nom de fichier selon le choix
                    if(choix2 == 1){
                        strcpy(name_map, "carte.txt");
                    }
                    if(choix2 == 2){
                        strcpy(name_map, "carte2.txt");
                    }
                    if(choix2 == 3){
                            strcpy(name_map, "carte3.txt");
                    }
                }

                // Lance le nouveau jeu
                // Libèrer la mémoire des données: serpent, bonus et carte
                freeSnake(snake);
                freeBonus(bonus);
                free_map(map);

                map = load_map(name_map); // Recharge la carte
                // Recréer les données, et les initialisations
                snake = create_Snake();
                init_snake(snake);
                bonus = init_Bonus(snake, map);
            }

            // Sûre et certain de quitter
            if (c == 'q') {
                printf("\n");
                printf("Fin de la partie\n");
                break; // Sortir imédiatement
            }
        }
        // Les touches de direction
        else if(c == 'o' || c == 'l' ||c == 'k' ||c == 'm'){
            // Le serpent mange(0)/avance(0)/perdre(1)
            run = mouvement_snake(snake, c, map, bonus);

            bonus = delete_bonus(map, bonus, snake); // Vérifier si le nombre de pas >= 10 et recréer
            if (run == 0) bonus->footsteps++; // Ajouter un pas quand le serpent bouge
            
            free_map(map); // load_map créer une carte, pour être sûr de ne pas avoir de fuite de mémoires donc on libère
            map = load_map(name_map); // Initialiser la map
            if (!map) { printf("Erreur map\n"); break; } // Teste d'erreur de vide
        }else{
            
        }
        
    }

    // Affichier le phrase de fin
    printf("Perdu ! Score final : %d\n", snake->score);

    // Libèrer toutes les données de la mémoire à libèrer
    freeSnake(snake); 
    freeBonus(bonus);
    free_map(map);

    return 0;
}
