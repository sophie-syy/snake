#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "noeud.h" //pour utiliser noeud et ses fonctions et autre bibliothèque incluse dans noeud.h

//structure de liste: noeud l'avant et noeud l'arrière
typedef struct _liste{
    Noeud *sentNext;
    Noeud *sentBack;
} Liste;

Liste* create_Liste(); /*créer une liste [0, 0]*/

void freeListe(Liste* l); /*libèrer la liste*/

Noeud* ithNoeud(Liste* l, int i);/*chercher l'ième noeud*/

Elt ithElt(Liste* l, int i);/*chercher le contenu l'ième noeud*/

void insert(Liste *l, int i, Elt e);/*inserer dans l'ième place un noeud*/

void delete(Liste *l, int i);/*suprimer l'ième noeud*/


#endif 
