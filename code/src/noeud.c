#include <stdio.h>
#include <stdlib.h>

Noeud* creerNoeud(Elt e, Noeud* n){
	Noeud* n = malloc(sizeof(Noeud));
	if(n==NULL){
		exit(EXIT_FAILURE);
	}
	n->val = e;
	n->suiv = n;
	n->sent = 0;
	return n;
}

void libererNoeud(Noeud* n){
	free(n);
}

Noeud* creerSent(){
	Noeud* n=creerNoeud(0, NULL);
	n->sent = 1;
	return n;
}

int estSent(Noeud * n){
	return (n->sent ==1);
}

int aSuivant(Noeud* n){
	return (n->suiv != NULL);
}

Noeud* suivant(Noeud* n){
	return n->suiv;
}

Elt valeur(Noeud *n){
	return n->val;
}

void changerValeur(Noeud* n, Elt e){
	n->val = e;
}

void changerSuiv(Noeud * n, Noeud * p){
	n->suiv = p;
}

