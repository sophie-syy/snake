#include "snake.h"

/* Tableau de voyelle */
char vowel[] = {'a', 'e', 'i', 'o', 'u', 'y'};


/* Créer le serpent tout vide (réserver des places) */
Snake* create_Snake(){
  Snake *snake = malloc(sizeof(Snake)); 

  snake->size = 0;
  snake->body = create_Liste();
  snake->x = create_Liste();
  snake->y = create_Liste();
  snake->score = 0;
  
  return snake;
}


/*Libèrer la mémoire du serpent, d'abord ses pointeurs des 'Liste', 
puis le pointeur de 'Snake'*/
void freeSnake(Snake *snake){ 
  freeListe(snake->body);
  freeListe(snake->x);
  freeListe(snake->y);
  free(snake);
}


/* Initialiser le serpent à une taille 1, d'un corps 'z', un score 0 
et d'un coordonnée(1, 1). Il sera toujours sur le coordonnée(1, 1) */
void init_snake(Snake *snake){ 
  Elt v = {'z', 1};

  snake->size = 1;
  snake->score = 0;
  insert(snake->body, 0, v);
  insert(snake->x, 0, v);
  insert(snake->y, 0, v);
  
}

/* Écrire le serpent dans la carte */
void write_snake(Map *map, Snake *snake){
  if (map == NULL || map->data == NULL || snake == NULL) return; 

  Noeud *actuel_body = snake->body->sentNext->suiv; 
  Noeud *actuel_x = snake->x->sentNext->suiv;
  Noeud *actuel_y = snake->y->sentNext->suiv;

  while (actuel_body->cont.c != 0){ 
    map->data[actuel_y->cont.i][actuel_x->cont.i] = actuel_body->cont.c;
    actuel_x = actuel_x->suiv;
    actuel_y = actuel_y->suiv;
    actuel_body = actuel_body->suiv;
  }
}

/* Supprimer le coordonnée de la queue quand le serpend se déplace sans manger */
void delete_queue(Snake *snake){
  delete(snake->x, snake->size+1);
  delete(snake->y, snake->size+1);
}

/* Booléen pour dire si la case du coordonnée x et y de la carte est un bonus ou pas */
bool is_Bonus(Bonus *bonus, int x, int y){
  if(bonus->x == x && bonus->y == y){
    return true;
  }else{
    return false;
  }
}

/* Booléen pour dire si le bonus est une voyelle ou pas */
bool belongs_vowel(Bonus *bonus){
  int i = 0, v = 0;

  while(i < NB_VOWEL && v == 0){
    if(bonus->letter == vowel[i]){
      v = 1;
    }else{
      i++;
    }
  }
  return i < 6; 
}

/* Manger le bonus, et insert dans le serpent le bonus et ses coordonnées, et ajoute le point*/
void eat_insert(Snake *snake, Bonus* bonus, Map *map){ 
  Elt b = {.c = bonus->letter};
  Elt x = {.i = bonus->x}; 
  Elt y = {.i = bonus->y};
  snake->size += 1;
  if(belongs_vowel(bonus)){
    snake->score += 10;
  }else{
    snake->score += 5;
  }
  insert(snake->body, 0, b);
  insert(snake->x, 0, x);
  insert(snake->y, 0, y);
}

/* Booléen pour dire si la case du coordonnée x et y de la carte est le corps du serpent ou pas */
bool belongs_snake(Snake* snake, int x, int y){
  Noeud *actuel_x = snake->x->sentNext->suiv;
  Noeud *actuel_y = snake->y->sentNext->suiv;
  while (actuel_x != NULL){
    if(actuel_x->cont.i == x && actuel_y->cont.i == y){
      return true;
    }
    actuel_x = actuel_x->suiv;
    actuel_y = actuel_y->suiv;
  }
  return false;
}

//regarde la case x, y de la map, et retourne un entier selon les condition: case = bonus, case = mur ou serpent, case = vide
int case_next(Map *map, int x, int y, Bonus *bonus, Snake *snake){
  char valeur = map->data[y][x];
  if(is_Bonus(bonus, x, y)){
    eat_insert(snake, bonus, map);
    return 2; 
  }else if(belongs_snake(snake, x, y) || valeur == '#'){
    return 0;
  }else{
    return 1;
  }
}

// selon le sens(touche), il fait avancer le serpent, ou manger le bonus, ou perdre, retourne 0 pour continuer, et 1 pour fin
int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus){
  int resultat = 0, mouvement;
  Elt x_elt = ithElt(snake->x, 1);
  Elt y_elt = ithElt(snake->y, 1);

  switch(button){
    case 'o':
      mouvement = case_next(map, x_elt.i, y_elt.i-1, bonus, snake);

      if(mouvement == 1){
        y_elt.i--;
        insert(snake->x, 0, x_elt);
        insert(snake->y, 0, y_elt);
        delete_queue(snake);
      }else if(mouvement == 2){
        bonus->footsteps = 10;
      }else{
        resultat = 1;
      }
      break; 
    

    case 'k':
      mouvement = case_next(map, x_elt.i-1, y_elt.i, bonus, snake);
      if(mouvement == 1){
        x_elt.i--;
        insert(snake->x, 0, x_elt);
        insert(snake->y, 0, y_elt);
        delete_queue(snake);
      }else if(mouvement == 2){
        bonus->footsteps = 10; 
      }else{
        resultat = 1;
      }
      break;

    case 'm':
      mouvement = case_next(map, x_elt.i+1, y_elt.i, bonus, snake);

      if(mouvement == 1){
        x_elt.i++;
        insert(snake->x, 0, x_elt);
        insert(snake->y, 0,y_elt);
        delete_queue(snake);
      }else if(mouvement == 2){
        bonus->footsteps = 10; 
      }else{
        resultat = 1;
      }
      break;
    
    case 'l':
      mouvement = case_next(map, x_elt.i, y_elt.i+1, bonus, snake);

      if(mouvement == 1){
        y_elt.i++;
        insert(snake->x, 0, x_elt);
        insert(snake->y, 0, y_elt);
        delete_queue(snake);
      }else if(mouvement == 2){
        bonus->footsteps = 10; 
      }else{
        resultat = 1;
      }
      break; 
  }
  return resultat;
}





