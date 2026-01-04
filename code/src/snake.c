#include <stdio.h>
#include "snake.h"


Snake* create_Snake(){
  Snake *snake = malloc(sizeof(Snake));
  snake->size = 0;
  
  snake->body = malloc(sizeof(Liste));
  snake->body->sentAvt = creerSent();
  snake->body->sentArr = creerSent();
  changerSuiv(snake->body->sentAvt, snake->body->sentArr);
  
  snake->x = malloc(sizeof(Liste));
  snake->x->sentAvt = creerSent();
  snake->x->sentArr = creerSent();
  changerSuiv(snake->x->sentAvt, snake->x->sentArr);
  
  snake->y = malloc(sizeof(Liste));
  snake->y->sentAvt = creerSent();
  snake->y->sentArr = creerSent();
  changerSuiv(snake->y->sentAvt, snake->y->sentArr);
  
  return snake;
}


void freeSnake(Snake *snake){
  libererListe(snake->body);
  libererListe(snake->x);
  libererListe(snake->y);
  free(snake);
}


void init(Snake *snake){
  snake->size = 1;
  snake->score = 0;
  inserer(snake->body, 0, 'z');
  inserer(snake->x, 0, 1);
  inserer(snake->y, 0, 1);
  
}


void write_snake(Map *map, Snake *snake){
    int x, y, i;
    char body_char, current_char;

    if (map == NULL || map->data == NULL || snake == NULL) return;
    
    for(i = 0; i < snake->size + 1; i++){
        x = iemeElt(snake->x, i);
        y = iemeElt(snake->y, i);
        body_char = iemeElt(snake->body, i);
        
        if (y >= 0 && y < map->height && x >= 0 && x < map->width) {
            current_char = map->data[y][x];

            if(current_char != '#'){
                map->data[y][x] = body_char;
            }
        }
    }
}

void suprime_queue(Snake *snake){
  supprimer(snake->x, snake->size+1);
  supprimer(snake->y, snake->size+1);
}

bool estBonus(Bonus *bonus, int x, int y){
  if(bonus->x == x && bonus->y == y){
    return true;
  }else{
    return false;
  }
}

void eat_insert(Snake *snake, Bonus* bonus, Map *map){
 /* int s_x = iemeElt(snake->x, 1);
  int s_y = iemeElt(snake->y, 1);
  int b_x = bonus->x;
  int b_y = bonus->y;

  if(s_x == b_x && s_y == b_y ){

    printf("eat\n");*/
    snake->size += 1;
    snake->score += 1;
    inserer(snake->body, 0, bonus->letter);
    inserer(snake->x, 0, bonus->x);
    inserer(snake->y, 0, bonus->y);
    //bonus->pas = 10; 
    /*return true;
  }else{
    return false;
  }*/
}


int case_suivant(Map *map, int x, int y, Bonus *bonus, Snake *snake){
  char valeur = map->data[y][x];
  if(estBonus(bonus, x, y)){
    eat_insert(snake, bonus, map);
    return 2; 
  }else if(valeur == ' '){
    return 1;
  }else{
    return 0;
  }
}

int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus){
  int resultat, mouvement;
  int x_elt = iemeElt(snake->x, 1);
  int y_elt = iemeElt(snake->y, 1);

  switch(button){
    case 'o':
      resultat = 0;
      mouvement = case_suivant(map, x_elt, y_elt-1, bonus, snake);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt-1);
        suprime_queue(snake);
      }else if(mouvement == 2){
        bonus->pas = 10; 
      }else{
        resultat = 1;
      }
      break;

    case 'k':
      resultat = 0;
      mouvement = case_suivant(map, x_elt-1, y_elt, bonus, snake);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt-1);
        inserer(snake->y, 0, y_elt);
        suprime_queue(snake);
      }else if(mouvement == 2){
        bonus->pas = 10; 
      }else{
        resultat = 1;
      }
      break;

    case 'm':
      resultat = 0;
      mouvement = case_suivant(map, x_elt+1, y_elt, bonus, snake);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt+1);
        inserer(snake->y, 0,y_elt);
        suprime_queue(snake);
      }else if(mouvement == 2){
        bonus->pas = 10; 
      }else{
        resultat = 1;
      }
      break;

    case 'l':
      resultat = 0;
      mouvement = case_suivant(map, x_elt, y_elt+1, bonus, snake);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt+1);
        suprime_queue(snake);
      }else if(mouvement == 2){
        bonus->pas = 10; 
      }else{
        resultat = 1;
      }
      break;
      
    case 'q':
      resultat = 1;
      break;

    default:
      resultat = 3;
      break;
  }
  printf("mouvement %d\n", mouvement);
  return resultat;
}


/*
#################################################
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#                                               #
#################################################
*/



