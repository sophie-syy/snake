#include "liste.h"

/* Créer une liste [0, 0] */
Liste* create_Liste(){
    Liste *l = malloc(sizeof(Liste)); // Alloue de la mémoire pour liste

    /* Créer les sentinelles */
    l->sentNext = create_Sent(); // Sentinelle avant
    l->sentBack = create_Sent(); // Sentinelle arrière

    changeNext(l->sentNext, l->sentBack); // Relier le sentinelle avant et le arrière
    return l;
}

// Libère la mémoire de la liste
/* Libére la mémoire de chaque noeud de la liste, puis de la liste pour ne pas perdre les noeuds avant */
void freeListe(Liste* l){
    // Première noeud
    Noeud *n = l->sentNext;
    // Tantque il y a un noeud, libérer et passe aux suivant
    while(n != NULL){
        l->sentNext = n->suiv; // Pour pas perdre le noeud suivant
        freeNoeud( n ); // Libérer le noeud
        n = l->sentNext;
    }
    free(l);
}

/* Chercher l'ième noeud */
Noeud* ithNoeud(Liste* l, int i){
    int j = 0; // Initialise j
    Noeud* res; 
    res = l->sentNext;

    // Chercher tant que il y a un noeud et au ième
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
    Noeud* prec = ithNoeud(l,i-1); // Noeud précédent
    // Créer et pointer le noeud aux précédent
    Noeud *n = create_Noeud(e, next(prec)); 
    changeNext(prec, n);
}

/* Supprimer l'ième noeud */
void delete(Liste *l, int i){
    if (l == NULL) {exit(EXIT_FAILURE);} // Si c'est vide, il sort et affiche une erreur 

    Noeud* prec = ithNoeud(l,i-1); // Noeud précédent
    Noeud *n = next(prec); // Noeud suivant
    changeNext(prec,next(n)); // Pointer le noeud suivant au précédent 
    freeNoeud( n ); // Libérer
}
