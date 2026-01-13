/*
Fichier principal du jeu de serpent
*/

#include <stdio.h> //pour ecrire et lire
#include <stdlib.h> //pour les réserves et libéres d'espace et aléatoire
#include <string.h> //pour les fonctions str: strlen(), strcpy()
#include <time.h> //pour utiliser time()

//pour utiliser tous les fonctions qu'on a créer pour le jeu: map, serpent, bonus et menu
#include "map.h" 
#include "snake.h"
#include "spawn.h"
#include "menu.h"


int main(void) {
    //initialisation des données 
    srand(time(NULL));//initialise le nombre de secondes écoulées depuis l'époque
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char name_map[100]; //tableau pour le nom du fichier de terrain (maximum 100 caractères)
    strcpy(name_map, "carte.txt");//initialiser a carte.txt

    int choix = menu_principal(name_map);//faire le choix
    //et selon le choix: partir, jouer, jouer le sauvegarde
    if (choix == MENU_LEAVE) {
        printf("Au revoir !\n");
        return 0;
    }

    if (choix == MENU_NEW) {
        map = load_map(name_map); //charger la map
        if (!map) { printf("Erreur map\n"); return 1; }//teste erreur de vide

        snake = create_Snake();//créer le sepent
        init_snake(snake); //initialiser a 'z'
        bonus = init_Bonus(snake, map); //créer le bonus
    }

    if (choix == MENU_LOAD) {
        //charger le sauvegarde, si il rentre, c'est qu'il y a un erreur
        if (!load_save(&snake, &bonus, &map, name_map)) {
            printf("Erreur chargement\n");
            return 1;
        }
    }
    
    //tant que le jeu roule, il mettre à jour
    int run = 0, choix2;
    while (!run) {
        //charger le bonus, le serpent et afficher la map
        write_bonus(map, bonus);
        write_snake(map, snake);
        print_map(map);

        printf("Score : %d\n", snake->score); //afficher le score

        char c = menu_direc_leave(1);//afficher la demande de sens

        //quitter
        if (c == 'q') {
            c = menu_direc_leave(2); //demande d'affirmation de quitter

            //sauvegarde et relance la demande d'affirmation de quitter
            while(c == 'x'){
                save(snake, bonus, name_map);
                c = menu_direc_leave(2);
            }

            //choisir la carte ou rejouer le jeu
            if (c == 'c' || c == 'r') {
                if(c == 'c'){
                    printf("\n");
                    printf(" ------------- Taille de la carte ------------- \n");
                    printf("1. carte%dx%d\n",16,9);
                    printf("2. carte%dx%d\n",27,14);
                    printf("3. carte%dx%d\n",49,18);
                    scanf("%d", &choix2);
                    getchar();

                    //change le nom de fichier selon le choix
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

                //lancer le nouveau jeu
                //libèrer les données
                freeSnake(snake);
                freeBonus(bonus);
                free_map(map);

                map = load_map(name_map); //recharge la map
                //recréer les données, et les initialisations
                snake = create_Snake();
                init_snake(snake);
                bonus = init_Bonus(snake, map);
            }

            //sûr et certin de quitter
            if (c == 'q') {
                printf("\n");
                printf("Fin de la partie\n");
                break;//sortir tout suite
            }
        }
        //les touches de sens
        else if(c == 'o' || c == 'l' ||c == 'k' ||c == 'm'){
            //le serpent mange(0)/avance(0)/perdre(1)
            run = mouvement_snake(snake, c, map, bonus);

            bonus = delete_bonus(map, bonus, snake);//vérifier si le nombre de pas>=10 et recréer
            if (run == 0) bonus->footsteps++;//ajouter un pas quand le serpent bouge
            
            free_map(map);//load_map créer une map, pour être sûr de ne pas fuite des mémoires, on libère
            map = load_map(name_map); //initialiser la map
            if (!map) { printf("Erreur map\n"); break; } //teste d'erreur de vide
        }else{
            
        }
        
    }

    //affichier le parole de fin
    printf("Perdu ! Score final : %d\n", snake->score);

    //libèrer tous les données a libèrer
    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);

    return 0;
}
