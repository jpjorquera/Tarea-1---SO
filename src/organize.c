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



   i = 0;
   int j = 0, k = 0;
   unsigned int largo_generos = 0;
   unsigned int largo_artistas = 0;
   unsigned int largo_canciones = 0;
   nodo * aux_gen = canciones->inicial;
   nodo * aux_art;
   nodo * aux_song;
   char * string_generos = (char *)calloc(1, sizeof(char));
   char * iterador = (char *)calloc(2, sizeof(char));
   while (i < canciones->largo) {
      largo_generos += strlen(aux_gen->contenido)+9;
      string_generos = (char *)realloc(string_generos, largo_generos);
      memset(iterador, '\0', 2);
      strcat(string_generos, "[");
      sprintf(iterador, "%d", (i+1));
      strcat(string_generos, iterador);
      strcat(string_generos, "] ");
      strcat(string_generos, aux_gen->contenido);
      strcat(string_generos, "\n");
      char * string_artistas = (char *)calloc(1, sizeof(char));
      aux_art = aux_gen->subcontenido->inicial;
      while (j < aux_gen->subcontenido->largo) {
         largo_artistas += strlen(aux_art->contenido)+9;
         string_artistas = (char *)realloc(string_artistas, largo_artistas);
         memset(iterador, '\0', 2);
         strcat(string_artistas, "[");
         sprintf(iterador, "%d", (j+1));
         strcat(string_artistas, iterador);
         strcat(string_artistas, "] ");
         strcat(string_artistas, aux_art->contenido);
         strcat(string_artistas, "\n");
         char * string_canciones = (char *)calloc(1, sizeof(char));
         aux_song = aux_art->subcontenido->inicial;
         while (k < aux_art->subcontenido->largo) {
            largo_canciones += strlen(aux_song->id->song)+9;
            string_canciones = (char *)realloc(string_canciones, largo_canciones);
            memset(iterador, '\0', 2);
            strcat(string_canciones, "[");
            sprintf(iterador, "%d", (k+1));
            strcat(string_canciones, iterador);
            strcat(string_canciones, "] ");
            strcat(string_canciones, aux_song->id->song);
            strcat(string_canciones, "\n");
            aux_song = aux_song->sig;
            k++;
         }
         printf("%s\n", string_canciones);
         largo_canciones = 0;
         k = 0;
         aux_art = aux_art->sig;
         j++;
      }
      largo_artistas = 0;
      j = 0;
      aux_gen = aux_gen->sig;
      i++;
   }
   free(iterador);
   i = 0;





   // Acciones
   char * accion = "Ingrese accion que desea realizar: ";
   char * mostrar = "[1] Mostrar\n";
   char * mover = "[2] Mover a\n";
   char * volver = "[3] Volver\n";
   char * abrir = "[2] Abrir\n";
   char * azar1 = "[3] Azar\n";
   char * azar2 = "[4] Azar\n";
   char * salir1 = "[4] Salir\n";
   char * salir2 = "[5] Salir\n";
   // Calcular largos
   unsigned int max_text = strlen(accion) + strlen(mostrar) + strlen(salir1)
                          + strlen(mover) + strlen(azar1) + 15;
   unsigned int max_text_volver = strlen(accion) + strlen(mostrar) + strlen(salir2)
                                + strlen(azar2) + strlen(volver) + 15;
   unsigned int max_text_abrir = strlen(accion) + strlen(mostrar) + strlen(salir2)
                                + strlen(azar2) + strlen(volver) + strlen(abrir) +15;
   // Verificar mayor para definir accion actual
   unsigned int max_text_all = max_text;
   if (max_text_volver > max_text_all) {
      max_text_all = max_text_volver;
   }
   if (max_text_abrir > max_text_all) {
      max_text_all = max_text_abrir;
   }
   // Strings para imprimir accion
   char * texto_accion_inicial = (char *)calloc(max_text, sizeof(char));
   char * texto_accion_volver = (char *)calloc(max_text_volver, sizeof(char));
   char * texto_accion_abrir = (char *)calloc(max_text_abrir, sizeof(char));
   char * texto_accion_actual = (char *)calloc(max_text_all, sizeof(char));
   strcpy(texto_accion_inicial, accion);
   strcat(texto_accion_inicial, "\n");
   strcat(texto_accion_inicial, mostrar);
   // Alternativa de texto
   strcpy(texto_accion_volver, texto_accion_inicial);
   strcpy(texto_accion_abrir, texto_accion_inicial);
   strcat(texto_accion_volver, mover);
   strcat(texto_accion_volver, volver);
   strcat(texto_accion_abrir, abrir);
   strcat(texto_accion_abrir, volver);
   strcat(texto_accion_inicial, mover);
   // Finalizar cada uno
   strcat(texto_accion_inicial, azar1);
   strcat(texto_accion_volver, azar2);
   strcat(texto_accion_abrir, azar2);
   strcat(texto_accion_inicial, salir1);
   strcat(texto_accion_volver, salir2);
   strcat(texto_accion_abrir, salir2);
   // Flags para identificar accion
   action_flags * actn_status = (action_flags *)calloc(1, sizeof(action_flags));
   inicializarActFlags(actn_status);
   short flag_level = 0;
   // Posicion relativas;
   nodo * actual = canciones->inicial;
   nodo * anterior = actual;
   unsigned int length = 0, pos_genre = 0;
   /*// Recibir input
   strcpy(texto_accion_actual, texto_accion_inicial);
   printf("%s", texto_accion_actual);
   char accn[15];
   memset(accn, '\0', 15);
   scanf("%s", accn);
   char * clean_accn = strip(accn);
   for (i=0; clean_accn[i]; i++) clean_accn[i] = tolower((unsigned char)clean_accn[i]);
   // Verificar accion
      // Salir
   if (!strncmp(clean_accn, "4", 1)) {
      printf("Saliendo del programa\n");
      // Liberar memoria
      free(texto_accion_inicial);
      free(texto_accion_volver);
      free(texto_accion_abrir);
      free(texto_accion_actual);
      exit(0);
   }
   // Mostrar
   else if (!strncmp(clean_accn, "1", 1)) {
      actn_status->status = 1;
      nodo * auxiliar = actual;
      // Ver largo del string a crear
      while (pos_genre < canciones->largo) {
         length += strlen(auxiliar->contenido);
         pos_genre++;
      }
      // Generar string de generos a imprimir
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
   // Azar
   else if (!strncmp(clean_accn, "3", 1)) {
      actn_status->status = 1;

   }
   // Mover a
   else if (!strncmp(clean_accn, "2", 1)) {
      actn_status->status = 1;
      flag_level++;

      
            nodo * auxiliar = actual;
            unsigned int largo = 0;
            while (largo < canciones->largo) {
               if (1) {
                  anterior = auxiliar;
                  actual = auxiliar->subcontenido->inicial;
                  memset(texto_accion_actual, '\0', max_text_all);
                  strcpy(texto_accion_actual, texto_accion_volver);
                  actn_status->mover = 1;
                  printf("Moviendose\n");
                  break;
               }
               auxiliar = auxiliar->sig;
               largo++;
            }
      if (!actn_status->mover) {
         printf("Carpeta erronea\n");
      }
      actn_status->mover = 0;
   }

   // Siguiente accion/ accion erronea
   while (1) {
      memset(accn, '\0', 3);
      if (!actn_status->status) printf("%s\n", err);
      else {printf("%s", texto_accion_actual);}
      scanf("%19s", accn);
      clean_accn = strip(accn);
      for (i=0; clean_accn[i]; i++) clean_accn[i] = tolower((unsigned char)clean_accn[i]);
      if (!strcmp(clean, "no")) printf("Saliendo del programa\n"), exit(0);
   }

   free(texto_accion_inicial);*/





}