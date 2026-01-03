#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "spawn.h"


char tab[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 
         'h', 'i', 'j', 'k', 'l', 'm', 'n', 
         'o', 'p', 'q', 'r', 's', 't', 'u',
         'v', 'w', 'x', 'y', 'z'};

char consone[] = {'b', 'c', 'd', 'f', 'g', 
                  'h', 'j', 'k', 'l', 'm', 
                  'n', 'p', 'q', 'r', 's', 
                  't', 'v', 'w', 'x', 'z'};

char voyelle[] = {'a', 'e', 'i', 'o', 'u', 'y'};

         
Bonus* create_Bonus(Map *map, Snake * snake){
    srand((unsigned)time(NULL));

    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 27];
    bonus->x = 1 + rand() % map->width;
    bonus->y = 1 + rand() % map->height;
    bonus->pas = 0;
    return bonus;
    
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
        bonus = create_Bonus(map, snake);
    }
    return bonus;
}

void eat_insert(Snake *snake, Bonus* bonus){
  snake->size += 1;
  snake->score += 1;
  inserer(snake->body, 0, bonus->letter);
  inserer(snake->x, 0, bonus->x);
  inserer(snake->y, 0, bonus->y);
}