#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"

#define TILE_SIZE 32


int main(void) {
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char nom_map[100] = "carte.txt";

    Uint32 last_input_time = 0;    // tempo de la manipulation
    Uint32 last_snake_time = 0;    // tempo de la mise a jour de serpent
    char next_direction = '\0';    // prochain touche
    char current_direction = '\0';  // touche executer

    //initialisation
    map = load_map(nom_map);
    snake = create_Snake();
    init_snake(snake);
    bonus = init_Bonus(snake, map);

    //initialisation sdl
    SDL_Init(SDL_INIT_VIDEO);

    //initialisation de la taille du jeu
    SDL_Window *window = SDL_CreateWindow(
        "Map SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        map->width * TILE_SIZE,
        map->height * TILE_SIZE,
        0
    );

    //créer la fenêtre du jeu
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event; //evenement sdl (ce que le joueur fait)
    
    int fin = 0;

    while (!fin) {
        //mettre à jour le serpent et bonus sur la map
        write_bonus(map, bonus);
        write_snake(map, snake);



        //les touches et le croix pour sortir de la page(SDL_QUIT)
        if (SDL_PollEvent(&event)){
            switch (event.type){
            case SDL_QUIT:
                fin = 1;
                break;
            
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_q:
                        fin = 1;
                        break;
                    
                    case SDLK_o:
                        next_direction = 'o';
                        break;

                    case SDLK_l:
                        next_direction = 'l';
                        break;

                    case SDLK_k:
                        next_direction = 'k';
                        break;

                    case SDLK_m:
                        next_direction = 'm';
                        break;
                }
            }  
        }

        // chaque 50ms charge le jeu
        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_input_time >= 50) {
            last_input_time = current_time;
            
            // mettre a jour la touche 
            if (next_direction != '\0') {
                current_direction = next_direction;
                next_direction = '\0';  // initialisation next_direction
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //initialiser font noir
        SDL_RenderClear(renderer); //coloré

        //colorer la map
        for (int y = 0; y < map->height; y++){
                for (int x = 0; x < map->width; x++){
                    SDL_Rect tile = {
                        x * TILE_SIZE,
                        y * TILE_SIZE,
                        TILE_SIZE,
                        TILE_SIZE
                    };
                        
                    if (map->data[y][x] == '#'){
                            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // mur
                    }else if (belongs_lettrer(map->data[y][x])){
                        if(bonus->y ==y && bonus->x == x){
                            SDL_SetRenderDrawColor(renderer, 200, 50, 50, 255); // bonus 
                        }else{
                            SDL_SetRenderDrawColor(renderer, 0, 120, 0, 255); // snake
                        }
                    }else{
                        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // vide
                    }
                    SDL_RenderFillRect(renderer, &tile);
            }
        }
        SDL_RenderPresent(renderer); 

        //chaque 300ms charger la map
        if (current_time - last_snake_time >= 300) {
            last_snake_time = current_time;
            

            fin = mouvement_snake(snake, current_direction, map, bonus);

            bonus = delete_bonus(map, bonus, snake);
            if (!fin) bonus->footsteps++;
                
                
            // initialisation de la map
            free_map(map);
            map = load_map(nom_map);
        }
    
    }

    printf("Perdu ! Score final : %d\n", snake->score);

    //liberer tout
    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
