#include "../include/header.h"

void get_genre(char * genre) {
	unsigned short genero = (unsigned short)genre[0];
	switch (genero) {
		case 0:
			strcpy(genre, "Blues");
			break;
		case 1:
			strcpy(genre, "Classic Rock");
			break;
		case 2:
			strcpy(genre, "Country");
			break;
		case 3:
			strcpy(genre, "Dance");
			break;
		case 4:
			strcpy(genre, "Disco");
			break;
		case 5:
			strcpy(genre, "Funk");
			break;
		case 6:
			strcpy(genre, "Grunge");
			break;
		case 7:
			strcpy(genre, "Hip-Hop");
			break;
		case 8:
			strcpy(genre, "Jazz");
			break;
		case 9:
			strcpy(genre, "Metal");
			break;
		case 10:
			strcpy(genre, "New Age");
			break;
		case 11:
			strcpy(genre, "Oldies");
			break;
		case 12:
			strcpy(genre, "Other");
			break;
		case 13:
			strcpy(genre, "Pop");
			break;
		case 14:
			strcpy(genre, "R&B");
			break;
		case 15:
			strcpy(genre, "Rap");
			break;
		case 16:
			strcpy(genre, "Reggae");
			break;
		case 17:
			strcpy(genre, "Rock");
			break;
		case 18:
			strcpy(genre, "Techno");
			break;
		case 19:
			strcpy(genre, "Industrial");
			break;
		case 20:
			strcpy(genre, "Alternative");
			break;
		case 21:
			strcpy(genre, "Ska");
			break;
		case 22:
			strcpy(genre, "Death Metal");
			break;
		case 23:
			strcpy(genre, "Pranks");
			break;
		case 24:
			strcpy(genre, "Soundtrack");
			break;
		case 25:
			strcpy(genre, "Euro-Techno");
			break;
		case 26:
			strcpy(genre, "Ambient");
			break;
		case 27:
			strcpy(genre, "Trip-Hop");
			break;
		case 28:
			strcpy(genre, "Vocal");
			break;
		case 29:
			strcpy(genre, "Jazz+Funk");
			break;
		case 30:
			strcpy(genre, "Fusion");
			break;
		case 31:
			strcpy(genre, "Trance");
			break;
		case 32:
			strcpy(genre, "Classical");
			break;
		case 33:
			strcpy(genre, "Instrumental");
			break;
		case 34:
			strcpy(genre, "Acid");
			break;
		case 35:
			strcpy(genre, "House");
			break;
		case 36:
			strcpy(genre, "Game");
			break;
		case 37:
			strcpy(genre, "Sound Clip");
			break;
		case 38:
			strcpy(genre, "Gospel");
			break;
		case 39:
			strcpy(genre, "Noise");
			break;
		case 40:
			strcpy(genre, "AlternRock");
			break;
		case 41:
			strcpy(genre, "Bass");
			break;
		case 42:
			strcpy(genre, "Soul");
			break;
		case 43:
			strcpy(genre, "Punk");
			break;
		case 44:
			strcpy(genre, "Space");
			break;
		case 45:
			strcpy(genre, "Meditative");
			break;
		case 46:
			strcpy(genre, "Instrumental Pop");
			break;
		case 47:
			strcpy(genre, "Instrumental Rock");
			break;
		case 48:
			strcpy(genre, "Ethnic");
			break;
		case 49:
			strcpy(genre, "Gothic");
			break;
		case 50:
			strcpy(genre, "Darkwave");
			break;
		case 51:
			strcpy(genre, "Techno-Industrial");
			break;
		case 52:
			strcpy(genre, "Electronic");
			break;
		case 53:
			strcpy(genre, "Pop-Folk");
			break;
		case 54:
			strcpy(genre, "Eurodance");
			break;
		case 55:
			strcpy(genre, "Dream");
			break;
		case 56:
			strcpy(genre, "Southern Rock");
			break;
		case 57:
			strcpy(genre, "Comedy");
			break;
		case 58:
			strcpy(genre, "Cult");
			break;
		case 59:
			strcpy(genre, "Gangsta");
			break;
		case 60:
			strcpy(genre, "Top 40");
			break;
		case 61:
			strcpy(genre, "Christian Rap");
			break;
		case 62:
			strcpy(genre, "Pop/Funk");
			break;
		case 63:
			strcpy(genre, "Jungle");
			break;
		case 64:
			strcpy(genre, "Native American");
			break;
		case 65:
			strcpy(genre, "Cabaret");
			break;
		case 66:
			strcpy(genre, "New Wave");
			break;
		case 67:
			strcpy(genre, "Psychadelic");
			break;
		case 68:
			strcpy(genre, "Rave");
			break;
		case 69:
			strcpy(genre, "Showtunes");
			break;
		case 70:
			strcpy(genre, "Trailer");
			break;
		case 71:
			strcpy(genre, "Lo-Fi");
			break;
		case 72:
			strcpy(genre, "Tribal");
			break;
		case 73:
			strcpy(genre, "Acid Punk");
			break;
		case 74:
			strcpy(genre, "Acid Jazz");
			break;
		case 75:
			strcpy(genre, "Polka");
			break;
		case 76:
			strcpy(genre, "Retro");
			break;
		case 77:
			strcpy(genre, "Musical");
			break;
		case 78:
			strcpy(genre, "Rock & Roll");
			break;
			printf("entre American\n");
		case 79:
			strcpy(genre, "Hard Rock");
			break;
		default:
			strcpy(genre, "Sin genero");
	}
}

void get_all(FILE * archivo, mp3tag * id) {
	// Buscar tag al final del archivo
	fseek(archivo, -128, SEEK_END);
	// Definir parametros en el heap
	char * tag_type = malloc(sizeof(char)*3);
	char * title = malloc(sizeof(char)*30);
	char * artist = malloc(sizeof(char)*30);
	char * album = malloc(sizeof(char)*30);
	char * year = malloc(sizeof(char)*4);
	char * comment = malloc(sizeof(char)*30);
	char * genre = malloc(sizeof(char)*20);
	// Leer atributos del archivo
	fread(tag_type, sizeof(char), 3, archivo);
	fread(title, sizeof(char), 30, archivo);
	fread(artist, sizeof(char), 30, archivo);
	fread(album, sizeof(char), 30, archivo);
	fread(year, sizeof(char), 4, archivo);
	fread(comment, sizeof(char), 30, archivo);
	fread(genre, sizeof(char), 1, archivo);
	// Decodificar genero
	get_genre(genre);
	// Almacenar en el mp3tag
	id->tag = tag_type;
	id->song = title;
	id->artist = artist;
	id->genre = genre;
	id->album = album;
	id->year = year;
	id->comment = comment;
}

int verifyTag(char * id) {
	if (strncmp(id, "TAG", 3) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}