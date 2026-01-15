#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "noeud.h" 


// Structure représentant une liste chaînée avec deux pointeurs "sentinelles" :
typedef struct _liste{ 
    Noeud *sentNext; 
    Noeud *sentBack;
} Liste;

Liste* create_Liste(); 

void freeListe(Liste* l); 

Noeud* ithNoeud(Liste* l, int i); 

Elt ithElt(Liste* l, int i); 

void insert(Liste *l, int i, Elt e); 

void delete(Liste *l, int i); 

#endif 
