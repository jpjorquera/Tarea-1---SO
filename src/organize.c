#include <ctype.h>
#include "../include/header.h"

typedef struct actn_flgs {
  short salir;
  short mover;
  short azar;
  short mostrar;
} action_flags;

void inicializarActFlags(action_flags * flags) {
  flags->salir = 0;
  flags->mover = 0;
  flags->azar = 0;
  flags->mostrar = 0;
}

char * strip(char * palabra) {
  char * end;
  // Eliminar inicial
  while(isspace((unsigned char) *palabra)) palabra++;
  // Todos espacios
  if (*palabra == 0) {
    return palabra;
  }
  // Eliminar final
  end = palabra + strlen(palabra) - 1;
  while(end > palabra && isspace((unsigned char)*end)) {
    end--;
  }
  *(end+1) = 0;
  return palabra;
}

int main() {
  char * err = "Comando erroneo, intente denuevo";
  char org_bib[20];
  // Pedir organizar
  printf("¿Desea Organizar la biblioteca?:\n");
  scanf("%19s", org_bib);
  char * clean = strip(org_bib);
  if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
  // Mientras rpta no sea si o no
  while (strcmp(clean, "si")) {
    printf("%s\n", err);
    scanf("%9s", org_bib);
    clean = strip(org_bib);
    if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
  }
  // Organizar
  lista * canciones = (lista *)calloc(1, sizeof(lista));
  inicializarLista(canciones);
  enlistSongs(canciones);
  createFolders(canciones);
  moveSongs(canciones);
  printf("Biblioteca organizada!\n\n");

  // Acciones
  char * accion = "Ingrese accion que desea realizar: ";
  char * mostrar = "Mostrar";
  char * mover = "Mover a";
  char * volver = "Volver";
  char * azar = "Azar";
  char * salir = "Salir";
  unsigned int max_text = strlen(accion) + strlen(mostrar) + strlen(salir)
                          + strlen(mover) + strlen(azar) + 15;
  unsigned int max_text_volver = strlen(accion) + strlen(mostrar) + strlen(salir)
                                + strlen(azar) + strlen(volver) + 15;
  // String para imprimir accion
  char * texto_accion_actual = (char *)calloc(max_text, sizeof(char));
  char * texto_accion_volver = (char *)calloc(max_text_volver, sizeof(char));
  strcpy(texto_accion_actual, accion);
  strcat(texto_accion_actual, "(");
  strcat(texto_accion_actual, mostrar);
  strcat(texto_accion_actual, ", ");
  // Alternativa de texto
  strcpy(texto_accion_volver, texto_accion_actual);
  strcpy(texto_accion_volver, volver);
  strcat(texto_accion_volver, ", ");
  strcat(texto_accion_actual, mover);
  strcat(texto_accion_actual, ", ");
  //
  strcat(texto_accion_actual, azar);
  strcat(texto_accion_volver, azar);
  strcat(texto_accion_actual, ", ");
  strcat(texto_accion_volver, ", ");
  strcat(texto_accion_actual, salir);
  strcat(texto_accion_volver, salir);
  strcat(texto_accion_actual, ")");
  strcat(texto_accion_volver, ")");
  // Recibir input
  printf("%s\n", texto_accion_actual);
  char accn[20];
  // Flags para identificar accion
  action_flags * actn_status = (action_flags *)calloc(1, sizeof(action_flags));
  inicializarActFlags(actn_status);
  scanf("%19s", accn);
  char * clean_accn = strip(accn);
  if (!strcmp(clean_accn, salir)) {
    printf("Saliendo del programa\n");
    free(texto_accion_actual);
    free(texto_accion_volver);
    exit(0);
  }
  while (1) {
    printf("%s\n", err);
    scanf("%19s", org_bib);
    clean_accn = strip(org_bib);
    if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
  }

  free(texto_accion_actual);
  




}