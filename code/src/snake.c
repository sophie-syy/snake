#include <stdio.h>
#include "snake.h"

Snake* creeSnake(char c){
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
  inserer(snake->body, 0, "x");
  inserer(snake->x, 0, 1);
  inserer(snake->y, 0, 1);
  
}

void mouvement_snake(Snake *snake, Map *map){

}

void eat_insert(Snake *snake,char c){
  snake->size += 1;
  inserer(snake->body, 0, c);
  inserer(snake->x, 0, ?);
  inserer(snake->y, 0, ?);
}

void what_is_case(const Map *map, int x, int y){

}


