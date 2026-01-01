#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "spawn.h"
#include "snake.h"


Bonus* create_Bonus(char letter, int x, int y){
    Bonus *bonus = malloc(sizeof(Bonus));
    bonus->letter = letter;
    bonus->x = x;
    bonus->y = y;
    return bonus;
}

void freeBonus(Bonus *bonus){
    free(bonus);
}

/*bool have_letter(){
    
}

int number_steps(){
    
}

void delete_bonus(){
    
}*/