#ifndef LISTE_H_INCLUDED
#define LISTE_H_INCLUDED

#include "noeud.h" // Permet d'utiliser le type Noeud, Elt et les fonctions déclarées dans noeud.h


// Structure représentant une liste chaînée avec deux pointeurs "sentinelles" :
typedef struct _liste{ 
    Noeud *sentNext; // - sentNext : pointe vers le début (avant) de la liste
    Noeud *sentBack; // - sentBack : pointe vers la fin (arrière) de la liste
} Liste;

Liste* create_Liste(); /* Créer une liste [0, 0] */

void freeListe(Liste* l); /* Libère toute la mémoire associée à la liste (nœuds + structure Liste). */

Noeud* ithNoeud(Liste* l, int i); /* Renvoie un pointeur vers le nœud situé à la position i dans la liste. */

Elt ithElt(Liste* l, int i); /* Renvoie l'élément (contenu) stocké dans le nœud situé à la position i. */

void insert(Liste *l, int i, Elt e); /* Insère l'élément e à la position i dans la liste */

void delete(Liste *l, int i); /* Supprime le nœud situé à la position i */


#endif 
