#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "map.h"
#include "snake.h"
#include "spawn.h"
#include "menu.h"

#define TILE_SIZE 32


int main(void) {
    Map *map = NULL;
    Snake *snake = NULL;
    Bonus *bonus = NULL;
    char nom_map[100] = "carte.txt";

    Uint32 last_input_time = 0;    // 上次处理输入的时间
    Uint32 last_snake_time = 0;    // 上次移动蛇的时间
    char next_direction = '\0';    // 下一个方向（缓冲）
    char current_direction = '\0';  // 当前方向（假设初始向右）



    //int choix = menu_principal(nom_map);
    map = load_map(nom_map);
    if (!map) { printf("Erreur map\n"); return 1; }

    snake = create_Snake();
    init(snake);

    bonus = create_Bonus(map, snake);
    bonus = init_Bonus(snake, bonus, map);




    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow(
        "Map SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        map->width * TILE_SIZE,
        map->height * TILE_SIZE,
        0
    );

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //int running = 1;

    SDL_Event event;


    /*if (choix == MENU_QUITTER) {
        printf("Au revoir !\n");
        return 0;
    }

    if (choix == MENU_NOUVEAU) {
        map = load_map(nom_map);
        if (!map) { printf("Erreur map\n"); return 1; }

        snake = create_Snake();
        init(snake);

        bonus = create_Bonus(map, snake);
        bonus = init_Bonus(snake, bonus, map);
    }

    if (choix == MENU_CHARGER) {
        if (!charger(&snake, &bonus, &map, nom_map)) {
            printf("Erreur chargement\n");
            return 1;
        }
    }*/
    
    int fin = 0;// choix2;

    while (!fin) {
        write_bonus(map, bonus);
        write_snake(map, snake);
        printf(" ================= carte %dx%d ================== \n", map->height, map->width);
        print_map(map);


        printf("Score : %d\n", snake->score);

        if (SDL_PollEvent(&event))
        {
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

        // 添加：每100ms更新一次方向（按键响应）
        Uint32 current_time = SDL_GetTicks();
        if (current_time - last_input_time >= 50) {
            last_input_time = current_time;
            
            // 如果有新的方向输入，更新当前方向
            if (next_direction != '\0') {
                current_direction = next_direction;
                next_direction = '\0';  // 清空缓冲
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //init la couleur noir
        SDL_RenderClear(renderer); //coloré

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
                    }else if (appartient_lettre(map->data[y][x])){
                        if(est_Bonus((map->data[y][x]), x, y, bonus)){
                            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // bonus 
                        }else{
                            SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // snake
                        }
                    }else{
                        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // vide
                    }
                    SDL_RenderFillRect(renderer, &tile);
            }
        }
        SDL_RenderPresent(renderer); 

        //c = menu_jeu(1);

        /*if (c == 'q') {
            c = menu_jeu(2);
            while(c == 'x' || c == 'c'){
                if (c == 'x') {
                    sauvegarder(snake, bonus, nom_map);
                }
                if (c == 'c') {
                    printf("\n");
                    printf(" ------------- Taille de la carte ------------- \n");
                    printf("1. carte%dx%d\n",16,9);
                    printf("2. carte%dx%d\n",27,14);
                    printf("3. carte%dx%d\n",49,18);
                    scanf("%d", &choix2);
                    getchar();

                    if(choix2 == 1){
                        strcpy(nom_map, "carte.txt");
                    }
                    if(choix2 == 2){
                        strcpy(nom_map, "carte2.txt");
                    }
                    if(choix2 == 3){
                        strcpy(nom_map, "carte3.txt");
                    }
                }
                c = menu_jeu(2);
            }
            if (c == 'r') {
                freeSnake(snake);
                freeBonus(bonus);
                free_map(map);

                map = load_map(nom_map);
                snake = create_Snake();
                init(snake);
                bonus = init_Bonus(snake, create_Bonus(map, snake), map);
            }
            if (c == 'q') {
                printf("\n");
                printf("Fin de la partie\n");
                break;
            }
        }*/

        if (current_time - last_snake_time >= 300) {
            last_snake_time = current_time;
            
            // 使用当前方向移动蛇
            if (current_direction != '\0') {
                fin = mouvement_snake(snake, current_direction, map, bonus);

                bonus = suprime_bonus(map, bonus, snake);
                if (!fin) bonus->pas++;
                
                // 重新渲染（把下面的渲染代码移到这里）
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                
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
                        }else if (appartient_lettre(map->data[y][x])){
                            if(est_Bonus((map->data[y][x]), x, y, bonus)){
                                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // bonus 
                            }else{
                                SDL_SetRenderDrawColor(renderer, 150, 150, 150, 255); // snake
                            }
                        }else{
                            SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255); // vide
                        }
                        SDL_RenderFillRect(renderer, &tile);
                    }
                }
                
                SDL_RenderPresent(renderer);
                
                // 重新加载地图
                free_map(map);
                map = load_map(nom_map);
                if (!map) { printf("Erreur map\n"); break; }
            }
        }
    
    }

    printf("Perdu ! Score final : %d\n", snake->score);

    freeSnake(snake);
    freeBonus(bonus);
    free_map(map);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
