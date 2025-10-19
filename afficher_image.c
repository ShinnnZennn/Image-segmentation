#include "segmentation.h"
#include "recup_img.h"
#include <stdlib.h>
#include <stdio.h>

Pixel** image_depuis_graphe(Graphe g){
    Pixel **image = (Pixel**) malloc(g.nbSommets * sizeof(Pixel*));
    for (int i = 0; i < g.nbSommets; i++) {
        image[i] = (Pixel*) malloc(sizeof(Pixel));
    }

    for (int i = 0; i < g.nbSommets; i++) {
        image[i]->r = rand() % 256;
        image[i]->g = rand() % 256;
        image[i]->b = rand() % 256;
    }

    return image;
}

void afficherImage(const char *nomFichier, Pixel **image, int largeur, int hauteur) {
    FILE *fichier = fopen(nomFichier, "wb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        exit(1);
    }

    unsigned char header[54] = {
        0x42, 0x4D, 0x36, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00
    };
    int tailleFichier = 54 + largeur * hauteur * 3;
    header[2] = tailleFichier;
    header[18] = largeur;
    header[22] = hauteur;
    fwrite(header, sizeof(unsigned char), 54, fichier);

    int padding = (largeur * 3) % 4 ? 4 - (largeur * 3) % 4 : 0;
    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            fwrite(&image[i * largeur + j]->b, sizeof(unsigned char), 1, fichier);
            fwrite(&image[i * largeur + j]->g, sizeof(unsigned char), 1, fichier);
            fwrite(&image[i * largeur + j]->r, sizeof(unsigned char), 1, fichier);
        }
        unsigned char zero = 0;
        for (int j = 0; j < padding; j++) {
            fwrite(&zero, sizeof(unsigned char), 1, fichier);
        }
    }

    fclose(fichier);
}

