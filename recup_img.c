#include <stdio.h>
#include <stdlib.h>
#include <jpeglib.h>
#include "recup_img.h"

// Fonction pour charger une image JPEG et la mettre dans une matrice
Pixel** chargerImageJPEG(const char *nomFichier, int *largeur, int *hauteur) {
    printf("Chargement de l'image : %s\n", nomFichier);
    FILE *fichier = fopen(nomFichier, "rb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        return NULL;
    }

    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    jpeg_stdio_src(&cinfo, fichier);
    jpeg_read_header(&cinfo, TRUE);
    jpeg_start_decompress(&cinfo);

    *largeur = cinfo.output_width;
    *hauteur = cinfo.output_height;
    int num_components = cinfo.output_components;

    printf("Largeur de l'image : %d pixels\n", *largeur);
    printf("Hauteur de l'image : %d pixels\n", *hauteur);

    Pixel **matrice = (Pixel**) malloc(*hauteur * sizeof(Pixel*));
    if (matrice == NULL) {
        printf("Erreur : allocation de mémoire échouée pour matrice\n");
        exit(1);
    }
    for (int i = 0; i < *hauteur; i++) {
        matrice[i] = (Pixel*) malloc(*largeur * sizeof(Pixel));
        if (matrice[i] == NULL) {
            printf("Erreur : allocation de mémoire échouée pour matrice[%d]\n", i);
            exit(1);
        }
    }

    unsigned char *row = (unsigned char *)malloc(*largeur * num_components);
    if (row == NULL) {
        printf("Erreur : allocation de mémoire échouée pour row\n");
        exit(1);
    }
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, &row, 1);
        for (int j = 0; j < *largeur; j++) {
            matrice[cinfo.output_scanline - 1][j].r = row[j * num_components];
            matrice[cinfo.output_scanline - 1][j].g = row[j * num_components + 1];
            matrice[cinfo.output_scanline - 1][j].b = row[j * num_components + 2];
        }
    }

    free(row);
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    fclose(fichier);

    return matrice;
}

// Fonction pour récupérer une image
Pixel** recup_img(const char *nomFichier, int *largeur, int *hauteur) {
    return chargerImageJPEG(nomFichier, largeur, hauteur);
}

// Fonction pour libérer la mémoire allouée pour une image
void libererImage(Pixel **image, int hauteur) {
    for (int i = 0; i < hauteur; i++) {
        free(image[i]);
    }
    free(image);
}