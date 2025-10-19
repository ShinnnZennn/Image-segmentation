#include "segmentation.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int sommet1;
    int sommet2;
    double poids;
} AreteTriable;

int comparerAretes(const void *a, const void *b) {
    AreteTriable *areteA = (AreteTriable *)a;
    AreteTriable *areteB = (AreteTriable *)b;
    return (areteA->poids > areteB->poids) - (areteA->poids < areteB->poids);
}

int trouverComposante(int *composantes, int sommet) {
    if (composantes[sommet] == sommet) {
        return sommet;
    } else {
        composantes[sommet] = trouverComposante(composantes, composantes[sommet]);
        return composantes[sommet];
    }
}

void fusionnerComposantes(int *composantes, int sommet1, int sommet2) {
    int comp1 = trouverComposante(composantes, sommet1);
    int comp2 = trouverComposante(composantes, sommet2);
    if (comp1 != comp2) {
        composantes[comp1] = comp2;
    }
}

void colorierComposantes(Pixel **image, int largeur, int hauteur, int *composantes) {
    // Utiliser une palette de couleurs pour les composantes
    Pixel palette[] = {
        {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 0},
        {255, 0, 255}, {0, 255, 255}, {128, 0, 0}, {0, 128, 0},
        {0, 0, 128}, {128, 128, 0}, {128, 0, 128}, {0, 128, 128}
    };
    int paletteSize = sizeof(palette) / sizeof(palette[0]);

    for (int i = 0; i < hauteur; i++) {
        for (int j = 0; j < largeur; j++) {
            int comp = trouverComposante(composantes, i * largeur + j);
            Pixel color = palette[comp % paletteSize];
            image[i][j].r = color.r;
            image[i][j].g = color.g;
            image[i][j].b = color.b;
        }
    }
}

Graphe segmenter(Graphe g, Pixel **image, int largeur, int hauteur) {
    printf("Début de la segmentation\n");

    int *composantes = (int*) malloc(g.nbSommets * sizeof(int));
    if (composantes == NULL) {
        printf("Erreur : allocation de mémoire échouée pour composantes\n");
        exit(1);
    }
    for (int i = 0; i < g.nbSommets; i++) {
        composantes[i] = i;
    }

    // Collecter toutes les arêtes
    int nbAretes = 0;
    for (int i = 0; i < g.nbSommets; i++) {
        Arete *arete = g.listesAdjacence[i];
        while (arete != NULL) {
            nbAretes++;
            arete = arete->suivant;
        }
    }

    AreteTriable *aretes = (AreteTriable *) malloc(nbAretes * sizeof(AreteTriable));
    if (aretes == NULL) {
        printf("Erreur : allocation de mémoire échouée pour aretes\n");
        exit(1);
    }

    int index = 0;
    for (int i = 0; i < g.nbSommets; i++) {
        Arete *arete = g.listesAdjacence[i];
        while (arete != NULL) {
            if (i < arete->sommet) { // Pour éviter les doublons
                aretes[index].sommet1 = i;
                aretes[index].sommet2 = arete->sommet;
                aretes[index].poids = arete->poids;
                index++;
            }
            arete = arete->suivant;
        }
    }

    // Trier les arêtes par poids croissant
    qsort(aretes, nbAretes, sizeof(AreteTriable), comparerAretes);

    // Définir un seuil pour la segmentation
    double seuil = 50.0; // Vous pouvez ajuster ce seuil selon vos besoins
    printf("Seuil de segmentation : %f\n", seuil);

    // Fusionner les composantes connexes en utilisant les arêtes triées
    for (int i = 0; i < nbAretes; i++) {
        int sommet1 = aretes[i].sommet1;
        int sommet2 = aretes[i].sommet2;
        if (aretes[i].poids <= seuil) {
            fusionnerComposantes(composantes, sommet1, sommet2);
        }
    }

    // Mettre à jour les couleurs des sommets en fonction des composantes
    colorierComposantes(image, largeur, hauteur, composantes);

    free(aretes);
    free(composantes);

    printf("Fin de la segmentation\n");

    return g;
}