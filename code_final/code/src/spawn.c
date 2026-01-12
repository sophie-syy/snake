#include <time.h> //pour utiliser time()
#include "snake.h" //pour utilisé les fonctions de serpent 
#include "spawn.h" //et bonus et autre include dans ces fichiers

//tableau d'alphabet
char tab[] = {'a', 'b', 'c', 'd', 'e',
              'f', 'g', 'h', 'i', 'j', 
              'k', 'l', 'm', 'n', 'o',
              'p', 'q', 'r', 's', 't',
              'u', 'v', 'w', 'x', 'y',
              'z'};

/*créer le bonus aléatoire*/
Bonus* create_Bonus(Map *map, Snake * snake){
    //initialise le nombre de secondes écoulées depuis l'époque
    srand(time(NULL));

    //crée un espace
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 26]; //aléatoire entre 0 et 25
    bonus->x = 1 + rand() % (map->width-2); //aléatoire entre 1 et longeur-2
    bonus->y = 1 + rand() % (map->height-2); //aléatoire entre 1 et largeur-2
    //(-2 pour pas dépacer la map et pas mette sur le bord de la map)

    bonus->footsteps = 0;//initialisation de pas
    return bonus;
}

/*initialiser le bonus, pour qu'il n'est pas sur le mur ni sur le serpent*/
Bonus * init_Bonus(Snake * snake, Bonus *bonus, Map *map){
int x = bonus->x, y = bonus->y;
    //tant que la case du bonus appartient au serpent ou au mur, libérer le bonus et recréer un autre
  while(belongs_snake(snake, x, y) || map->data[y][x] == '#') {
    freeBonus(bonus);
    bonus = create_Bonus(map, snake);
  }
  return bonus;
}

/*libèrer le bonus*/
void freeBonus(Bonus *bonus){
    free(bonus);
}

/*Ecrire le bonus sur la map*/
void write_bonus(Map *map, Bonus * bonus){
    map->data[bonus->y][bonus->x] = bonus->letter; 
}

/*suprimer le bonus*/
Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake){
    //suprime seulement si le nombre de pas égale à 10 pas, libére le bonus et crée
    if(bonus->footsteps >= 10){
        freeBonus(bonus);
        bonus = init_Bonus(snake, create_Bonus(map, snake), map);
    }
    return bonus;
}

