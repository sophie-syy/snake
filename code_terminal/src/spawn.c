#include "snake.h" // Pour utilisé les fonctions de serpent 
#include "spawn.h" // et bonus et autre include dans ces fichiers


// Tableau d'alphabet
char tab[] = {'a', 'b', 'c', 'd', 'e',
              'f', 'g', 'h', 'i', 'j', 
              'k', 'l', 'm', 'n', 'o',
              'p', 'q', 'r', 's', 't',
              'u', 'v', 'w', 'x', 'y',
              'z'};

/* Créer le bonus aléatoire */
Bonus* create_Bonus(Map *map, Snake * snake){
    // Crée un espace
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 26]; // Aléatoire entre 0 et 25
    bonus->x = 1 + rand() % (map->width-2); // Aléatoire entre 1 et longeur-2
    bonus->y = 1 + rand() % (map->height-2); // Aléatoire entre 1 et largeur-2
    // (-2 pour pas dépacer la map et pas mette sur le bord de la map)

    bonus->footsteps = 0; // Initialisation de pas
    return bonus;
}

/* Initialiser le bonus, pour qu'il n'est pas sur le mur, ni sur le serpent */
Bonus * init_Bonus(Snake * snake, Map *map){
    Bonus * bonus = create_Bonus(map, snake);
    int x = bonus->x, y = bonus->y;
    // tantque la case du bonus appartient au serpent ou au mur, recréer une autre
    while(belongs_snake(snake, x, y) || map->data[y][x] == '#') {
        freeBonus(bonus);
        bonus = create_Bonus(map, snake);
        x = bonus->x, y = bonus->y;
    }
    return bonus;
}

/* Libèrer la mémoire de bonus */
void freeBonus(Bonus *bonus){
    free(bonus);
}

/* Ecrire le bonus sur la carte */
void write_bonus(Map *map, Bonus * bonus){
    map->data[bonus->y][bonus->x] = bonus->letter; 
}

/* Supprimer le bonus */
Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake){
    // Supprimer seulement si le nombre de pas égale à 10 pas, et crée
    if(bonus->footsteps >= 10){
        freeBonus(bonus);
        bonus = init_Bonus(snake, map);
    }
    return bonus;
}

