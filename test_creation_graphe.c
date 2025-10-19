#include "recup_img.h"
#include "construire_graphe.h"

int main() {
    const char *nomFichier = "3.bmp";
    int largeur, hauteur;

    Pixel **image = chargerImageBMP(nomFichier, &largeur, &hauteur);

    Graphe graphe = creerGraphe(image, largeur, hauteur);

    printf("Nombre de sommets dans le graphe : %d\n", graphe.nbSommets);

    libererGraphe(graphe);
    libererMatrice(image, hauteur);

    return 0;
}