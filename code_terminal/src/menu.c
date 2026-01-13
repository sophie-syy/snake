#include "menu.h"

/*vider le scanf tant qu'il a '\n' ou EOF avec getchar()*/
void purge(void){
    int c = 0;
    while ((c=getchar())!='\n' && c!= EOF);
}

/* afficher le Menu principal */
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

    //pour dire lancer le jeu: MENU_NEW
    if (choix == 1) {
        return MENU_NEW;
    }
    //pour changer le nom fichier du carte, ensuite dire lancer le jeu: MENU_NEW
    if (choix == 2) {
        printf("\n");
        printf(" ------------- Taille de la carte ------------- \n");
        printf("1. carte%dx%d\n",16,9);
        printf("2. carte%dx%d\n",27,14);
        printf("3. carte%dx%d\n",49,18);
        scanf("%d", &choix2);
        purge();

        //changer le nom du fichier selon le choix du jouer
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
    //pour dire lancer le sauvegarde:MENU_LOAD
    if (choix == 3) {
        return MENU_LOAD;
    }
    return MENU_LEAVE;
}

/* Menu pendant le jeu */
char menu_direc_leave(int position) {
    char c;
    //si c'est 1, il demande la direction, sinon il affiche le menu de quitte
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

/* Sauvegarder la partie dans save.txt */
void save(Snake *snake, Bonus *bonus, char *name_map) {
    //ouvrir le fichier qui sauvegarde les données en seul ecriture
    FILE *f = fopen("sauvegarde/save.txt", "w");
    if (!f) { printf("Erreur ouverture save.txt\n"); return; } //teste erreur d'ouverture

    //ECRIRE LES DONNÉES DANS LE FICHIER SAVE.TXT(sauvegarde dans une ordre précise pour la suite de relire)

    fprintf(f, "%s\n", name_map); //nom du fichier de niveau
    fprintf(f, "%d\n", snake->score); //le score
    fprintf(f, "%d\n", snake->size);//la taille du serpent

    // sauvegarde des segments
    //serpent
    Noeud *nb = snake->body->sentNext->suiv;//
    while (nb->cont.c != 0) {
        fprintf(f, " %c ", nb->cont.c);
        nb = nb->suiv;
    }
    fprintf(f, "\n"); //pour la beauté de lecture dans save.txt

    //coordonnée x
    Noeud *nx = snake->x->sentNext->suiv;
    while (nx->cont.i != 0) {
        fprintf(f, "%d ", nx->cont.i);
        nx = nx->suiv;
    }
    fprintf(f, "\n");

    //coordonnée y
    Noeud *ny = snake->y->sentNext->suiv;
    while (ny->cont.i != 0) {
        fprintf(f, "%d ", ny->cont.i);
        ny = ny->suiv;
    }
    fprintf(f, "\n");

    // Sauvegarde du bonus
    fprintf(f, "%d %d %d\n", bonus->x, bonus->y, bonus->footsteps);

    fclose(f);//fermer le fichier save
    printf(" ------------Sauvegarde effectuée--------------- \n");
}

/* Charger une partie depuis save.txt */
int load_save(Snake **snake, Bonus **bonus, Map **map, char *name_map) {
    //ouvert le fichier save pour lire les sauvegardes
    FILE *f = fopen("sauvegarde/save.txt", "r"); 
    //teste erreur d'ouverture
    if (!f) return 0;

    //RECUPÉRER LES DONNÉES (il lit dans une ordre précise)
    // changer le nom de fichier par la carte de sauvegarde
    fscanf(f, "%s", name_map);
    //charger la map
    *map = load_map(name_map);

    //prendre le score et taille
    int score, size;
    fscanf(f, "%d", &score);
    fscanf(f, "%d", &size);

    //créer le serpent et charger les informations
    *snake = create_Snake();
    (*snake)->score = score;
    (*snake)->size = size;

    // Ajouter au fur et à mesure les lettres du corps et ces coordonnées
    //prendre puis inserte
    Elt b, x, y;
    for (int i = 1; i <= size; i++) {
        fscanf(f, " %c ", &b.c); // un espace précise devant pour qu'il ignore les espaces a la suite
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
    
    // récupérer les informations du bonus
    int bx, by, footsteps;
    fscanf(f, "%d %d %d", &bx, &by, &footsteps);
    //créer et charger le bonus
    *bonus = create_Bonus(*map, *snake);
    (*bonus)->x = bx;
    (*bonus)->y = by;
    (*bonus)->footsteps = footsteps;

    fclose(f);//fermeture du fichier save
    return 1;
}