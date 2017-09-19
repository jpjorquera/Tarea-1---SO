#include <stdio.h>
#include "id3v2lib/include/id3v2lib.h"
#include "../include/header.h"

char * get_artist(char * nombre_archivo) {
	FILE *archivo;
	archivo = fopen(nombre_archivo, "r");
	ID3v2_tag * tag = load_tag(nombre_archivo);
	ID3v2_frame * artista = tag_get_artist(tag);
	ID3v2_frame_text_content * contenido_artista = parse_text_frame_content(artista);
	fclose(archivo);
	return contenido_artista->data;
}

char * get_genre(char * nombre_archivo) {
	FILE *archivo;
	archivo = fopen(nombre_archivo, "r");
	ID3v2_tag * tag = load_tag(nombre_archivo);
	ID3v2_frame * genero = tag_get_genre(tag);
	ID3v2_frame_text_content * contenido_genero = parse_text_frame_content(genero);
	fclose(archivo);
	return contenido_genero->data;
}

void get_all(char * nombre_archivo, char * art, char * gnr) {
	FILE *archivo;
	archivo = fopen(nombre_archivo, "r");
	ID3v2_tag * tag = load_tag(nombre_archivo);
	ID3v2_frame * artista = tag_get_artist(tag);
	ID3v2_frame * genero = tag_get_genre(tag);
	ID3v2_frame_text_content * contenido_artista = parse_text_frame_content(artista);
	ID3v2_frame_text_content * contenido_genero = parse_text_frame_content(genero);
	art = contenido_artista->data;
	gnr = contenido_genero->data;
	fclose(archivo);
}