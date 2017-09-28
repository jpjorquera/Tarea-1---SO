#include <stdio.h>
#include <stdlib.h>
#include "include/header.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
	lista * canciones = (lista *)calloc(1, sizeof(lista));
	inicializarLista(canciones);
	enlistSongs(canciones);

	int i = 0, j = 0, k = 0;
	nodo * auxi = canciones->inicial;
	nodo * auxj;
	nodo * auxk;
	while (i < canciones->largo) {
		//printf("\n");
		//printf("Genero: %s\n", auxi->contenido);
		auxj = auxi->subcontenido->inicial;
		//printf("n de artistas: %d\n", auxi->subcontenido->largo);
		j = 0;
		while (j < auxi->subcontenido->largo) {
			//printf("n de canciones: %d\n", auxj->subcontenido->largo);
			/*printf("\n");
			printf("Artista: %s\n", auxj->contenido);
			printf("\n");*/
			auxk = auxj->subcontenido->inicial;
			k = 0;
			while (k < auxj->subcontenido->largo) {
				//printf("Titulo: %s\n", auxk->id->song);
				k++;
				if (k < auxj->subcontenido->largo) {
					auxk = auxk->sig;
				}
			}
			j++;
			if (j < auxi->subcontenido->largo) {
				auxj = auxj->sig;
			}
		}
		i++;
		if (i < canciones->largo) {
			auxi = auxi->sig;
		}
		createFolders(canciones);
		moveSongs(canciones);
	}


	//destroyAdy(canciones);
}