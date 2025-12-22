#include <stdio.h>
#include "snake.h"
#include "spawn.h"

Snake* creeSnake(){
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

void init(Snake *snake){
  snake->size = 1;
  snake->score = 0;
  inserer(snake->body, 0, "z");
  inserer(snake->x, 0, 1);
  inserer(snake->y, 0, 1);
  
}

void eat_insert(Snake *snake, Bonus* c){
  snake->size += 1;
  snake->score += 1;
  inserer(snake->body, 0, c->letter);
  inserer(snake->x, 0, c->x);
  inserer(snake->y, 0, c->y);
}

bool belongs_to_snake(Snake* snake, Bonus* c){
  Noeud *actuel_x = snake->x->sentAvt;
  Noeud *actuel_y = snake->y->sentAvt;
  while (actuel_x != NULL){
    if(actuel_x == c->x && actuel_y == c->y){
        return True;
    }
    actuel_x = actuel_x->suiv;
    actuel_y = actuel_x->suiv;
  }
  return False;
}

void mouvement_snake(Snake *snake, char button){
  switch(button){
    case 'o':
      snake->x
      break;
    case 'k':
      break;
    case 'm':
      break;
    case 'l':
      break;
    case 'q':
      break;
    default:
      break;
  }
}

void what_is_case(const Map *map, int x, int y){

}


