#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include "id3v2lib/include/id3v2lib.h"
#include "../include/header.h"

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

void listSongs(lista * canciones) {
	struct dirent *entrada;
	DIR * carpeta = opendir("../Biblioteca De Musica");
    while ((entrada = readdir(carpeta)) != NULL) {
    	char * extension = (char *)malloc(sizeof(char));
    	if (getExt(entrada->d_name, extension)) {
    		if (!strncmp(extension, "mp3", 3)) {
    			insertarGen(canciones, entrada->d_name);
    		}
    	};
    }
    closedir(carpeta);
}

void readFolders() {

}

void enterFolder() {

}

void readSong() {

}

int main() {
	char * extension = (char *)malloc(sizeof(char));
	int asd = getExt("hola.qwerty", extension);
	printf("Encontre la wea?: %d\n", asd);
	printf("Y la ext era: %s\n", extension);
}