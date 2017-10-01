#ifndef HEADER_H_
#define HEADER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "estructuras.h"

// id
// Obtiene el genero en base al número correspondiente
void get_genre(char * numero_genero);
// Obtiene el tag entero id3v1
void get_all(FILE * archivo, mp3tag * tag);
// Verifica que sea id3v1
int verifyTag(char * id);
// dir
// Obtiene la extension del archivo
int getExt(char * archivo, char ** extension);
// Lee el directorio para armar la lista con las canciones
int enlistSongs(lista * canciones);
// Crea las carpetas necesarias
void createFolders(lista * canciones);
// Mueve las canciones a las carpetas correspondientes
void moveSongs(lista * canciones);

#endif