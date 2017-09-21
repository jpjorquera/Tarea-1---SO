#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include "id3v2lib/include/id3v2lib.h"
#include "../include/header.h"

//#include "id.c"				// /* Borrar para el
//#include "estructuras.c"	//		Makefile	*/

int getExt(char * archivo, char * extension) {
	char * ext = strrchr(archivo, '.');
	if (!ext) {
		return 0;
	} 
	else {
		strcpy(extension, (ext+1));
    	return 1;
	}
}

int listSongs(lista * canciones) {
	struct dirent *entrada;
	DIR * carpeta = opendir("Biblioteca De Musica");
	if (carpeta == NULL) {
        return 0;
    }
    while ((entrada = readdir(carpeta)) != NULL) {
    	char * extension = (char *)malloc(sizeof(char));
    	if (getExt(entrada->d_name, extension)) {
    		if (!strncmp(extension, "mp3", 3)) {
    			insertarGen(canciones, entrada->d_name);
    		}
    	};
    }
    closedir(carpeta);
    return 1;
}

void insertSong(lista * generos, lista * canciones) {
	nodo * actual = canciones->inicial;
	unsigned int i = 0;
	char * biblioteca = "Biblioteca De Musica/";
	printf("fuera insertSong de largo: %d\n", canciones->largo); // test
	while (i < canciones->largo) {
		char * cancion = actual->contenido;
		printf("contenido %s\n", cancion);
		char * path = (char *)malloc(strlen(cancion)+strlen(biblioteca)+1);
		strcpy(path, biblioteca);
		printf("path 1: %s\n", path);
		strcat(path, cancion);
		printf("path 2: %s\n", path);
		char * gen = get_genre(path);
		printf("Saque el genero %s\n", gen);
		char * art = get_artist(path);
		printf("Saque el artista %s\n", art);
		insertarGen(generos, gen);
		insertarArt(generos, gen, art);
		i++;
		if (i < canciones->largo) {
			actual = actual->sig;
		}
	}
}

void readFolders() {

}

void enterFolder() {

}

void readSong() {

}

/*int main() {
	lista * canciones = (lista *)malloc(sizeof(lista));
	listSongs(canciones);
	lista * genre = (lista *)malloc(sizeof(lista));
	insertSong(genre, canciones);
	free(canciones);
}*/