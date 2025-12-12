#include "snake.h"

Snake* creeSnake(char c){
    Snake *snake = malloc(sizeof(Snake));
    snake->caract = c;
    snake->size = 1;
    snake->body = malloc(sizeof(Liste));
    snake->body->sentAvt = creerSent();
    snake->body->sentArr = creerSent();
    changerSuiv(snake->body->sentAvt, snake->body->sentArr);
    return snake;
}

void init_position(Snake *snake);

void mouve_snake(Snake *snake, Map *map);

void eat_insert(Snake *snake,char c);

void what_is_case(const Map *map, int x, int y);

void mouvement_snake(Snake *snake, Map *map);
