#include "snake.h" 
#include "spawn.h" 


// Tableau d'alphabet
char tab[] = {'a', 'b', 'c', 'd', 'e',
              'f', 'g', 'h', 'i', 'j', 
              'k', 'l', 'm', 'n', 'o',
              'p', 'q', 'r', 's', 't',
              'u', 'v', 'w', 'x', 'y',
              'z'};


/* Créer le bonus aléatoire, et retourne le bonus*/
Bonus* create_Bonus(Map *map, Snake * snake){ 
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 26]; 
    bonus->x = 1 + rand() % (map->width-2); 
    bonus->y = 1 + rand() % (map->height-2); 
    bonus->footsteps = 0; 
    return bonus; 
}

/* Initialiser le bonus, pour qu'il n'est pas sur le mur, ni sur le serpent */
Bonus * init_Bonus(Snake * snake, Map *map){
    Bonus * bonus = create_Bonus(map, snake);
    int x = bonus->x, y = bonus->y;
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

/* mettre à jour le bonus sur la map */
void write_bonus(Map *map, Bonus * bonus){
    map->data[bonus->y][bonus->x] = bonus->letter; 
}

/* Supprimer le bonus et retourne un nouveau bonus*/
Bonus* delete_bonus(Map *map, Bonus *bonus, Snake * snake){
    if(bonus->footsteps >= 10){
        freeBonus(bonus);
        bonus = init_Bonus(snake, map);
    }
    return bonus;
}

/*chercher si variable appartient à l'alphabet*/
bool belongs_lettrer(char variable){
  int i=0, v = 0;
  while(i< SOMME_LETTER && v == 0){
    if(variable == tab[i]){
      v = 1;
    }else{
      i++;
    }
  }
  return i < SOMME_LETTER;
}

