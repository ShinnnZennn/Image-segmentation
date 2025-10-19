#include <stddef.h>
#include <stdio.h>
#include <jpeglib.h>
#include <stdlib.h>
#include "reconstruction_image.h"

void reconstruction_image(const char *nomFichier, Pixel **image, int largeur, int hauteur) {
    printf("Enregistrement de l'image : %s\n", nomFichier);
    FILE *fichier = fopen(nomFichier, "wb");
    if (fichier == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier %s\n", nomFichier);
        exit(1);
    }

    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, fichier);

    cinfo.image_width = largeur;
    cinfo.image_height = hauteur;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 75, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    JSAMPROW row_pointer[1];
    int row_stride = largeur * 3;
    unsigned char *row = (unsigned char *)malloc(row_stride);

    while (cinfo.next_scanline < cinfo.image_height) {
        for (int j = 0; j < largeur; j++) {
            row[j * 3] = image[cinfo.next_scanline][j].r;
            row[j * 3 + 1] = image[cinfo.next_scanline][j].g;
            row[j * 3 + 2] = image[cinfo.next_scanline][j].b;
        }
        row_pointer[0] = row;
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    free(row);
    jpeg_finish_compress(&cinfo);
    jpeg_destroy_compress(&cinfo);
    fclose(fichier);
    printf("Image enregistrée avec succès : %s\n", nomFichier);
}