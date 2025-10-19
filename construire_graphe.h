#ifndef CONSTRUIRE_GRAPHE_H
#define CONSTRUIRE_GRAPHE_H

#include "recup_img.h"

typedef struct Arete {
    int sommet;
    double poids;
    struct Arete *suivant;
} Arete;

typedef struct Graphe{
    int nbSommets;
    Arete **listesAdjacence;
} Graphe;

Graphe creerGraphe(Pixel **image, int largeur, int hauteur);
void libererGraphe(Graphe graphe);

#endif 