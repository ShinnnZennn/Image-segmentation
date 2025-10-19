#include "construire_graphe.h"
#include "recup_img.h"
#include "segmentation.h"
#include "reconstruction_image.h"
#include "afficher_image.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <input_image> <output_directory>\n", argv[0]);
        return 1;
    }

    const char *input_image = argv[1];
    const char *output_directory = argv[2];

    // Exemple de traitement d'une image
    char input_image_path[256];
    snprintf(input_image_path, sizeof(input_image_path), "%s", input_image);
    printf("Chemin de l'image d'entrée : %s\n", input_image_path);

    int largeur, hauteur;
    Pixel **image = recup_img(input_image_path, &largeur, &hauteur);
    if (image == NULL) {
        printf("Erreur : impossible de charger l'image %s\n", input_image_path);
        return 1;
    }

    printf("Dimensions de l'image : %d x %d\n", largeur, hauteur);

    // Vérifiez les données de l'image chargée
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            printf("Pixel [%d, %d] - R: %d, G: %d, B: %d\n", i, j, image[i][j].r, image[i][j].g, image[i][j].b);
        }
    }

    Graphe g = creerGraphe(image, largeur, hauteur);
    printf("Graphe créé\n");

    g = segmenter(g, image, largeur, hauteur);
    printf("Graphe segmenté\n");

    // Vérifiez les données de l'image segmentée
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            printf("Pixel [%d, %d] - R: %d, G: %d, B: %d\n", i, j, image[i][j].r, image[i][j].g, image[i][j].b);
        }
    }

    char output_image_path[256];
    snprintf(output_image_path, sizeof(output_image_path), "%s/segment.jpg", output_directory);
    printf("Chemin du fichier de sortie : %s\n", output_image_path);

    reconstruction_image(output_image_path, image, largeur, hauteur);
    printf("Image reconstruite\n");

    // Optionally, display the image if you have a function for that
    // afficherImage(output_image_path, image, largeur, hauteur);
    // printf("Image affichée\n");

    // Free the allocated memory for the image and the graph
    libererImage(image, hauteur);
    libererGraphe(g);
    printf("Mémoire libérée\n");

    return 0;
}