// Pour Liste et manipulations

/* ===== MENU PRINCIPAL ===== */


/* ===== MENU JEU ===== */
char menu_jeu(void) {
    char c;
    printf("Direction (k o l m), quitter(q) : ");
    scanf("%c", &c);
    getchar();
    return c;
}

/* ===== SAUVEGARDE ===== */
void sauvegarder(Snake *snake, Bonus *bonus, char *nom_map) {
    FILE *f = fopen("sauvegarde/save.txt", "w");
    if (!f) { printf("Erreur ouverture save.txt\n"); return; }

    fprintf(f, "%s\n", nom_map);
    fprintf(f, "%d\n", snake->score);
    fprintf(f, "%d\n", snake->size);

    // Sauvegarde des segments
    Noeud *nb = snake->body->sentAvt->suiv;
    while (nb != snake->body->sentArr) {
        fprintf(f, "%c ", nb->cont);
        nb = nb->suiv;
    }
    fprintf(f, "\n");

    Noeud *nx = snake->x->sentAvt->suiv;
    while (nx != snake->x->sentArr) {
        fprintf(f, "%d ", nx->cont);
        nx = nx->suiv;
    }
    fprintf(f, "\n");

    Noeud *ny = snake->y->sentAvt->suiv;
    while (ny != snake->y->sentArr) {
        fprintf(f, "%d ", ny->cont);
        ny = ny->suiv;
    }
    fprintf(f, "\n");

    // Sauvegarde du bonus
    fprintf(f, "%d %d %d\n", bonus->x, bonus->y, bonus->pas);

    fclose(f);
    printf("Sauvegarde effectuée dans save.txt\n");
}

/* ===== CHARGEMENT ===== */
int charger(Snake *snake, Bonus *bonus, Map *map, char *nom_map) {
    FILE *f = fopen("sauvegarde/save.txt", "r");
    if (!f) return 0;

    // Nom de la map
    fscanf(f, "%s", nom_map);
    map = load_map(nom_map);
    if (!map) { fclose(f); return 0; }

    // Score et taille
    int score, taille;
    if (fscanf(f, "%d %d", &score, &taille) != 2) { fclose(f); return 0; }

    snake = create_Snake();
    snake->score = score;
    snake->size = 0;

    snake->x = listeVide();
    snake->y = listeVide();

    // Ajouter les segments
    Noeud *lastX = (*snake)->x->sentAvt;
    Noeud *lastY = (*snake)->y->sentAvt;

    for (int i = 0; i < taille; i++) {
        int xi, yi;
        if (fscanf(f, "%d %d", &xi, &yi) != 2) { fclose(f); return 0; }

        Noeud *nx = creerNoeud(xi, (*snake)->x->sentArr);
        Noeud *ny = creerNoeud(yi, (*snake)->y->sentArr);

        lastX->suiv = nx; lastX = nx;
        lastY->suiv = ny; lastY = ny;

        (*snake)->size++;
    }
    lastX->suiv = (*snake)->x->sentArr;
    lastY->suiv = (*snake)->y->sentArr;

    // Charger le bonus
    int bx, by, pas;
    if (fscanf(f, "%d %d %d", &bx, &by, &pas) != 3) { fclose(f); return 0; }

    *bonus = create_Bonus(*map, *snake);
    (*bonus)->x = bx;
    (*bonus)->y = by;
    (*bonus)->pas = pas;

    fclose(f);
    return 1;
}

