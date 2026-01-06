#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "liste.h"


int menu_principal(char *nom_fichier) {
    int choix, choix2;
    printf("===== SNAKE =====\n");
    printf("1. Nouvelle partie\n");
    printf("2. Choisir la carte\n");
    printf("3. Partie sauvegardée\n");
    printf("4. Quitter\n");
    printf("Choix : ");
    scanf("%d", &choix);
    getchar();

    if (choix == 1) {
        printf("fichier %s\n",nom_fichier);
        return MENU_NOUVEAU;
    }
    if (choix == 2) {
        printf("Taille de la carte : \n");
        printf("1. carte%dx%d\n",16,9);
        printf("2. carte%dx%d\n",27,14);
        printf("3. carte%dx%d\n",49,18);
        scanf("%d", &choix2);
        getchar();

        if(choix2 == 1){
            strcpy(nom_fichier, "carte.txt");
        }
        if(choix2 == 2){
            strcpy(nom_fichier, "carte2.txt");
        }
        if(choix2 == 3){
            strcpy(nom_fichier, "carte3.txt");
        }
        return menu_principal(nom_fichier);
    }
    if (choix == 3) {
        return MENU_CHARGER;
    }
    return MENU_QUITTER;
}

char menu_jeu(void) {
    char c;
    printf("Direction (k o l m), quitter(q) sauvegarde(x): ");
    scanf("%c", &c);
    getchar();
    return c;
}

/*char* choix_carte(char *nom_fichier){
    int choix;
    printf("Taille de la carte : \n");
    printf("1. carte%dx%d\n",16,9);
    printf("2. carte%dx%d\n",27,14);
    printf("3. carte%dx%d\n",49,18);
    scanf("%d", &choix);
    getchar();
    
    if(choix == 1){
        nom_fichier = "carte.txt";
    }
    if(choix == 2){
        nom_fichier = "carte2.txt";
    }
    if(choix == 3){
        nom_fichier = "carte3.txt";
    }
    return nom_fichier;
}

void commencer(Map **map, Snake **snake, Bonus **bonus, char * nom_map){
    int choix = menu_principal(nom_map);

    if (choix == MENU_QUITTER) {
        printf("Au revoir !\n");
    }

    if (choix == MENU_NOUVEAU) {
        *map = load_map(nom_map);
        if (!*map) { printf("Erreur map\n"); }

        *snake = create_Snake();
        init(*snake);

        *bonus = create_Bonus(*map, *snake);
        *bonus = init_Bonus(*snake, *bonus, *map);
    }

    if (choix == MENU_CHARGER) {
        if (!charger(&(*snake), &(*bonus), &(*map), &(*nom_map))) {
            printf("Erreur chargement\n");
        }
    }
}

int menu_quitter(Map *map, Snake * snake, Bonus *bonus, char *nom_map) {
    int c;
    printf("Vous voulez vraiment quitté?: ");
    printf("1. sauvegarder\n");
    printf("2. recommencer\n");
    printf("3. Choisir la carte\n");
    printf("4. Quitter\n");
    scanf("%d", &c);
    getchar();
    if (c == '1') {
        sauvegarder(snake, bonus, nom_map);
        return 0;
    }else if (c == '2') {
        commencer(map, snake, bonus, nom_map);
        return 0;
    }else if (c == '3') {
        choix_carte(nom_map);
        commencer(map, snake, bonus, nom_map);
        return 0;
    }else if (c == '4') {
        printf("Fin de la partie\n");
        return 1;
    }else{
        return menu_quitter(map, snake, bonus, nom_map);
    }
}*/

void sauvegarder(Snake *snake, Bonus *bonus, char *nom_map) {
    FILE *f = fopen("sauvegarde/save.txt", "w");
    if (!f) { printf("Erreur ouverture save.txt\n"); return; }

    fprintf(f, "%s\n", nom_map);
    fprintf(f, "%d\n", snake->score);
    fprintf(f, "%d\n", snake->size);

    // Sauvegarde des segments
    int taille = 0;
    Noeud *nb = snake->body->sentAvt;
    while (taille <= snake->size) {
        if(taille > 0){
            fprintf(f, " %c ", nb->cont);
        }
        nb = nb->suiv;
        taille++;
    }
    fprintf(f, "\n");

    taille = 0;
    Noeud *nx = snake->x->sentAvt;
    while (taille <= snake->size) {
        if(taille > 0){
            fprintf(f, "%d ", nx->cont);
        }
        nx = nx->suiv;
        taille++;
    }
    fprintf(f, "\n");

    taille = 0;
    Noeud *ny = snake->y->sentAvt;
    while (taille <= snake->size) {
        if(taille > 0){
            fprintf(f, "%d ", ny->cont);
        }
        ny = ny->suiv;
        taille++;
    }
    fprintf(f, "\n");

    // Sauvegarde du bonus
    fprintf(f, "%d %d %d\n", bonus->x, bonus->y, bonus->pas);

    fclose(f);
    printf("Sauvegarde effectuée dans save.txt\n");
}

int charger(Snake **snake, Bonus **bonus, Map **map, char *nom_map) {
    FILE *f = fopen("sauvegarde/save.txt", "r");
    if (!f) return 0;

    // Nom de la map
    fscanf(f, "%s", nom_map);
    *map = load_map(nom_map);

    // Score et taille
    int score, size;
    fscanf(f, "%d", &score);
    fscanf(f, "%d", &size);

    *snake = create_Snake();
    (*snake)->score = score;
    (*snake)->size = size;

    // Ajouter les segments
    char b;
    int x, y;
    for (int i = 1; i <= size; i++) {
        fscanf(f, " %c ", &b);
        inserer((*snake)->body, i, b);
        afficherListe((*snake)->body, 2);
    }
    
    for (int k = 1; k <= size; k++) {
        fscanf(f, "%d", &x);
        inserer((*snake)->x ,k, x);
    }

    for (int j = 1; j <= size; j++) {
        fscanf(f, "%d", &y);
        inserer((*snake)->y, j, y);
    }
    
    // Charger le bonus
    int bx, by, pas;
    fscanf(f, "%d %d %d", &bx, &by, &pas);

    *bonus = create_Bonus(*map, *snake);
    (*bonus)->x = bx;
    (*bonus)->y = by;
    (*bonus)->pas = pas;

    fclose(f);
    return 1;
}