#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "snake.h"
#include "spawn.h"


char tab[] = {'a', 'b', 'c', 'd', 'e',
              'f', 'g', 'h', 'i', 'j', 
              'k', 'l', 'm', 'n', 'o',
              'p', 'q', 'r', 's', 't',
              'u', 'v', 'w', 'x', 'y',
              'z'};

         
Bonus* create_Bonus(Map *map, Snake * snake){
    srand((unsigned)time(NULL));

    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 26];
    bonus->x = 1 + rand() % (map->width-2);
    bonus->y = 1 + rand() % (map->height-2);
    bonus->pas = 0;
    return bonus;
    
}

Bonus * init_Bonus(Snake * snake, Bonus *bonus, Map *map){
  while(appartient_snake(snake, bonus->x, bonus->y)) {
    freeBonus(bonus);
    bonus = create_Bonus(map, snake);
  }
  return bonus;
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
        bonus = init_Bonus(snake, create_Bonus(map, snake), map);
    }
    return bonus;
}

bool appartient_lettre(char variable){
  int i=0, v = 0;
  while(i<26 && v == 0){
    if(variable == tab[i]){
      v = 1;
    }else{
      i++;
    }
  }
  return i < 26;
}

bool est_Bonus(char variable, int x, int y, Bonus *bonus){
    if(bonus->letter == variable && y == bonus->y && bonus->x == x){
        return true;
    }else{
        return false;
    }
}