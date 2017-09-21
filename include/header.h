#ifndef HEADER_H_
#define HEADER_H_

#include "estructuras.h"
// id
char * get_artist(char * archivo);
char * get_genre(char * archivo);
void get_all(char * archivo, char * artista, char * genero);
// dir
int getExt(char * archivo, char * extension);
int listSongs(lista * canciones);
void insertSong(lista * generos, lista * canciones);
void readFolders();
void enterFolder();
void readSong();

#endif