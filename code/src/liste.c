#include "liste.h"

Liste* listeVide(){
    Liste *l = malloc(sizeof(Liste));
    l->sentAvt = creerSent();
    l->sentArr = creerSent();
    changerSuiv(l->sentAvt, l->sentArr);
    return l;
}

void libererListe(Liste* l){
    Noeud *n = l->sentAvt;
    while(n != NULL){
        l->sentAvt = n->suiv;
        libererNoeud( n );
        n = l->sentAvt;
    }
    free(l);
}

int estListeVide(Liste* l){
    return (suivant(l->sentAvt) == l->sentArr);
}

Noeud* iemeNoeud(Liste* l, int i){
    int j = 0;
    Noeud* res;
    res = l->sentAvt;
    while(res != NULL && j < i){
        res = res->suiv;
        j++;
    }
    return res;
}

Elt iemeElt(Liste* l, int i){
    return (contenu(iemeNoeud(l, i)));
}


void inserer(Liste *l, int i, Elt e){
    Noeud* prec = iemeNoeud(l,i-1);
    Noeud *n = creerNoeud(e, suivant(prec));
    changerSuiv(prec,n);
}

void supprimer(Liste *l, int i){
    if (l == NULL)
    {
        exit(EXIT_FAILURE);
    }

    Noeud* prec = iemeNoeud(l,i-1);
    Noeud *n = suivant(prec);
    changerSuiv(prec,suivant( n ));
    libererNoeud( n );
}

void afficherListe(Liste *l){
    if (l == NULL){
        exit(EXIT_FAILURE);
    }
    Noeud *actuel = l->sentAvt;

    printf("[");
    while (actuel != NULL){
        printf("%d ", actuel->cont);
        actuel = actuel->suiv;
    }
    printf("]\n");
}

int longueur(Liste* l){
    int lg = 0;
    if (l == NULL){
        exit(EXIT_FAILURE);
    }
    Noeud *actuel = l->sentAvt;

    while (actuel != NULL){
        lg++;
        actuel = actuel->suiv;
    }
    return lg-2;
}
