#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

typedef struct node {
	char * contenido;
	struct node * sig;
	struct lista_enlazada * subcontenido;
} nodo;

typedef struct lista_enlazada {
	struct node * inicial;
	struct node * final;
	unsigned int largo;
} lista;

int buscarGenero(lista generos, char * genero);
int buscarArtista(lista generos, char * genero, char * artista);

#endif