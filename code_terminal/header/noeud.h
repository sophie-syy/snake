#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

// Structure de Elt qui contient: un caractère(c) et un entier(i).
typedef struct _elt{
    char c;
    int i;
}Elt;

typedef struct _noeud Noeud; // Renommé _noeud à Noeud

// Structure de noeud qui contient :
struct _noeud{ 
    Elt cont; // - cont : donnée stockée dans le nœud
    int sent; // - sent : indique si le nœud est une sentinelle
    Noeud *suiv; // - suiv : pointeur vers le nœud suivant
};

Noeud* create_Noeud(Elt e, Noeud* n); /* Créer un noeud */

void freeNoeud(Noeud* n);/* Libèrer la mémoire d'un noeud*/

Noeud* create_Sent();/* Créer un noued sentinelle */

Noeud* next(Noeud* n);/* Renvoie le pointeur vers le nœud suivant */

Elt content(Noeud *n);/* Renvoie l'élément (la donnée) dans le nœud.*/

void changeNext(Noeud * n, Noeud * p);/* Relie deux noeuds ensemble */
// Le nœud n pointera désormais vers p comme nœud suivant.

#endif
