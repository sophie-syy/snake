#include "noeud.h"

/* Créer un noeud e */
Noeud* create_Noeud(Elt e, Noeud* s){
    // Réserver un place de type Noeud
    Noeud *n = malloc (sizeof(Noeud));
    // Remplir les données du noeud
    n->cont = e;
    n->sent = 0;
    n->suiv = s;
    return n;
}

/* Libèrer la mémoire de noeud */
void freeNoeud(Noeud* n){
    free(n);
}

/* Créer le sentinelle */
Noeud* create_Sent(){
    //definir l'entier 0
    Elt e = {.i = 0};
    //créer le noeud
    Noeud *n = create_Noeud(e, NULL);
    //noeud -> sentinelle
    n->sent = 1;
    return n;
}

/* Chercher le noeud suivant */
Noeud* next(Noeud* n){
    return n->suiv;
}

/* Le contenu du noeud */
Elt content(Noeud *n){
    return n->cont;
}

/* Relier 2 noeuds ensemble, l'un après l'autre */
void changeNext(Noeud * n, Noeud * p){
    n->suiv = p;
}
