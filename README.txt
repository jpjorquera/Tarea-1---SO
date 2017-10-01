Para correr se de compilar y correr con:
make
make run

Es requisito que la música sea mueva dentro de la carpeta "biblioteca" para el correcto funcionamiento,
se incluyó a la carpeta vacía para lo antes dicho.

El programa reconoce sólo id3v1, por lo que es posible que algunas canciones no sean organizadas y
queden simplemente dentro de biblioteca.

Mientras corre el programa se debe ingresar "si" o "no" para organizar la biblioteca y luego navegar
usando los números que se muestran en pantalla

El main se encuentra en src/organize.c
En general se distribuyó en funciones:
en ./include se encuentran los headers
en ./src los .c, en donde:
dir.c 			Maneja el movimiento entre directorios
estructuras.c 	Maneja las listas enlazadas que fueron utilizadas 
				para resolver el problema e incluidas en estructuras.h
id.c 			Trabaja con los archivos de música para el id3v1
organize.c 		Main

