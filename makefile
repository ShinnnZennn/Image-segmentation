CC = gcc
CFLAGS = -Wall
LIBS = -ljpeg -lm

all: main

main: main.o construire_graphe.o recup_img.o segmentation.o reconstruction_image.o afficher_image.o
	$(CC) $(CFLAGS) main.o construire_graphe.o recup_img.o segmentation.o reconstruction_image.o afficher_image.o $(LIBS) -o main

main.o: main.c construire_graphe.h recup_img.h segmentation.h reconstruction_image.h afficher_image.h
	$(CC) $(CFLAGS) -c main.c -o main.o

construire_graphe.o: construire_graphe.c construire_graphe.h recup_img.h
	$(CC) $(CFLAGS) -c construire_graphe.c -o construire_graphe.o

recup_img.o: recup_img.c recup_img.h
	$(CC) $(CFLAGS) -c recup_img.c -o recup_img.o

segmentation.o: segmentation.c segmentation.h construire_graphe.h
	$(CC) $(CFLAGS) -c segmentation.c -o segmentation.o

reconstruction_image.o: reconstruction_image.c reconstruction_image.h
	$(CC) $(CFLAGS) -c reconstruction_image.c -o reconstruction_image.o

afficher_image.o: afficher_image.c afficher_image.h
	$(CC) $(CFLAGS) -c afficher_image.c -o afficher_image.o

images: images.zip
	unzip -o images.zip -d images

output:
	mkdir -p output

run: all images output
	./main images/ output/

clean:
	rm -f *.o main
	rm -rf images output

.PHONY: all clean run images output