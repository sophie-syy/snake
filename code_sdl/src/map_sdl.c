#include <SDL2/SDL.h>
#include <stdio.h>

#define TILE_SIZE 32
#define MAP_W 8
#define MAP_H 8

int map[MAP_H][MAP_W] = {
    {1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1}
};

int main(void)
{
    SDL_Init(SDL_INIT_VIDEO);

    //init
    SDL_Window *window = SDL_CreateWindow(
        "Map SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        MAP_W * TILE_SIZE,
        MAP_H * TILE_SIZE,
        0
    );

    //créé une feuille
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    int running = 1;

    //sauvegarde tableau
    SDL_Event event;

    //commence du jeu
    while (running)
    {
        //SDL_PollEvent 1er event
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) //sortir, x du fenetre
                running = 0;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //init la couleur noir
        SDL_RenderClear(renderer); //coloré

        for (int y = 0; y < MAP_H; y++)
        {
            for (int x = 0; x < MAP_W; x++)
            {
                //créé un SDL_Rect de nature: x, y, largeur, hauteur
                SDL_Rect tile = {
                    x * TILE_SIZE,
                    y * TILE_SIZE,
                    TILE_SIZE,
                    TILE_SIZE
                };
                
                if (map[y][x] == 1)
                    SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // init les mur: gris clair
                else
                    SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);   // int le sol: gris foncé

                SDL_RenderFillRect(renderer, &tile); //coloré le carré de la place x, y
            }
        }

        SDL_RenderPresent(renderer); //mettre a jour sur la fénetre
        SDL_Delay(16); //att 16ms 
    }

    //free
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}