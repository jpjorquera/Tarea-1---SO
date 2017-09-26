#include <sys/types.h>
#include <dirent.h>
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

int enlistSongs(lista * canciones) {
	struct dirent *entrada;
	DIR * carpeta = opendir("Biblioteca De Musica");
	char * biblioteca = "Biblioteca de Musica/";
	if (carpeta == NULL) {
        return 0;
    }
    while ((entrada = readdir(carpeta)) != NULL) {
    	char * extension = (char *)malloc(sizeof(char));
    	if (getExt(entrada->d_name, extension)) {
    		if (!strncmp(extension, "mp3", 3)) {
    			mp3tag * tag = (mp3tag *)malloc(sizeof(mp3tag));

    			// Armando direccion del archivo
    			char * path = (char *)malloc(strlen(entrada->d_name)+strlen(biblioteca)+1);
				strcpy(path, biblioteca);
				strcat(path, entrada->d_name);
				// Abriendo archivo
    			FILE * archivo = fopen(path, "r");
    			// Obtener tag
    			get_all(archivo, tag);
    			// Verificard version ID3v1
    			if (verifyTag(tag->tag)) {
                // Insertar a la lista
	    			insertarGen(canciones, tag->genre);
	    			insertarArt(canciones, tag->genre, tag);
    			}
    			// Cerrar archivo
    			fclose(archivo);
    		}
    	};
    }
    closedir(carpeta);
    return 1;
}

void readFolders() {

}

void enterFolder() {

}

void readSong() {

}