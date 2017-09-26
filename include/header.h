#ifndef HEADER_H_
#define HEADER_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "estructuras.h"

// id
void get_genre(char * numero_genero);
void get_all(FILE * archivo, mp3tag * tag);
int verifyTag(char * id);
// dir
int getExt(char * archivo, char * extension);
int enlistSongs(lista * canciones);
void createFolders(lista * canciones);
void readSong();
#endif