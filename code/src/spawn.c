#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include"spawn.h"


char tab[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
         'h', 'i', 'j', 'k', 'l', 'm', 'n', 
         'o', 'p', 'q', 'r', 's', 't', 'u',
         'v', 'w', 'x', 'y', 'z'};

         
Bonus* create_Bonus(Map *map, Snake * snake){
    srand((unsigned)time(NULL));

    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 27];
    bonus->x = 1 + rand() % map->width;
    bonus->y = 1 + rand() % map->height;
    bonus->pas = 0;
    if(check_bonus(snake, bonus)){
        create_Bonus(map, snake);
    }else{
        return bonus;
    }
    
}

bool check_bonus(Snake * snake, Bonus *bonus){
    Noeud *actuel_x = snake->x->sentAvt;
    Noeud *actuel_y = snake->y->sentAvt;

  while (actuel_x != NULL){
    if(actuel_x->cont == bonus->x && actuel_y->cont == bonus->y){
      return true;
    }
    actuel_x = actuel_x->suiv;
    actuel_y = actuel_x->suiv;
  }
  return false;
    
}

void freeBonus(Bonus *bonus){
    free(bonus);
}

void write_bonus(Map *map, Bonus * bonus){
    map->data[bonus->y][bonus->x] = bonus->letter;
}

Bonus* suprime_bonus(Map *map, Bonus *bonus, Snake * snake){
    if(bonus->pas >= 10){
        freeBonus(bonus);
        Bonus *bonus = create_Bonus(map, snake);
    }
    return bonus;
}