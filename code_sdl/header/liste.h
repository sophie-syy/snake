#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "noeud.h"

typedef struct _liste{
    Noeud *sentAvt;
    Noeud *sentArr;
} Liste;

Liste* listeVide();

void libererListe(Liste* l);

int estListeVide(Liste* l);

Noeud* iemeNoeud(Liste* l, int i);

Elt iemeElt(Liste* l, int i);

void inserer(Liste *l, int i, Elt e);

void supprimer(Liste *l, int i);

void afficherListe(Liste *l, int nature);

int longueur(Liste *l);

#endif 
