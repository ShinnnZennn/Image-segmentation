#include "recup_img.h"

int main() {
    const char *nomFichier = "3.bmp"; // Nom de l'image 
    int largeur, hauteur;

    
    Pixel **matrice = chargerImageBMP(nomFichier, &largeur, &hauteur);

    
    printf("Dimensions de l'image : %d x %d\n", largeur, hauteur);


    afficherMatricePixels(matrice, largeur, hauteur);


    libererMatrice(matrice, hauteur);

    return 0;
}
