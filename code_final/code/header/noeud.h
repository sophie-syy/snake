#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

//structure de Elt: entier, caractère
typedef struct _elt{
    char c;
    int i;
}Elt;

//renommé _noeud a Noeud
typedef struct _noeud Noeud;

//structure de noeud: elt, contenu, et le noeud suivant 
struct _noeud{
    Elt cont;
    int sent;
    Noeud *suiv;
};

Noeud* create_Noeud(Elt e, Noeud* n); /*créer un noeud*/

void freeNoeud(Noeud* n);/*libèrer le noeud*/

Noeud* create_Sent();/*créer le sentinelle*/

Noeud* next(Noeud* n);/*chercher le noeud suivant*/

Elt content(Noeud *n);/*le contenu du noeud*/

void changeNext(Noeud * n, Noeud * p);/*relier 2 noeuds ensemble*/

#endif
