#include <ctype.h>
#include <time.h>
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

// Funcion para eliminar espacios del input
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
   srand(time(NULL));
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
   printf("\n");
   printf("Biblioteca organizada!\n\n");


   // Crear strings de opciones a mostrar
   lista * alternativas = calloc(1, sizeof(lista));
   inicializarLista(alternativas);
   i = 0;
   int j = 0, k = 0;
   unsigned int largo_generos = 0;
   unsigned int largo_artistas = 0;
   unsigned int largo_canciones = 0;
   nodo * aux_gen = canciones->inicial;
   nodo * aux_art;
   nodo * aux_song;
   char * string_generos = (char *)calloc(1, sizeof(char));
   // Ir formando el string para mostrar opciones para
   // generos, artistas y canciones

   // Avanzar generos
   while (i < canciones->largo) {
      // Recalcular largo
      largo_generos += strlen(aux_gen->contenido)+9;
      string_generos = (char *)realloc(string_generos, largo_generos);
      char * iterador = (char *)calloc(4, sizeof(char));
      // Armar opciones de genero
      memset(iterador, '\0', 4);
      strcat(string_generos, "[");
      sprintf(iterador, "%d", (i+1));
      strcat(string_generos, iterador);
      insertarGen(alternativas, iterador);
      strcat(string_generos, "] ");
      strcat(string_generos, aux_gen->contenido);
      strcat(string_generos, "\n");
      char * string_artistas = (char *)calloc(1, sizeof(char));

      // Avanzar artistas
      aux_art = aux_gen->subcontenido->inicial;
      while (j < aux_gen->subcontenido->largo) {
         // Recalcular largo
         largo_artistas += strlen(aux_art->contenido)+9;
         string_artistas = (char *)realloc(string_artistas, largo_artistas);
         char * iterador2 = (char *)calloc(4, sizeof(char));
         // Armar opciones de artista
         memset(iterador2, '\0', 4);
         strcat(string_artistas, "[");
         sprintf(iterador2, "%d", (j+1));
         insertarArt(alternativas, iterador, iterador2);
         strcat(string_artistas, iterador2);
         strcat(string_artistas, "] ");
         strcat(string_artistas, aux_art->contenido);
         strcat(string_artistas, "\n");
         char * string_canciones = (char *)calloc(1, sizeof(char));
         aux_song = aux_art->subcontenido->inicial;

         // Avanzar canciones
         while (k < aux_art->subcontenido->largo) {
            // Recalcular largo
            largo_canciones += strlen(aux_song->id->song)+9;
            string_canciones = (char *)realloc(string_canciones, largo_canciones);
            char * iterador3 = (char *)calloc(4, sizeof(char));
            // Armar opciones de cancion
            memset(iterador3, '\0', 4);
            strcat(string_canciones, "[");
            sprintf(iterador3, "%d", (k+1));
            strcat(string_canciones, iterador3);
            strcat(string_canciones, "] ");
            strcat(string_canciones, aux_song->id->song);
            strcat(string_canciones, "\n");
            aux_song = aux_song->sig;
            free(iterador3);
            k++;
         }
         aux_art->subcontenido->str = string_canciones;
         largo_canciones = 0;
         k = 0;
         aux_art = aux_art->sig;
         j++;
      }
      aux_gen->subcontenido->str = string_artistas;
      largo_artistas = 0;
      j = 0;
      aux_gen = aux_gen->sig;
      i++;
   }
   alternativas->str = string_generos;
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
   /*************************************************/
   // Recibir input
   strcpy(texto_accion_actual, texto_accion_inicial);
   printf("%s", texto_accion_actual);
   char accn[15];
   memset(accn, '\0', 15);
   scanf("%s", accn);
   char * clean_accn = strip(accn);
   printf("\n");
   // Verificar accion
      // Salir
   if (!strncmp(clean_accn, "4", 1)) {
      printf("Saliendo del programa\n");
      // Liberar memoria
      free(texto_accion_inicial);
      free(texto_accion_volver);
      free(texto_accion_abrir);
      free(texto_accion_actual);
      free(actn_status);
      destroyAdy(canciones, 0);
      destroyAdyStr(alternativas, 1);
      exit(0);
   }
   // Mostrar contenido
   else if (!strncmp(clean_accn, "1", 1)) {
      actn_status->status = 1;
      actn_status->mostrar = 1;
      printf("Contenido:\n");
      printf("%s\n", alternativas->str);
   }
   // Azar
   else if (!strncmp(clean_accn, "3", 1)) {
      // Obtener semilla
      int random = rand() % (canciones->largo + 1);
      nodo * aux_rand = canciones->inicial;
      i = 0;
      // Avanzar genero
      while (i < (random-1)) {
         aux_rand = aux_rand->sig;
         i++;
      }
      random = rand() % (aux_rand->subcontenido->largo + 1);
      i = 0;
      aux_rand = aux_rand->subcontenido->inicial;
      // Avanzar artista
      while (i < (random-1)) {
         aux_rand = aux_rand->sig;
         i++;
      }
      printf("El artista al azar es ");
      printf("%s\nSus canciones son:\n", aux_rand->contenido);
      unsigned int random_length = 0;
      char * random_art = (char *)calloc(1, sizeof(char));
      int rand_max = aux_rand->subcontenido->largo;
      aux_rand = aux_rand->subcontenido->inicial;
      i = 0;
      // Armar string de canciones
      while (i < rand_max) {
         random_length += strlen(aux_rand->id->song) + 6;
         random_art = (char *)realloc(random_art, random_length);
         strcat(random_art, "- ");
         strcat(random_art, aux_rand->id->song);
         strcat(random_art, "\n");
         aux_rand = aux_rand->sig;
         i++;
      }
      printf("%s\n", random_art);
      actn_status->status = 1;
      free(random_art);
   }
   // Mover a
   else if (!strncmp(clean_accn, "2", 1)) {
      printf("Opciones:\n");
      printf("%s", alternativas->str);
      printf("[%d] Cancelar\n", (alternativas->largo+1));
      while (1) {
         scanf("%s", accn);
         printf("\n");
         char * clean_accn = strip(accn);
         int dig_accn = atoi(clean_accn);
         if (dig_accn > 0 && dig_accn < canciones->largo+1) {
            actn_status->status = 1;
            flag_level++;
            i = 0;
            anterior = canciones->inicial;
            while (i < (dig_accn-1)) {
               actual = actual->sig;
               i++;
            }
            printf("Moviendose a ");
            printf("%s\n\n", actual->contenido);
            memset(texto_accion_actual, '\0', max_text_all);
            strcpy(texto_accion_actual, texto_accion_volver);
            break;
         }
         if (dig_accn == (canciones->largo+1)) {
            actn_status->status = 1;
            break;
         }
         if (!actn_status->status) {
            printf("%s\n", err);
            actn_status->mover = 1;
         }
      }
   }
   // No entro a ningun comando
   else {
      actn_status->status = 0;
   }


   // Siguiente accion
   while (1) {
      // Si accion fue erronea
      if (!actn_status->status) printf("%s\n", err);
      // Mostrar opciones de accion
      else {printf("%s", texto_accion_actual);}
      memset(accn, '\0', 14);
      // Recibir input
      scanf("%19s", accn);
      clean_accn = strip(accn);
      printf("\n");
      // Verificar accion
         // Salir || Azar
      if (!strncmp(clean_accn, "4", 1)) {
         // Salir
         if (!flag_level) {
            printf("Saliendo del programa\n");
            // Liberar memoria
            free(texto_accion_inicial);
            free(texto_accion_volver);
            free(texto_accion_abrir);
            free(texto_accion_actual);
            free(actn_status);
            destroyAdy(canciones, 0);
            destroyAdyStr(alternativas, 1);
            exit(0);
         }
         // Azar
         else {
            // Obtener semilla
            int random = rand() % (canciones->largo + 1);
            nodo * aux_rand = canciones->inicial;
            i = 0;
            // Avanzar genero
            while (i < (random-1)) {
               aux_rand = aux_rand->sig;
               i++;
            }
            random = rand() % (aux_rand->subcontenido->largo + 1);
            i = 0;
            aux_rand = aux_rand->subcontenido->inicial;
            // Avanzar artista
            while (i < (random-1)) {
               aux_rand = aux_rand->sig;
               i++;
            }
            printf("El artista al azar es ");
            printf("%s\nSus canciones son:\n", aux_rand->contenido);
            unsigned int random_length = 0;
            char * random_art = (char *)calloc(1, sizeof(char));
            int rand_max = aux_rand->subcontenido->largo;
            aux_rand = aux_rand->subcontenido->inicial;
            i = 0;
            // Armar string de canciones
            while (i < rand_max) {
               random_length += strlen(aux_rand->id->song) + 6;
               random_art = (char *)realloc(random_art, random_length);
               strcat(random_art, "- ");
               strcat(random_art, aux_rand->id->song);
               strcat(random_art, "\n");
               aux_rand = aux_rand->sig;
               i++;
            }
            printf("%s\n", random_art);
            actn_status->status = 1;
            free(random_art);
         }
      }
      // Mostrar
      else if (!strncmp(clean_accn, "1", 1)) {
         actn_status->status = 1;
         actn_status->mostrar = 1;
         printf("Contenido:\n");
         if (flag_level == 0) {
            printf("%s\n", alternativas->str);
         }
         else {
            printf("%s\n", actual->subcontenido->str);
         }
      }
      // Azar || Volver
      else if (!strncmp(clean_accn, "3", 1)) {
         // Primer nivel -> Azar
         if (!flag_level) {
            // Obtener semilla
            int random = rand() % (canciones->largo + 1);
            nodo * aux_rand = canciones->inicial;
            i = 0;
            // Avanzar genero
            while (i < (random-1)) {
               aux_rand = aux_rand->sig;
               i++;
            }
            random = rand() % (aux_rand->subcontenido->largo + 1);
            i = 0;
            aux_rand = aux_rand->subcontenido->inicial;
            // Avanzar artista
            while (i < (random-1)) {
               aux_rand = aux_rand->sig;
               i++;
            }
            printf("El artista al azar es ");
            printf("%s\nSus canciones son:\n", aux_rand->contenido);
            unsigned int random_length = 0;
            char * random_art = (char *)calloc(1, sizeof(char));
            int rand_max = aux_rand->subcontenido->largo;
            aux_rand = aux_rand->subcontenido->inicial;
            i = 0;
            // Armar string de canciones
            while (i < rand_max) {
               random_length += strlen(aux_rand->id->song) + 6;
               random_art = (char *)realloc(random_art, random_length);
               strcat(random_art, "- ");
               strcat(random_art, aux_rand->id->song);
               strcat(random_art, "\n");
               aux_rand = aux_rand->sig;
               i++;
            }
            printf("%s\n", random_art);
            actn_status->status = 1;
            free(random_art);
         }
         // 2o o 3er nivel -> Volver
         // Volver al nivel anterior
         else {
            // Volver a biblioteca
            actn_status->status = 1;
            if (flag_level == 1) {
               printf("Volviendo a biblioteca\n");
               anterior = canciones->inicial;
               actual = canciones->inicial;
               memset(texto_accion_actual, '\0', max_text_all);
               strcpy(texto_accion_actual, texto_accion_inicial);
            }
            else if (flag_level == 2) {
               // Volver a genero
               printf("Volviendo a %s\n", anterior->contenido);
               actual = anterior;
               anterior = canciones->inicial;
               memset(texto_accion_actual, '\0', max_text_all);
               strcpy(texto_accion_actual, texto_accion_volver);
            }
            printf("\n");
            flag_level--;
         }
      }
   
      // Mover a || Abrir
      else if (!strncmp(clean_accn, "2", 1)) {
         // Mover a
         if (flag_level < 2) {
            printf("Opciones:\n");
            // Mostrar opciones de subcontenido
            if (flag_level == 0){
               printf("%s", alternativas->str);
               printf("[%d] Cancelar\n", (alternativas->largo+1));
            }
            else if (flag_level == 1) {
               printf("%s", actual->subcontenido->str);
               printf("[%d] Cancelar\n", (actual->subcontenido->largo+1));
            }
            // Mientras accion sea erronea
            while (1) {
               char accn_mostrar[15];
               // Recibir input
               scanf("%s", accn_mostrar);
               memset(accn, '\0', 15);
               printf("\n");
               char * clean_accn_mostrar = strip(accn_mostrar);
               int dig_accn = atoi(clean_accn_mostrar);
               unsigned int largo_actual;
               // Calcular maxima opcion
               if (flag_level) {
                  largo_actual = actual->subcontenido->largo+1;
               }
               else if (flag_level == 0) {
                  largo_actual = canciones->largo+1;
               }

               // Si opcion fue correcta
               if (dig_accn > 0 && dig_accn < largo_actual) {
                  actn_status->status = 1;
                  i = 0;
                  // Guardar anterior
                  anterior = actual;
                  if (flag_level) {
                     actual = actual->subcontenido->inicial;
                  }
                  // Avanzar actual
                  while (i < (dig_accn-1)) {
                     actual = actual->sig;
                     i++;
                  }
                  printf("Moviendose a ");
                  printf("%s\n\n", actual->contenido);
                  // Actualizar texto de acciones
                  memset(texto_accion_actual, '\0', max_text_all);
                  if (!flag_level) {
                     strcpy(texto_accion_actual, texto_accion_volver);
                  }
                  else {
                     strcpy(texto_accion_actual, texto_accion_abrir);
                  }
                  flag_level++;
                  break;
               }
               // Cancelar
               else if (dig_accn == largo_actual) {
                  actn_status->status = 1;
                  break;
               }
               // Error
               else {
                  printf("%s\n", err);
                  actn_status->mover = 1;
               }
            }
         }
         // Abrir
         else {
            // Mostrar opciones
            printf("Opciones:\n");
            printf("%s", actual->subcontenido->str);
            unsigned int n_cancelar = actual->subcontenido->largo+1;
            printf("[%u] Cancelar\n", n_cancelar);
            // Mientras accion sea erronea
            while (1) {
               char accn_abrir[15];
               // Recibir input
               scanf("%s", accn_abrir);
               memset(accn, '\0', 15);
               printf("\n");
               char * clean_accn_abrir = strip(accn_abrir);
               int dig_accn_abrir = atoi(clean_accn_abrir);
               // Opcion correcta
               if (dig_accn_abrir > 0 && dig_accn_abrir < n_cancelar) {
                  actn_status->status = 1;
                  // Avanzar a cancion
                  i = 0;
                  nodo * aux_abrir = actual->subcontenido->inicial;
                  while (i < dig_accn_abrir-1) {
                     aux_abrir = aux_abrir->sig;
                     i++;
                  }
                  printf("Abriendo %s\n", aux_abrir->id->song);
                  printf("\n");
                  // Armar tag en pantalla
                  printf("Titulo: %s\n", aux_abrir->id->song);
                  printf("Artista: %s\n", aux_abrir->id->artist);
                  printf("Album: %s\n", aux_abrir->id->album);
                  printf("Año: %s\n", aux_abrir->id->year);
                  printf("Genero: %s\n", aux_abrir->id->genre);
                  printf("\n");
                  break;
               }
               // Cancelar
               else if (dig_accn_abrir == n_cancelar) {
                  actn_status->status = 1;
                  break;
               }
               // Accion erronea
               else { printf("%s\n", err); }
            }
         }
      }
      // Salir en nivel 3
      else if (!strncmp(clean_accn, "5", 1) && flag_level>0) {
         printf("Saliendo del programa\n");
         // Liberar memoria
         free(texto_accion_inicial);
         free(texto_accion_volver);
         free(texto_accion_abrir);
         free(texto_accion_actual);
         free(actn_status);
         destroyAdy(canciones, 0);
         destroyAdyStr(alternativas, 1);
         exit(0);
      }

      // No entro a ningun comando
      else {
         actn_status->status = 0;
      }
   }
}