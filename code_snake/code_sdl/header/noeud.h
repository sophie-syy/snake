#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Structure de Elt qui contient: un caractère(c) et un entier(i).
typedef struct _elt{
    char c;
    int i;
}Elt;

typedef struct _noeud Noeud; 

// Structure de noeud qui contient :
struct _noeud{ 
    Elt cont; 
    int sent; 
    Noeud *suiv; 
};

Noeud* create_Noeud(Elt e, Noeud* n); 

void freeNoeud(Noeud* n);

Noeud* create_Sent();

Noeud* next(Noeud* n);

Elt content(Noeud *n);

void changeNext(Noeud * n, Noeud * p);
#endif
