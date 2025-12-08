#ifndef NOEUD_H_INCLUDED
#define NOEUD_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

typedef int Elt;

typedef struct noeud Noeud;

struct noeud{
    Elt cont;
    int sent;
    Noeud *suiv;
};

Noeud* creerNoeud(Elt e, Noeud* n);

void libererNoeud(Noeud* n);

Noeud* creerSent();

int estSent(Noeud * n);

int aSuivant(Noeud* n);

Noeud* suivant(Noeud* n);

Elt contenu(Noeud *n);

void changerCont(Noeud* n, Elt e);

void changerSuiv(Noeud * n, Noeud * p);

#endif
