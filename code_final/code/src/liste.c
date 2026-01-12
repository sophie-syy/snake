#include "liste.h"

/*créer une liste [0, 0]*/
Liste* create_Liste(){
    Liste *l = malloc(sizeof(Liste));
    //créer les sentinelles
    l->sentNext = create_Sent();
    l->sentBack = create_Sent();
    //relier le sentinelle avant et le dernier
    changeNext(l->sentNext, l->sentBack);
    return l;
}

/*libèrer la liste, libérer chaque noeud de la liste puis la liste,
 pour pas perdre les noeuds avant*/
void freeListe(Liste* l){
    //première noeud
    Noeud *n = l->sentNext;
    //tant qu'il y a un noeud, libére, et passe au suivant
    while(n != NULL){
        l->sentNext = n->suiv;//pour pas perdre le noeud suivant
        freeNoeud( n );
        n = l->sentNext;
    }
    free(l);
}

/*chercher l'ième noeud*/
Noeud* ithNoeud(Liste* l, int i){
    int j = 0;
    Noeud* res;
    res = l->sentNext;

    //chercher tant que il y a un noeud et au ième
    while(res != NULL && j < i){ 
        res = res->suiv;
        j++;
    }
    return res;
}

/*chercher le contenu l'ième noeud*/
Elt ithElt(Liste* l, int i){
    return (content(ithNoeud(l, i)));
}

/*inserer dans l'ième place un noeud*/
void insert(Liste *l, int i, Elt e){
    Noeud* prec = ithNoeud(l,i-1); //noeud précédent
    // créer et accrocher le noeud au précédent
    Noeud *n = create_Noeud(e, next(prec)); 
    changeNext(prec, n);
}

/*suprimer l'ième noeud*/
void delete(Liste *l, int i){
    if (l == NULL) {exit(EXIT_FAILURE);}//teste de vide

    Noeud* prec = ithNoeud(l,i-1);//noeud précédent
    Noeud *n = next(prec);//noeud suivant
    changeNext(prec,next(n)); //accrocher le noeud suivant au précédent 
    freeNoeud( n );//libérer
}
