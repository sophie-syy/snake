#include <stdio.h>
#include <stdlib.h>

Liste* listeVide(){
	Liste* l = malloc(sizeof(Liste));
	l->sentAvt = creerSent();
	l->sentArr = creerSent();
	changerSuiv(l->sentAvt, l->sentArr);
	return l;
}

void libererListe(Liste* l){
	Noeud *n = l->sentAvt;
	while(n != NULL){
		l->sentAvt = n->suiv;
		libererNoeud(n);
		n = l->sentAvt;
	}
	free(l);
}

int estListeVide(Liste* l){
	return (suivant(l->sentAvt) == l->sentAvt;
}

Noeud* iemeNoeud(Liste* l, int i){
	//si dehors de la liste, retourne sentArr
	Noeud *res = l->sentAvt; 
	int j = 0;
	while (aSuivant(res) && j < i){
		res = res->suiv;
		j++;
	}
	return res;
}

Elt iemeElt(Liste* l, int i){
	return valeur(iemeNoeud(l, i));
}

void inserer(Liste *l, int i, Elt e){
	Noeud * pre = iemeNoeud(l, i-1);
	Noeud *n = creerNoeud(e, suivant(pre));
	changerSuiv(pre, n);
	
}

void supprimer(Liste *l, int i){
	Noeud *a = iemeNoeud(l, i-1);
	Noeud *s = suivant(a);
	changerSuiv(a, suivant(s));
	libererNoeud(s);
}

void afficherListe(Liste *l){
	Noeud *n = l->sentAvt; 
	printf("[ ";
	while (aSuivant(n)){
		n = suivant(n);
		printf("%d ", valeur(n));
	}
	printf("]";
}

int longueur(Liste *l){
	int t=0;
	Noeud *n = l->sentAvt; 
	while (aSuivant(n)){
		n = suivant(n);
		t++;
	}
	return t;
}

