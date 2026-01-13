#include "noeud.h"

/*créer un noeud e*/
Noeud* create_Noeud(Elt e, Noeud* s){
    //réserver un place de type Noeud
    Noeud *n = malloc (sizeof(Noeud));
    //remplire les données du noeud
    n->cont = e;
    n->sent = 0;
    n->suiv = s;
    return n;
}

/*libèrer le noeud*/
void freeNoeud(Noeud* n){
    free(n);
}

/*créer le sentinelle*/
Noeud* create_Sent(){
    //definir l'entier 0
    Elt e = {.i = 0};
    //créer le noeud
    Noeud *n = create_Noeud(e, NULL);
    //noeud -> sentinelle
    n->sent = 1;
    return n;
}

/*chercher le noeud suivant*/
Noeud* next(Noeud* n){
    return n->suiv;
}

/*le contenu du noeud*/
Elt content(Noeud *n){
    return n->cont;
}

/*relier 2 noeuds ensemble, l'un après l'autre*/
void changeNext(Noeud * n, Noeud * p){
    n->suiv = p;
}
