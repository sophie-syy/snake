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
  // Teste des entrées d'une erreur: NULL (vide)
  if (map == NULL || map->data == NULL || snake == NULL) return; 

  // Des noeuds pour faire le parcours de la liste
  // ->suiv, pour ignorer le 0 du début; liste vide = [0, 0]
  Noeud *actuel_body = snake->body->sentNext->suiv; 
  Noeud *actuel_x = snake->x->sentNext->suiv;
  Noeud *actuel_y = snake->y->sentNext->suiv;

  // Parcourir une liste (x, y et body ont tous la même taille)
  // Actuel_body->cont.c != 0, pour ignorer le 0 de la fin
  while (actuel_body->cont.c != 0){ 
    // Ecrire le serpent
    map->data[actuel_y->cont.i][actuel_x->cont.i] = actuel_body->cont.c;
    
    // Mettre à jour(le suivant)
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

  /* Parcourir le tableau de voyelle*/
  while(i < NB_VOWEL && v == 0){
    /* Si c'est une voyelle, on sorte directement (v = 1), sinon on continue */
    if(bonus->letter == vowel[i]){
      v = 1;
    }else{
      i++;
    }
  }
  /* s'il a fini de parcourir sans trouver, i = 6 donc faux 
   s'il a trouvé, i est sûrement plus petit que 6, donc vraie */
  return i < 6;
}

/* Manger le bonus */
void eat_insert(Snake *snake, Bonus* bonus, Map *map){
  // Mettre en Elt pour le fonction insert
  Elt b = {.c = bonus->letter};
  Elt x = {.i = bonus->x}; 
  Elt y = {.i = bonus->y};

  // Augmenté la taille du serpent
  snake->size += 1;
  // Si c'est une voyelle, ajouté 10 points, sinon 5 points)
  if(belongs_vowel(bonus)){
    snake->score += 10;
  }else{
    snake->score += 5;
  }
  
  // Insérer dans la tête le bonus mangé
  insert(snake->body, 0, b);
  insert(snake->x, 0, x);
  insert(snake->y, 0, y);
}

/* Booléen pour dire si la case du coordonnée x et y de la carte est le corps du serpent ou pas */
bool belongs_snake(Snake* snake, int x, int y){
  // Des noeuds pour faire le parcours de la liste
  // ->suiv, pour ignorer le 0 du début; liste vide = [0, 0]
  Noeud *actuel_x = snake->x->sentNext->suiv;
  Noeud *actuel_y = snake->y->sentNext->suiv;

  // Parcourir une liste (x, y ont tous la même taille)
  // Actuel_body->cont.c != 0, pour ignorer le 0 de la fin
  while (actuel_y->cont.c != 0){
    // Si la case du coordonnée x et y est égale à ieme corps du serpent, on sorte (return)
    if(actuel_x->cont.i == x && actuel_y->cont.i == y){
      return true;
    }
    // Mettre à jour(le suivant)
    actuel_x = actuel_x->suiv;
    actuel_y = actuel_y->suiv;
  }
  // Sinon c'est faux
  return false;
}

/* Voir la case du coordonnée x et y est-il un bonus, une partie du corps du serpent, un mur ou vide
si il retourne 2, il mange: 0, il perdre: 1, vide */
int case_next(Map *map, int x, int y, Bonus *bonus, Snake *snake){
  //la case du coordonnée x et y
  char valeur = map->data[y][x];

  // Si c'est un bonus
  if(is_Bonus(bonus, x, y)){
    eat_insert(snake, bonus, map);
    return 2; 
  // Si c'est une partie du corps du serpent ou un mur
  }else if(belongs_snake(snake, x, y) || valeur == '#'){
    return 0;
  }else{
    return 1;
  }
}

/* Deplacer/manger/perdre le serpent selon la touche d'entrée(boutton) */
int mouvement_snake(Snake *snake, char button, Map *map, Bonus *bonus){
  // Resultat pour definir si le jeu continue(0) ou le jeu est perdu (1)
  int resultat = 0, mouvement;
  // Le coordonnée x et y de la tête du serpent
  Elt x_elt = ithElt(snake->x, 1);
  Elt y_elt = ithElt(snake->y, 1);

  // Selon les touches
  switch(button){
    // Avancer
    case 'o':
      // Regarder la case en haut (1 pour avancer, 2 pour manger, 1 pour perdre)
      mouvement = case_next(map, x_elt.i, y_elt.i-1, bonus, snake);

      if(mouvement == 1){
        /* Inserte x et y la case suivant au serpent pour qu'il déplace,
         et supprime le coordonée de la queue, MÊME POUR LES AUTRES TOUCHES */
        y_elt.i--;
        insert(snake->x, 0, x_elt);
        insert(snake->y, 0, y_elt);
        delete_queue(snake);
      }else if(mouvement == 2){
        bonus->footsteps = 10; // Pour que le jeu crée un nouveau bonus après l'avoir mangé
      }else{
        resultat = 1;
      }
      break; // fini définitivement
    
    // à gauche
    case 'k':
      // Regarder la case à gauche (1 pour avancer, 2 pour manger, 1 pour perdre)
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

    // à droite
    case 'm':
      // Regarder la case à droite (1 pour avancer, 2 pour manger, 1 pour perdre)
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
    
    // Reculer
    case 'l':
    // Regarder la case en bas (1 pour avancer, 2 pour manger, 1 pour perdre)
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






