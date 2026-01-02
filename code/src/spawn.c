#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "spawn.h"
#include "snake.h"
#include "map.h"
#ifndef MAP_EMPTY
# define MAP_EMPTY ' '
#endif

/* Etat interne : 1 seul bonus à la fois */
static Bonus *g_bonus = NULL;
static int    g_steps = 0;
static bool   g_seeded = false;

Bonus* create_Bonus(char letter, int x, int y)
{
    Bonus *bonus = malloc(sizeof(*bonus));
    if (!bonus) return NULL;
    bonus->letter = letter;
    bonus->x = x;
    bonus->y = y;
    return bonus;
}

void freeBonus(Bonus *bonus)
{
    free(bonus);
}

void init_random(void)
{
    if (!g_seeded) {
        srand((unsigned)time(NULL));
        g_seeded = true;
    }
}

bool have_letter(void)
{
    return (g_bonus != NULL);
}

int number_steps(void)
{
    return g_steps;
}

void step_bonus(void)
{
    if (g_bonus)
        g_steps++;
}

Bonus* get_bonus(void)
{
    return g_bonus;
}

void delete_bonus(void)
{
    if (g_bonus)
    {
        /* Efface la lettre sur la map (facultatif si ton moteur redessine tout) */
        map_set(g_bonus->x, g_bonus->y, MAP_EMPTY);

        freeBonus(g_bonus);
        g_bonus = NULL;
    }
    g_steps = 0;
}
/* Trouve une case vide aléatoire (avec fallback scan complet) */
static bool find_empty_cell(int *out_x, int *out_y)
{
    int w = map_width();
    int h = map_height();

    if (w <= 0 || h <= 0) return false;

    /* Tentatives aléatoires */
    int attempts = w * h * 2;
    while (attempts-- > 0)
    {
        int x = rand() % w;
        int y = rand() % h;

        if (map_get(x, y) == MAP_EMPTY && !snake_occupies(x, y))
        {
            *out_x = x;
            *out_y = y;
            return true;
        }
    }

    /* Fallback : scan complet */
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (map_get(x, y) == MAP_EMPTY && !snake_occupies(x, y))
            {
                *out_x = x;
                *out_y = y;
                return true;
            }
        }
    }
    return false;
}
/*
  Spawn une lettre (pomme) uniquement s'il n'y en a pas déjà une.
  Retourne false si impossible (pas de place ou malloc fail).
*/
bool spawn_random_letter(char letter)
{
    if (g_bonus)
        return true; /* déjà un bonus -> "1 par 1" respecté */

    init_random();

    int x, y;
    if (!find_empty_cell(&x, &y))
        return false;

    g_bonus = create_Bonus(letter, x, y);
    if (!g_bonus)
        return false;

    map_set(x, y, letter);
    g_steps = 0;
    return true;
}

