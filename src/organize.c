#include <ctype.h>
#include "../include/header.h"

typedef struct actn_flgs {
   short status;
   short salir;
   short mover;
   short abrir;
   short azar;
   short mostrar;
} action_flags;

void inicializarActFlags(action_flags * flags) {
   flags->status = 0;
   flags->salir = 0;
   flags->mover = 0;
   flags->azar = 0;
   flags->abrir = 0;
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
   char * err = "Accion invalida, intente denuevo";
   char org_bib[20];
   // Pedir organizar
   printf("¿Desea Organizar la biblioteca?: (si/no)\n");
   scanf("%19s", org_bib);
   char * clean = strip(org_bib);
   int i;
   for (i=0; clean[i]; i++) clean[i] = tolower((unsigned char)clean[i]);
   if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
   // Mientras rpta no sea si/no
   while (strcmp(clean, "si")) {
      memset(org_bib, '\0', 20);
      printf("%s\n", err);
      scanf("%9s", org_bib);
      clean = strip(org_bib);
      for (i=0; clean[i]; i++) clean[i] = tolower((unsigned char)clean[i]);
      if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
   }
   // Organizar libreria
   lista * canciones = (lista *)calloc(1, sizeof(lista));
   inicializarLista(canciones);
   enlistSongs(canciones);
   createFolders(canciones);
   moveSongs(canciones);
   if (!canciones->largo){
      printf("No habia nada en la biblioteca, saliendo\n");
      exit(0);
   }
   printf("Biblioteca organizada!\n\n");
   // Acciones
   char * accion = "Ingrese accion que desea realizar: ";
   char * mostrar = "Mostrar";
   char * mover = "Mover a";
   char * volver = "Volver";
   char * abrir = "Abrir";
   char * azar = "Azar";
   char * salir = "Salir";
   unsigned int max_text = strlen(accion) + strlen(mostrar) + strlen(salir)
                          + strlen(mover) + strlen(azar) + 15;
   unsigned int max_text_volver = strlen(accion) + strlen(mostrar) + strlen(salir)
                                + strlen(azar) + strlen(volver) + 15;
   unsigned int max_text_abrir = strlen(accion) + strlen(mostrar) + strlen(salir)
                                + strlen(azar) + strlen(volver) + strlen(abrir) +15;
   // Verificar mayor para definir accion actual
   unsigned int max_text_all = max_text;
   if (max_text_volver > max_text_all) {
      max_text_all = max_text_volver;
   }
   if (max_text_abrir > max_text_all) {
      max_text_all = max_text_abrir;
   }
   // String para imprimir accion
   char * texto_accion_inicial = (char *)calloc(max_text, sizeof(char));
   char * texto_accion_volver = (char *)calloc(max_text_volver, sizeof(char));
   char * texto_accion_abrir = (char *)calloc(max_text_abrir, sizeof(char));
   char * texto_accion_actual = (char *)calloc(max_text_all, sizeof(char));
   strcpy(texto_accion_inicial, accion);
   strcat(texto_accion_inicial, "(");
   strcat(texto_accion_inicial, mostrar);
   strcat(texto_accion_inicial, ", ");
   // Alternativa de texto
   strcpy(texto_accion_volver, texto_accion_inicial);
   strcpy(texto_accion_abrir, texto_accion_inicial);
   strcat(texto_accion_volver, mover);
   strcat(texto_accion_volver, ", ");
   strcat(texto_accion_volver, volver);
   strcat(texto_accion_volver, ", ");
   strcat(texto_accion_abrir, abrir);
   strcat(texto_accion_abrir, ", ");
   strcat(texto_accion_abrir, volver);
   strcat(texto_accion_abrir, ", ");
   strcat(texto_accion_inicial, mover);
   strcat(texto_accion_inicial, ", ");
   //
   strcat(texto_accion_inicial, azar);
   strcat(texto_accion_volver, azar);
   strcat(texto_accion_abrir, azar);
   strcat(texto_accion_inicial, ", ");
   strcat(texto_accion_volver, ", ");
   strcat(texto_accion_abrir, ", ");
   strcat(texto_accion_inicial, salir);
   strcat(texto_accion_volver, salir);
   strcat(texto_accion_abrir, salir);
   strcat(texto_accion_inicial, ")");
   strcat(texto_accion_volver, ")");
   strcat(texto_accion_abrir, ")");
   // Convertir a lowercases
   mostrar = "mostrar";
   mover = "mover a";
   volver = "volver";
   abrir = "abrir";
   azar = "azar";
   salir = "salir";
   // Flags para identificar accion
   action_flags * actn_status = (action_flags *)calloc(1, sizeof(action_flags));
   inicializarActFlags(actn_status);
   short flag_level = 0;
   // Posicion relativas;
   nodo * actual = canciones->inicial;
   unsigned int length = 0, pos_genre = 0;
   // Recibir input
   strcpy(texto_accion_actual, texto_accion_inicial);
   printf("%s\n", texto_accion_actual);
   char accn[20];
   scanf("%19s", accn);
   char * clean_accn = strip(accn);
   for (i=0; clean_accn[i]; i++) clean_accn[i] = tolower((unsigned char)clean_accn[i]);
   // Verificar accion
      // Salir
   if (!strcmp(clean_accn, salir)) {
      printf("Saliendo del programa\n");
      free(texto_accion_inicial);
      free(texto_accion_volver);
      free(texto_accion_abrir);
      free(texto_accion_actual);
      exit(0);
   }
   // Mostrar
   else if (!strcmp(clean_accn, mostrar)) {
      actn_status->status = 1;
      nodo * auxiliar = actual;
      while (pos_genre < canciones->largo) {
         length += strlen(auxiliar->contenido);
         pos_genre++;
      }
      char * generos = (char *)calloc(length + (pos_genre * 2) + 2, sizeof(char));
      auxiliar = actual;
      while (pos_genre > 0) {
         strcat(generos, auxiliar->contenido);
         strcat(generos, " ");
         auxiliar = auxiliar->sig;
         pos_genre--;
      }
      printf("%s\n\n", generos);
   }
   // Mover a
   else if (!strcmp(clean_accn, mover)) {
      actn_status->status = 1;
      flag_level++;
      memset(texto_accion_actual, '\0', max_text_all);
      strcpy(texto_accion_actual, texto_accion_volver);
   }
   // Azar
   else if (!strcmp(clean_accn, azar)) {
      actn_status->status = 1;
   }
   // Siguiente accion/ accion erronea
   while (1) {
      memset(accn, '\0', 20);
      if (!actn_status->status) printf("%s\n", err);
      else {printf("%s\n", texto_accion_actual);}
      scanf("%19s", accn);
      clean_accn = strip(accn);
      for (i=0; clean_accn[i]; i++) clean_accn[i] = tolower((unsigned char)clean_accn[i]);
      if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
   }

   free(texto_accion_inicial);





}