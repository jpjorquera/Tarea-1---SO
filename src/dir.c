#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include "../include/header.h"

// Obtiene la extension del archivo
int getExt(char * archivo, char ** extension) {
    // Buscar punto
	char * ext = strrchr(archivo, '.');
	if (!ext) {
		return 0;
	}
    // Copiar el resto
	else {
		strcpy(extension[0], (ext+1));
    	return 1;
	}
}

// Lee el directorio para armar la lista con las canciones
int enlistSongs(lista * canciones) {
	struct dirent * entrada;
	DIR * carpeta = opendir("biblioteca");
	char * biblioteca = "./biblioteca/";
    // Intentar leer carpeta
	if (carpeta == NULL) {
        return 0;
    }
    int largo;
    // Mientras haya contenido
    while ((entrada = readdir(carpeta)) != NULL) {
        // Verificar extension
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
                else {
                    freeTag(tag, 0);
                }
                free(path);
    			// Cerrar archivo
    			fclose(archivo);
    		}
    	}
        free(extension);
    }
    closedir(carpeta);
    return 1;
}

// Crea las carpetas necesarias
void createFolders(lista * canciones) {
    char * biblioteca = "./biblioteca/";
    struct stat st = {0};
    int i, j;
    nodo * auxi = canciones->inicial;
    nodo * auxj;
    i = 0;
    // Recorrer generos
    while (i < canciones->largo) {
        int largo_str_gen = strlen(biblioteca) + strlen(auxi->contenido) + 1;
        char * path_gen = (char *)calloc(largo_str_gen, sizeof(char));
        strcpy(path_gen, biblioteca);
        strncat(path_gen, auxi->contenido, strlen(auxi->contenido));
        if (stat(path_gen, &st) == -1) {
                mkdir(path_gen, 0700);
            }
        auxj = auxi->subcontenido->inicial;
        j = 0;
        // Recorrer artistas
        while (j < auxi->subcontenido->largo) {
            int largo_str_art = largo_str_gen + strlen(auxj->contenido) + 2;
            char * path_art = (char *)calloc(largo_str_art, sizeof(char));
            strcpy(path_art, path_gen);
            strncat(path_art, "/", 1);
            strncat(path_art, auxj->contenido, strlen(auxj->contenido));
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

// Mueve las canciones a las carpetas correspondientes
void moveSongs(lista * canciones) {
    char * biblioteca = "./biblioteca/";
    struct dirent * entrada;
    DIR * carpeta = opendir("biblioteca");
    int largo;
    // Leer contenido de carpeta
    while ((entrada = readdir(carpeta)) != NULL) {
        char * extension = (char *)calloc(5, sizeof(char));
        // Verificar extension
        if (getExt(entrada->d_name, &extension)) {
            if (!strncmp(extension, "mp3", 3)) {
                mp3tag * tag_actual = (mp3tag *)calloc(1, sizeof(mp3tag));
                largo = strlen(entrada->d_name) + strlen(biblioteca) + 1;
                char * path = (char *)calloc(largo, sizeof(char));
                strcpy(path, biblioteca);
                strncat(path, entrada->d_name, strlen(entrada->d_name));
                FILE * archivo = fopen(path, "rb");
                // Obtener tag
                get_all(archivo, tag_actual);
                // Verificar id3v1
                if (verifyTag(tag_actual->tag)) {
                    int largo_dir = strlen(biblioteca) + strlen(tag_actual->genre) 
                                    + strlen(tag_actual->artist) + strlen(entrada->d_name) + 5;
                    char * new_path = (char *)calloc(largo_dir, sizeof(char));
                    strcpy(new_path, biblioteca);
                    strncat(new_path, tag_actual->genre, strlen(tag_actual->genre));
                    strncat(new_path, "/", 1);
                    strncat(new_path, tag_actual->artist, strlen(tag_actual->artist));
                    strncat(new_path, "/", 1);
                    strncat(new_path, entrada->d_name, strlen(entrada->d_name));
                    // Mover archivos
                    rename(path, new_path);
                    free(new_path);
                }
                freeTag(tag_actual, 0);
                free(path);
                fclose(archivo);
            }
        }
        free(extension);
    }
    closedir(carpeta);
}
