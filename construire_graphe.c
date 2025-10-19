#include "construire_graphe.h"
#include <math.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h> // Ajout pour les messages de débogage

Graphe creerGraphe(Pixel **image, int largeur, int hauteur) {
    Graphe graphe;
    graphe.nbSommets = largeur * hauteur;
    graphe.listesAdjacence = (Arete**) malloc(graphe.nbSommets * sizeof(Arete*));
    if (graphe.listesAdjacence == NULL) {
        printf("Erreur : allocation de mémoire échouée pour listesAdjacence\n");
        exit(1);
    }
    for (int i = 0; i < graphe.nbSommets; i++) {
        graphe.listesAdjacence[i] = NULL;
    }

    for (int y = 0; y < hauteur; y++) {
        for (int x = 0; x < largeur; x++) {
            int sommet = y * largeur + x;
            if (x < largeur - 1) {
                int voisin = y * largeur + (x + 1);
                double poids = sqrt(pow(image[y][x].r - image[y][x + 1].r, 2) +
                                    pow(image[y][x].g - image[y][x + 1].g, 2) +
                                    pow(image[y][x].b - image[y][x + 1].b, 2));
                Arete *arete1 = (Arete*) malloc(sizeof(Arete));
                if (arete1 == NULL) {
                    printf("Erreur : allocation de mémoire échouée pour arete1\n");
                    exit(1);
                }
                arete1->sommet = voisin;
                arete1->poids = poids;
                arete1->suivant = graphe.listesAdjacence[sommet];
                graphe.listesAdjacence[sommet] = arete1;

                Arete *arete2 = (Arete*) malloc(sizeof(Arete));
                if (arete2 == NULL) {
                    printf("Erreur : allocation de mémoire échouée pour arete2\n");
                    exit(1);
                }
                arete2->sommet = sommet;
                arete2->poids = poids;
                arete2->suivant = graphe.listesAdjacence[voisin];
                graphe.listesAdjacence[voisin] = arete2;
            }
            if (y < hauteur - 1) {
                int voisin = (y + 1) * largeur + x;
                double poids = sqrt(pow(image[y][x].r - image[y + 1][x].r, 2) +
                                    pow(image[y][x].g - image[y + 1][x].g, 2) +
                                    pow(image[y][x].b - image[y + 1][x].b, 2));
                Arete *arete1 = (Arete*) malloc(sizeof(Arete));
                if (arete1 == NULL) {
                    printf("Erreur : allocation de mémoire échouée pour arete1\n");
                    exit(1);
                }
                arete1->sommet = voisin;
                arete1->poids = poids;
                arete1->suivant = graphe.listesAdjacence[sommet];
                graphe.listesAdjacence[sommet] = arete1;

                Arete *arete2 = (Arete*) malloc(sizeof(Arete));
                if (arete2 == NULL) {
                    printf("Erreur : allocation de mémoire échouée pour arete2\n");
                    exit(1);
                }
                arete2->sommet = sommet;
                arete2->poids = poids;
                arete2->suivant = graphe.listesAdjacence[voisin];
                graphe.listesAdjacence[voisin] = arete2;
            }
        }
    }

    return graphe;
}

void libererGraphe(Graphe graphe) {
    for (int i = 0; i < graphe.nbSommets; i++) {
        Arete *arete = graphe.listesAdjacence[i];
        while (arete != NULL) {
            Arete *temp = arete;
            arete = arete->suivant;
            free(temp);
        }
    }
    free(graphe.listesAdjacence);
}