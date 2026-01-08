#include "noeud.h"

Noeud* creerNoeud(Elt e, Noeud* s){
    Noeud *n = malloc (sizeof(Noeud));
    if (n == NULL){
        exit(EXIT_FAILURE);
    }

    n->cont = e;
    n->sent = 0;
    n->suiv = s;
    return n;
}

void libererNoeud(Noeud* n){
    free(n);
}

Noeud* creerSent(){
    Noeud *n = creerNoeud(0, NULL);
    n->sent = 1;
    return n;
}

int estSent(Noeud * n){
    return(n->sent == 1);
}

int aSuivant(Noeud* n){
    return (n->suiv != NULL);
}

Noeud* suivant(Noeud* n){
    return n->suiv;
}

Elt contenu(Noeud *n){
    return n->cont;
}

void changerCont(Noeud* n, Elt e){
    n->cont = e;
}

void changerSuiv(Noeud * n, Noeud * nouv){
    n->suiv = nouv;
}
