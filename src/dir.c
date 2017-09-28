#include <sys/types.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../include/header.h"

int getExt(char * archivo, char ** extension) {
	char * ext = strrchr(archivo, '.');
	if (!ext) {
		return 0;
	} 
	else {
		strcpy(extension[0], (ext+1));
    	return 1;
	}
}

int enlistSongs(lista * canciones) {
	struct dirent * entrada;
	DIR * carpeta = opendir("Biblioteca De Musica");
	char * biblioteca = "./Biblioteca De Musica/";
	if (carpeta == NULL) {
        return 0;
    }
    int largo;
    while ((entrada = readdir(carpeta)) != NULL) {
    	char * extension = (char *)calloc(5, sizeof(char));
    	if (getExt(entrada->d_name, &extension)) {
    		if (!strncmp(extension, "mp3", 3)) {
    			mp3tag * tag = (mp3tag *)calloc(1, sizeof(mp3tag));
    			// Armando direccion del archivo
                largo = strlen(entrada->d_name) + strlen(biblioteca) + 1;
    			char * path = (char *)calloc(largo, sizeof(char));
				strcpy(path, biblioteca);
				strncat(path, entrada->d_name, strlen(entrada->d_name));
				// Abriendo archivo
    			FILE * archivo = fopen(path, "rb");
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

void moveSongs(lista * canciones) {
    char * biblioteca = "Biblioteca de Musica/";
    struct dirent * entrada;
    DIR * carpeta = opendir("Biblioteca De Musica");
    while ((entrada = readdir(carpeta)) != NULL) {
        char * extension = (char *)calloc(5, sizeof(char));
        if (getExt(entrada->d_name, &extension)) {
            if (!strncmp(extension, "mp3", 3)) {
                mp3tag * tag_actual = (mp3tag *)malloc(sizeof(mp3tag));
                char * path = (char *)malloc(sizeof(char)*(strlen(entrada->d_name)+strlen(biblioteca)+1));
                strcpy(path, biblioteca);
                strcat(path, entrada->d_name);
                FILE * archivo = fopen(path, "r");
                // Obtener tag
                get_all(archivo, tag_actual);
                if (verifyTag(tag_actual->tag)) {
                    int largo_dir = strlen(biblioteca) + strlen(tag_actual->genre) 
                                    + strlen(tag_actual->artist) + strlen(entrada->d_name)+ 2;
                    char * new_path = (char *)malloc(sizeof(char) * largo_dir);
                    strcpy(new_path, biblioteca);
                    strcat(new_path, tag_actual->genre);
                    strcat(new_path, "/");
                    strcat(new_path, tag_actual->artist);
                    strcat(new_path, "/");
                    strcat(new_path, entrada->d_name);
                    rename(path, new_path);
                    free(new_path);
                }
                free(path);
                free(tag_actual);
                fclose(archivo);
            }
        }
    }
}

void enterFolder() {

}

void readSong() {

}