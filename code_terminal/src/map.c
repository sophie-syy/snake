#include "map.h"

// Lire le fichier de "carte.txt" et remplie la matrice de la carte et ses tailles 
Map *load_map(const char *filename) {
    char fullpath[50]; // Tableau pour mettre le chemin des "fichiers .txt"
    snprintf(fullpath, sizeof(fullpath),"sauvegarde/%s", filename); // Mettre dans le tableau le dossier, et le nom du fichier donnée
    FILE *file = fopen(fullpath, "r"); // Ouverir le fichier en seule lecture
    
    // Teste d'erreur d'ouverture
    if (file == NULL) {
        perror("Erreur d'ouverture de carte.txt");
    }
    // Réserver(alloue) une place de taille de carte
    Map *map = malloc(sizeof(Map));
    // Initialisation des données de la carte
    map->data = NULL;
    map->width = 0;
    map->height = 0;

    // Tableau pour mettre les caractères lue
    char buffer[1024];

    // tant qu'il peut lire, il lit la ligne entier
    while (fgets(buffer, sizeof(buffer), file)) {
        int len = strlen(buffer); // La taille des caractères lue d'une ligne, donc c'est la longueur

        // Si le dernier caractère lue est à la ligne, change en \0 (fin sans saute de ligne)
        if (buffer[len - 1] == '\n')  
            buffer[len - 1] = '\0';

        // Mettre à jour la hauteur de la carte
        if (map->width == 0)
            map->width = strlen(buffer); 

        // Prendre une place déjà créer pour une matrice
        map->data = realloc(map->data, sizeof(char *) * (map->height + 1));
        // Réserver de la mémoire de la taille de la matrice
        map->data[map->height] = malloc(map->width + 1);
        // Stocker les caractères de la carte
        strcpy(map->data[map->height], buffer);
        
        map->height++; // Augmenter la hauteur si on peut toujour lire
    }

    // Fermer le fichier ouvert
    fclose(file);
    return map;
}

// Libérer la mémoire de la carte
void free_map(Map *map) {
    // Parcourir selon la hauteur 
    for (int i = 0; i < map->height; i++) {
        free(map->data[i]); // Libérer le tableau de hauteur i
    }
    free(map->data); // Libérer le tableau de hauteur
    free(map); // Libérer le pointeur de la carte
}

// Affichier la carte
void print_map(Map *map) {
    // Parcourir le tableau par hauteur
    for (int i = 0; i < map->height; i++) {
        printf("%s\n", map->data[i]); // Afficher le tableau de hauteur i
    }
}
