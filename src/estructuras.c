#include <stdlib.h>
#include "../include/estructuras.h"

int buscarGenero(lista generos, char * genero) {
	nodo * actual = generos.inicial;
	unsigned int largo = generos.largo;
	unsigned int i = 0;
	while (i < largo) {
		if (actual->contenido == genero) {
			return 1;
		}
		else {
			actual = actual->sig;
		}
		++i;
	}
	return 0;
}

int buscarArtista(lista generos, char * genero,char * artista) {
	nodo * actual_genero = generos.inicial;
	unsigned int largo_genero = generos.largo;
	unsigned int i = 0, j = 0;
	while (i < largo_genero) {
		if (actual_genero->contenido == genero) {
			nodo * actual_artista = actual_genero->subcontenido->inicial;
			unsigned int largo_artista = actual_genero->subcontenido->largo;
			while (j < largo_artista) {
				if (actual_artista->contenido == artista){
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

void insertarGen(lista generos, char * genero) {
	if (generos.largo == 0){
		nodo * aux = (nodo *)malloc(sizeof(nodo));
		aux->contenido = genero;
		generos.inicial = aux;
		generos.final = aux;
		generos.largo = 1;
	}
	else {
		nodo * aux = (nodo *)malloc(sizeof(nodo));
		aux->contenido = genero;
		generos.final->sig = aux;
		generos.final = aux;
		generos.largo += 1;
	}
}

void insertarArt(lista generos, char * genero, char * artista) {
	nodo * actual_genero = generos.inicial;
	while (actual_genero->contenido != genero) {
		actual_genero = actual_genero->sig;
	}
	if (actual_genero->subcontenido->largo == 0) {
		nodo * aux = (nodo *)malloc(sizeof(nodo));
		aux->contenido = artista;
		actual_genero->subcontenido->inicial = aux;
		actual_genero->subcontenido->final = aux;
		actual_genero->subcontenido->largo = 1;
	}
	else {
		nodo * aux = (nodo *)malloc(sizeof(nodo));
		aux->contenido = artista;
		actual_genero->subcontenido->final->sig = aux;
		actual_genero->subcontenido->final = aux;
		actual_genero->subcontenido->largo += 1;
	}
}

void inicializarLista(lista * lis) {
	lis = (lista *)malloc(sizeof(lista));
}

void destroyAdy(lista * generos) {
	nodo * aux;
	lista * art = generos->inicial->subcontenido;
	while (generos->largo > 0) {
		while (art->largo > 0) {
			aux = art->inicial->subcontenido->inicial;
			art->inicial->subcontenido->inicial = art->inicial->subcontenido->inicial->sig;
			free(aux);
			art->inicial->subcontenido->largo -= 1;
		}
		free(art->inicial->subcontenido);

		aux = generos->inicial;
		generos->inicial = generos->inicial->sig;
		free(aux);
		generos->largo -= 1;
	}
}