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

char consone[] = {'b', 'c', 'd', 'f', 'g', 
                  'h', 'j', 'k', 'l', 'm', 
                  'n', 'p', 'q', 'r', 's', 
                  't', 'v', 'w', 'x', 'z'};

char voyelle[] = {'a', 'e', 'i', 'o', 'u', 'y'};

         
Bonus* create_Bonus(Map *map, Snake * snake){
    srand((unsigned)time(NULL));

    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = tab[rand() % 26];
    bonus->x = 1 + rand() % (map->width-2);
    bonus->y = 1 + rand() % (map->height-2);
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

bool eat_insert(Snake *snake, Bonus* bonus, Map *map, char button){
  int s_x = iemeElt(snake->x, 1);
  int s_y = iemeElt(snake->y, 1);
  int b_x = bonus->x;
  int b_y = bonus->y;

  printf("%d = %d, %d = %d \n", s_x-1, b_x, s_y, b_y);
  printf("%d = %d, %d = %d \n", s_x+1, b_x, s_y, b_y);
  printf("%d = %d, %d = %d \n", s_x, b_x, s_y-1, b_y);
  printf("%d = %d, %d = %d \n", s_x, b_x, s_y+1, b_y);

  if((s_x-1 == b_x && s_y == b_y && button == 'k') || 
     (s_x == b_x && s_y-1 == b_y && button == 'o') || 
     (s_x+1 == b_x && s_y == b_y && button == 'm') || 
     (s_x == b_x && s_y+1 == b_y && button == 'l')){

    printf("eat\n");
    snake->size += 1;
    snake->score += 1;
    inserer(snake->body, 0, bonus->letter);
    inserer(snake->x, 0, bonus->x);
    inserer(snake->y, 0, bonus->y);
    return true;
  }else{
    return false;
  }
}
