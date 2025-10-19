#include "segmentation.h"
#include "recup_img.h"
#include <stdlib.h>
#include <stdio.h>


Pixel** image_depuis_graphe(Graphe g);
void afficherImage(const char *nomFichier, Pixel **image, int largeur, int hauteur);
