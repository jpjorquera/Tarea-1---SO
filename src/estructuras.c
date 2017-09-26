#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../include/estructuras.h"

int buscarGenero(lista * generos, char * genero) {
	nodo * actual = generos->inicial;
	unsigned int largo = generos->largo;
	unsigned int i = 0;
	while (i < largo) {
		if (strcmp(actual->contenido, genero) == 0) {
			return 1;
		}
		else {
			actual = actual->sig;
		}
		++i;
	}
	return 0;
}

int buscarArtista(lista * generos, char * genero,char * artista) {
	nodo * actual_genero = generos->inicial;
	unsigned int largo_genero = generos->largo;
	unsigned int i = 0, j = 0;
	while (i < largo_genero) {
		if (strcmp(actual_genero->contenido, genero) == 0) {
			nodo * actual_artista = actual_genero->subcontenido->inicial;
			unsigned int largo_artista = actual_genero->subcontenido->largo;
			while (j < largo_artista) {
				if (strcmp(actual_artista->contenido, artista) == 0){
					return 1;
				}
				else {
					actual_artista = actual_artista->sig;
				}
				++j;
			}
		}
		else {
			actual_genero = actual_genero->sig;
		}
		++i;
	}
	return 0;
}

void insertarGen(lista * generos, char * genero) {
	if (!buscarGenero(generos, genero)) {
		nodo * aux;
		if (generos->largo == 0){
			aux = (nodo *)malloc(sizeof(nodo));
			aux->contenido = genero;
			generos->inicial = aux;
			generos->final = aux;
			generos->largo = 1;
		}
		else {
			aux = (nodo *)malloc(sizeof(nodo));
			aux->contenido = genero;
			generos->final->sig = aux;
			generos->final = aux;
			generos->largo += 1;
		}
		aux->subcontenido = (lista *)malloc(sizeof(lista));
		aux->subcontenido->largo = 0;
	}
}

void insertarArt(lista * generos, char * genero, char * artista) {
	nodo * actual_genero = generos->inicial;
	while (strcmp(actual_genero->contenido, genero) != 0) {
		actual_genero = actual_genero->sig;
	}
	int found = buscarArtista(generos, genero, artista);
	if (!found) {
		nodo * aux = (nodo *)malloc(sizeof(nodo));
		aux->contenido =  artista;
		if (actual_genero->subcontenido->largo == 0) {
			actual_genero->subcontenido->inicial = aux;
		}
		else {
			actual_genero->subcontenido->final->sig = aux;
		}
		actual_genero->subcontenido->final = aux;
		actual_genero->subcontenido->largo++;
		aux->subcontenido = (lista *)malloc(sizeof(lista));
		aux->subcontenido->largo = 0;
	}
}

void insertarTag(lista * generos, mp3tag * tag) {
	char * genero = tag->genre;
	char * artista = tag->artist;
	nodo * actual_genero = generos->inicial;
	while (strcmp(actual_genero->contenido, genero) != 0) {
		actual_genero = actual_genero->sig;
	}
	nodo * actual_artista = actual_genero->subcontenido->inicial;
	while (strcmp(actual_artista->contenido, artista) != 0) {
		actual_artista = actual_artista->sig;
	}
	nodo * aux = (nodo *)malloc(sizeof(nodo));
	if (actual_artista->subcontenido->largo == 0) {
		actual_artista->subcontenido->inicial = aux;
	}
	else {
		actual_artista->subcontenido->final->sig = aux;
	}
	actual_artista->subcontenido->final = aux;
	actual_artista->subcontenido->largo++;
	aux->id = tag;
}

void inicializarLista(lista * lis) {
	lis->largo = 0;
}

void freeTag(mp3tag * id) {
	free(id->tag);
	free(id->song);
	free(id->artist);
	free(id->genre);
	free(id->album);
	free(id->year);
	free(id->comment);
	free(id);
}

void destroyAdy(lista * generos) {
	nodo * aux;
	nodo * aux_gen;
	lista * art = generos->inicial->subcontenido;
	while (generos->largo > 0) {
		while (art->largo > 0) {
			art->largo -= 1;
			aux = art->inicial;
			while (aux->subcontenido->largo > 0) {
				aux->subcontenido->largo--;
				nodo * tag_aux = aux->subcontenido->inicial;
				if (aux->subcontenido->largo > 0) {
					aux->subcontenido->inicial = tag_aux->sig;
				}
				freeTag(tag_aux->id);
				free(tag_aux);
			}
			free(aux->subcontenido);
			if (art->largo > 0) {
				art->inicial = art->inicial->sig;
			}
			free(aux);
		}
		generos->largo -= 1;
		aux_gen = generos->inicial;
		if (generos->largo > 0) {
			generos->inicial = generos->inicial->sig;
			art = generos->inicial->subcontenido;
		}
		free(aux_gen->subcontenido);
		free(aux_gen);
	}
	free(generos);
}