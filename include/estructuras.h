#ifndef ESTRUCTURAS_H_
#define ESTRUCTURAS_H_

#define ID_TAG_SIZE 3
#define ID_TEXT_SIZE 30
#define ID_YEAR_SIZE 4

typedef struct node {
	char * contenido;
	struct node * sig;
	struct lista_enlazada * subcontenido;
	struct tag * id;
} nodo;

typedef struct lista_enlazada {
	struct node * inicial;
	struct node * final;
	unsigned int largo;
} lista;

typedef struct tag {
	char * tag;
	char * song;
	char * artist;
	char * genre;
	char * album;
	char * year;
	char * comment;
} mp3tag;

int buscarGenero(lista * generos, char * genero);
int buscarArtista(lista * generos, char * genero, char * artista);
void insertarGen(lista * generos, char * genero);
void insertarArt(lista * generos, char * genero, char * artista);
void insertarTag(lista * generos, mp3tag * tag);
void inicializarLista(lista * generos);
void freeTag(mp3tag * tag);
void destroyAdy(lista * generos);

#endif