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
	char * str;
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

// Revisa si el genero ya esta en la lista
int buscarGenero(lista * generos, char * genero);
// Revisa si el artista ya esta en la lista
int buscarArtista(lista * generos, char * genero, char * artista);
// Intenta insertar el genero
void insertarGen(lista * generos, char * genero);
// Intenta insertar el artista
void insertarArt(lista * generos, char * genero, char * artista);
// Intenta insertar el tag id3v1
void insertarTag(lista * generos, mp3tag * tag);
// Inicializa la lista con largo 0
void inicializarLista(lista * generos);
// Libera la memoria del tag
void freeTag(mp3tag * tag, short mode);
// Destruye lista de adyacencia
void destroyAdy(lista * generos, short mode);
// Destruye lista de adyacencia especializada en strings
void destroyAdyStr(lista * generos, short mode);

#endif