#ifndef SPAWN_H
#define SPAWN_H

#include <stdbool.h>

typedef struct _bonus {
    char letter;
    int x;
    int y;
} Bonus;

Bonus* create_Bonus(char letter, int x, int y);

void   freeBonus(Bonus *bonus);

bool  have_letter(void);     /* true si un bonus existe */

int   number_steps(void);    /* nombre de ticks/pas depuis le spawn */

void  delete_bonus(void);    /* supprime le bonus courant */

void  init_random(void);                 /* à appeler 1 fois au début (ou auto) */

bool  spawn_random_letter(char letter);  /* spawn si aucun bonus n'existe */

Bonus* get_bonus(void);                  /* accès au bonus courant (coords, lettre) */

void  step_bonus(void);                  /* incrémente le compteur si bonus actif */

#endif
