#ifndef MAP_H
#define MAP_H

typedef struct {
    char **data;   
    int width;     
    int height;    
} Map;

Map *load_map(const char *filename);
void free_map(Map *map);
void print_map(Map *map);

#endif
