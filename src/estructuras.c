#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/estructuras.h"

int buscarGenero(lista * generos, char * genero) {
	nodo * actual = generos->inicial;
	unsigned int largo = generos->largo;
	unsigned int i = 0;
	while (i < largo) {
		if (strncmp(actual->contenido, genero, strlen(genero)) == 0) {
			return 1;
		}
		else {
			actual = actual->sig;
		}
		++i;
	}
	return 0;
}

int buscarArtista(lista * generos, char * genero, char * artista) {
	nodo * actual_genero = generos->inicial;
	unsigned int largo_genero = generos->largo;
	unsigned int i = 0, j = 0;
	while (i < largo_genero) {
		if (strncmp(actual_genero->contenido, genero, strlen(genero)) == 0) {
			nodo * actual_artista = actual_genero->subcontenido->inicial;
			unsigned int largo_artista = actual_genero->subcontenido->largo;
			while (j < largo_artista) {
				if (strncmp(actual_artista->contenido, artista, strlen(genero)) == 0){
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
		aux->subcontenido = (lista *)calloc(1, sizeof(lista));
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
		aux->subcontenido = (lista *)calloc(1, sizeof(lista));
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

void freeTag(mp3tag * id, short mode) {
	if (mode == 1) {
		free(id->artist);
		free(id->genre);
	}
	else {
		free(id->artist);
		free(id->genre);
		free(id->tag);
		free(id->song);
		free(id->album);
		free(id->year);
		free(id->comment);
		free(id);
	}
}

void destroyAdy(lista * generos, short mode) {
	nodo * aux;
	nodo * aux_gen;
	lista * art = generos->inicial->subcontenido;
	if (mode == 1){
		free(generos->str);
	}
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
				freeTag(tag_aux->id, mode);
				free(tag_aux);
			}
			if (mode == 1){
				free(aux->subcontenido->str);
			}
			free(aux->subcontenido->str);
			free(aux->subcontenido);
			if (art->largo > 0) {
				art->inicial = art->inicial->sig;
			}
			free(aux);
		}
		free(art->str);
		generos->largo -= 1;
		aux_gen = generos->inicial;
		if (generos->largo > 0) {
			generos->inicial = generos->inicial->sig;
			art = generos->inicial->subcontenido;
		}
		if (mode == 1){
			free(aux_gen->subcontenido->str);
		}
		free(aux_gen->subcontenido);
		free(aux_gen);
	}
	free(generos);
}

void destroyAdyStr(lista * generos, short mode) {
	nodo * aux;
	nodo * aux_art;
	nodo * aux_gen = generos->inicial;
	lista * art;
	while (generos->largo > 0) {
		art = aux_gen->subcontenido;
		aux_art = art->inicial;
		while (art->largo > 0) {
			aux = aux_art;
			aux_art = aux_art->sig;
			(art->largo)--;
			free(aux->contenido);
			free(aux->subcontenido);
			free(aux);
		}
		free(art->str);
		free(art);
		aux = aux_gen;
		free(aux->contenido);
		aux_gen = aux_gen->sig;
		(generos->largo)--;
		free(aux);
	}
	free(generos->str);
	free(generos);
}