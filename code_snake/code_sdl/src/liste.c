#include "liste.h"

/* Créer une liste [0, 0], et retourne la liste*/
Liste* create_Liste(){
    Liste *l = malloc(sizeof(Liste)); 
    l->sentNext = create_Sent(); 
    l->sentBack = create_Sent(); 

    changeNext(l->sentNext, l->sentBack); 
    return l;
}

/*libèrer la liste*/
void freeListe(Liste* l){
    Noeud *n = l->sentNext;
    while(n != NULL){
        l->sentNext = n->suiv; 
        freeNoeud( n );
        n = l->sentNext;
    }
    free(l);
}

/* Chercher l'ième noeud */
Noeud* ithNoeud(Liste* l, int i){
    int j = 0; 
    Noeud* res; 
    res = l->sentNext;

    while(res != NULL && j < i){ 
        res = res->suiv;
        j++;
    }
    return res;
}

/* Chercher le contenu l'ième noeud */
Elt ithElt(Liste* l, int i){
    return (content(ithNoeud(l, i)));
}

/* Inserer dans l'ième place un noeud */
void insert(Liste *l, int i, Elt e){
    Noeud* prec = ithNoeud(l,i-1); 
    Noeud *n = create_Noeud(e, next(prec)); 
    changeNext(prec, n);
}

/* Supprimer l'ième noeud */
void delete(Liste *l, int i){
    if (l == NULL) {exit(EXIT_FAILURE);} 
    Noeud* prec = ithNoeud(l,i-1); 
    Noeud *n = next(prec); 
    changeNext(prec,next(n)); 
    freeNoeud( n ); 
}
