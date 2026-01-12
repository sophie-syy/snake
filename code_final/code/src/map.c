#include "map.h"

//lire le fichier de carte.txt et remplie la matrisse de la map et ses tailles 
Map *load_map(const char *filename) {
    char fullpath[50]; //tableau pour mettre le chemin des fichiers .txt
    snprintf(fullpath, sizeof(fullpath),"sauvegarde/%s", filename); //mettre dans le tableau le dossier, et le nom du fichier donnée
    FILE *file = fopen(fullpath, "r"); // ouvert le fichier en seule lecture
    
    //teste erreur d'ouverture
    if (file == NULL) {
        perror("Erreur d'ouverture de carte.txt");
    }
    //réserver un place de taille Map
    Map *map = malloc(sizeof(Map));
    //initialisation des données de map
    map->data = NULL;
    map->width = 0;
    map->height = 0;

    //tableau pour mettre les caractères lue
    char buffer[1024];

    //tant qu'il peut lire, il lit la ligne entier
    while (fgets(buffer, sizeof(buffer), file)) {
        int len = strlen(buffer); //taille des caractères lue d'une ligne, donc c'est la longueur

        //si le dernier caractère lue est à la ligne, change en \0 (fin sans saute de ligne)
        if (buffer[len - 1] == '\n')  
            buffer[len - 1] = '\0';

        //mettre à jour l'hauteur de la map
        if (map->width == 0)
            map->width = strlen(buffer); 

        //prendre une place créer déja pour une matrisse
        map->data = realloc(map->data, sizeof(char *) * (map->height + 1));
        //réserver un place de tableau d'un taille d'hauteur
        map->data[map->height] = malloc(map->width + 1);
        //ecrire dans le tableau d' un numéro hauteur varié
        strcpy(map->data[map->height], buffer);
        
        map->height++;//augmenter la hauteur si on peut toujour lire
    }

    //fermer le fichier ouvert
    fclose(file);
    return map;
}

//libérer la map, d'abord chanque tableau, puis la matrisse et en fin la map 
void free_map(Map *map) {
    //parcourir selon l'hauteur
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]); //libérer le tableau d'hauteur i
    }
    free(map->data);//libérer le tableau d'hauteur
    free(map); //libérer le pointeur map
}

//affichier la map
void print_map(Map *map) {
    //parcourir le tableau par hauteur
    for (int i = 0; i < map->height; i++) {
        printf("%s\n", map->data[i]); //afficher le tableau d'hauteur i
    }
}
