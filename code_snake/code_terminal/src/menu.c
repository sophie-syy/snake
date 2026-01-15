#include "menu.h"

//// Vider le scanf tantque il y a '\n' ou EOF avec getchar() 
void purge(void){
    int c = 0;
    while ((c=getchar())!='\n' && c!= EOF);
}

/* affichier le menu de début, et demande le choix au joueur,
si change le nom du ficher entrée si le joueur demande et retourne un constante symbolique (definie par nous)*/
int menu_principal(char *name_fichier) { 
    int choix, choix2;
    printf("\n");
    printf(" ==================== SNAKE ==================== \n");
    printf("1. Nouvelle partie\n");
    printf("2. Choisir la carte\n");
    printf("3. Partie sauvegardée\n");
    printf("4. Quitter\n");
    printf("Choix : ");
    scanf("%d", &choix);
    purge();

    if (choix == 1) {
        return MENU_NEW;
    }
    if (choix == 2) {
        printf("\n");
        printf(" ------------- Taille de la carte ------------- \n");
        printf("1. carte%dx%d\n",16,9);
        printf("2. carte%dx%d\n",27,14);
        printf("3. carte%dx%d\n",49,18);
        scanf("%d", &choix2);
        purge();
        if(choix2 == 1){
            strcpy(name_fichier, "carte.txt");
        }
        if(choix2 == 2){
            strcpy(name_fichier, "carte2.txt");
        }
        if(choix2 == 3){
            strcpy(name_fichier, "carte3.txt");
        }
        return MENU_NEW;
    }

    if (choix == 3) {
        return MENU_LOAD;
    }
    return MENU_LEAVE;
}

// Menu pendant le jeu, il affiche le menu pour les touches ou le menu pour sortir du jeu selon position
char menu_direc_leave(int position) {
    char c;
    if(position == 1){
        printf("Direction (k o l m), quitter(q): "); 
    }else{
        printf("\n");
        printf(" ******** Vous voulez vraiment quitté? ********** \n");
        printf("x. sauvegarder\n");
        printf("r. recommencer\n");
        printf("c. Choisir la carte\n");
        printf("q. Quitter\n");
    }
    scanf(" %c", &c);
    purge();
    return c;
}

/*enregistre dans un fichier save.txt le nom de la carte, les données de serpent, et les données de bonus*/
void save(Snake *snake, Bonus *bonus, char *name_map) { 
    FILE *f = fopen("sauvegarde/save.txt", "w");
    if (!f) { printf("Erreur ouverture save.txt\n"); return; } 
    fprintf(f, "%s\n", name_map); 
    fprintf(f, "%d\n", snake->score); 
    fprintf(f, "%d\n", snake->size);
    Noeud *nb = snake->body->sentNext->suiv;//
    while (nb->cont.c != 0) {
        fprintf(f, " %c ", nb->cont.c);
        nb = nb->suiv;
    }
    fprintf(f, "\n"); 
    Noeud *nx = snake->x->sentNext->suiv;
    while (nx->cont.i != 0) {
        fprintf(f, "%d ", nx->cont.i);
        nx = nx->suiv;
    }
    fprintf(f, "\n");
    Noeud *ny = snake->y->sentNext->suiv;
    while (ny->cont.i != 0) {
        fprintf(f, "%d ", ny->cont.i);
        ny = ny->suiv;
    }
    fprintf(f, "\n");

    fprintf(f, "%d %d %d\n", bonus->x, bonus->y, bonus->footsteps);
 
    fclose(f);
    printf(" ------------Sauvegarde effectuée--------------- \n");
}


//il recupere les données sauvegarder dans save.txt et charge la map, le serpent, le nom du fichier, et le boonus
int load_save(Snake **snake, Bonus **bonus, Map **map, char *name_map) {
    FILE *f = fopen("sauvegarde/save.txt", "r"); 
    if (!f) return 0;
    fscanf(f, "%s", name_map);
    *map = load_map(name_map);
    int score, size;
    fscanf(f, "%d", &score);
    fscanf(f, "%d", &size);
    *snake = create_Snake();
    (*snake)->score = score;
    (*snake)->size = size;
    
    Elt b, x, y;
    for (int i = 1; i <= size; i++) {
        fscanf(f, " %c ", &b.c); 
        insert((*snake)->body, i, b);
    }
    
    for (int k = 1; k <= size; k++) {
        fscanf(f, "%d", &x.i);
        insert((*snake)->x ,k, x);
    }

    for (int j = 1; j <= size; j++) {
        fscanf(f, "%d", &y.i);
        insert((*snake)->y, j, y);
    }

    int bx, by, footsteps;
    fscanf(f, "%d %d %d", &bx, &by, &footsteps);

    *bonus = create_Bonus(*map, *snake);
    (*bonus)->x = bx;
    (*bonus)->y = by;
    (*bonus)->footsteps = footsteps;

    fclose(f); 
    return 1;
}