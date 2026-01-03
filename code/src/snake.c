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


int what_is_case(const Map *map, int x, int y){
  char valeur = map->data[y][x];
  if(valeur == '#'){
    return 0;
  }else if(valeur == ' '){
    return 1;
  }else{
    return 2;
  }
}

int mouvement_snake(Snake *snake, char button, Map *map){
  int resultat, mouvement;
  int x_elt = iemeElt(snake->x, 1);
  int y_elt = iemeElt(snake->y, 1);

  switch(button){
    case 'o':
      resultat = 0;
      mouvement = what_is_case(map, x_elt, y_elt-1);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt-1);
        suprime_queue(snake);
      }else if(mouvement == 2){
        inserer(snake->body, 0, map->data[x_elt][y_elt-1]); 
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt-1);
      }else{
        resultat = 1;
      }
      break;

    case 'k':
      resultat = 0;
      mouvement = what_is_case(map, x_elt-1, y_elt);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt-1);
        inserer(snake->y, 0, y_elt);
        suprime_queue(snake);
      }else if(mouvement == 2){
        inserer(snake->body, 0, map->data[x_elt-1][y_elt]); 
        inserer(snake->x, 0, x_elt-1);
        inserer(snake->y, 0, y_elt);
      }else{
        resultat = 1;
      }
      break;

    case 'm':
      resultat = 0;
      mouvement = what_is_case(map, x_elt+1, y_elt);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt+1);
        inserer(snake->y, 0,y_elt);
        suprime_queue(snake);
      }else if(mouvement == 2){
        inserer(snake->body, 0, map->data[x_elt+1][y_elt]); 
        inserer(snake->x, 0, x_elt+1);
        inserer(snake->y, 0,y_elt);
      }else{
        resultat = 1;
      }
      break;

    case 'l':
      resultat = 0;
      mouvement = what_is_case(map, x_elt, y_elt+1);

      if(mouvement == 1){
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt+1);
        suprime_queue(snake);
      }else if(mouvement == 2){
        inserer(snake->body, 0, map->data[x_elt][y_elt+1]); 
        inserer(snake->x, 0, x_elt);
        inserer(snake->y, 0, y_elt+1);
      }else{
        resultat = 1;
      }
      break;
      
    case 'q':
      resultat = 1;
      break;
    default:
      printf("Erreur de touche.\n");
      break;
  }

  return resultat;
}






