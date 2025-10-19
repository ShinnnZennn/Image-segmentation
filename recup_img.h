#ifndef RECUP_IMG_H
#define RECUP_IMG_H

typedef struct {
    unsigned char r, g, b;
} Pixel;

Pixel** recup_img(const char *nomFichier, int *largeur, int *hauteur);
void libererImage(Pixel **image, int hauteur);

#endif // RECUP_IMG_H