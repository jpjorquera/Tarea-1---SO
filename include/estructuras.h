#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

typedef struct node {
	char * cosa;
	struct node * sig;
} nodo;

typedef struct lista_enlazada {
	struct node * inicial;
	short largo;
} lista;

#endif