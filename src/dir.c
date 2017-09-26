#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
	struct dirent * entrada;
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
    			char * path = (char *)malloc(sizeof(char)*(strlen(entrada->d_name)+strlen(biblioteca)+1));
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
	    			insertarArt(canciones, tag->genre, tag->artist);
                    insertarTag(canciones, tag);
    			}
    			// Cerrar archivo
    			fclose(archivo);
    		}
    	};
    }
    closedir(carpeta);
    return 1;
}

void createFolders(lista * canciones) {
    char * biblioteca = "Biblioteca de Musica/";
    struct stat st = {0};
    int i, j;
    nodo * auxi = canciones->inicial;
    nodo * auxj;
    i = 0;
    while (i < canciones->largo) {
        int largo_str_gen = strlen(biblioteca) + strlen(auxi->contenido);
        char * path_gen = (char *)malloc(sizeof(char) * largo_str_gen);
        strcpy(path_gen, biblioteca);
        strcat(path_gen, auxi->contenido);
        if (stat(path_gen, &st) == -1) {
                mkdir(path_gen, 0700);
            }
        auxj = auxi->subcontenido->inicial;
        j = 0;
        while (j < auxi->subcontenido->largo) {
            int largo_str_art = largo_str_gen + strlen(auxj->contenido) + 1;
            char * path_art = (char *)malloc(sizeof(char) * largo_str_art);
            strcpy(path_art, path_gen);
            strcat(path_art, "/");
            strcat(path_art, auxj->contenido);
            if (stat(path_art, &st) == -1) {
                mkdir(path_art, 0700);
            }
            j++;
            if (j < auxi->subcontenido->largo) {
                auxj = auxj->sig;
            }
            free(path_art);
        }
        free(path_gen);
        i++;
        if (i < canciones->largo) {
            auxi = auxi->sig;
        }
    }
}

void enterFolder() {

}

void readSong() {

}