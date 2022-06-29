#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void imprimir_pantalla_de_inicio()
{
	printf("¡Bienvenido al juego de Escape Pokemon jugador! :D\n");
	printf("Te despertas en una sala desconocida y no sabes qué hacer.\n");
	printf("Tu objetivo es escapar de esta sala interactuando con los \n\
		objetos de la misma\n");
	printf("Empezas con un primer objeto y a partir de él tenes que \n\
		buscar la forma de abrir la puerta.\n");
}


void imprimir_comandos()
{
	printf("1. Ayuda.\n");
	printf("2. Agarrar <objeto>.\n");
	printf("3. Describir <objeto>.\n");
	printf("4. Información conocida (Imprime la información conocida de la sala).");
	printf("5. Salir.\n");
	system("clear");
}


void imprimir_ayuda()
{
	printf("INTERACCIONES \n"); 
	printf("Acciones posibles:\n"); // Imprimir segundo campo de archivo de interacciones
	printf("Para interacciones de 1 objeto, deben tener el formato: \n"); // Formato de interacciones
	printf("Para interacciones de 2 objetos, las interacciones deben tener el formato: \n"); // Formato de interacciones
}


void imprimir_informacion_conocida()
{
	printf("\n");
	printf("\n");
	printf("\n");
}


void verificar_accion()
{
	// if (2 objetos y no se posee el primero)
	// printf("Accion inválida.");
	// Mostrar accion mensaje luego de completada
	switch (cuarto campo de archivo de interacciones) {
		case 'm':
			//mostrar mensaje
		break;

		case 'e':
			// eliminar objeto
		break;

		case 'd':
			// descubrir objeto
		break;

		case 'g':
			// descubrir objeto
		break;

		case 'r':
			// reemplazar objeto
		break;
	}
}


void agarrar_objeto(sala_t *sala)
{

}


void describir_objeto(sala_t *sala)
{

}


void evaluar_comando(bool *salir, sala_t *sala)
{
	char *comando;
	char *accion;
	char *aux;
	scanf("Ingrese comando: %s", comando);

	sscanf(comando, "%s %s", accion, aux);

	if (strcmp(accion, "ayuda") == 0 || strcmp(accion, "Ayuda") == 0) {
		imprimir_ayuda();

	} else if (strcmp(accion, "agarrar") == 0 || 
		   strcmp(accion, "Agarrar") == 0) {
		agarrar_objeto(sala);

	} else if (strcmp(accion, "describir") == 0 || 
		   strcmp(accion, "Describir") == 0) {
		describir_objeto(sala);

	} else if ((strcmp(accion, "Informacion") == 0 || 
		    strcmp(accion, "informacion") == 0) &&
		   (strcmp(aux, "conocida") == 0 ||
		    strcmp(aux, "Conocida") == 0)) {
		imprimir_informacion_conocida();

	} else if (/*Es algun comando del archivo de interacciones*/) {
		verificar_accion();

	} else if (strcmp(accion, "salir") == 0 || 
		   strcmp(accion, "Salir") == 0){
		*salir = true; 

	} else {
		printf("El comando que insertaste NO es correcto.\n");
		printf("Por favor, ingresa un comando valido o escribí \"ayuda\" para conocer los comandos posibles.\n");
	}
}


bool argumentos_invalidos(int argc)
{
	if (argc != 3) {
		printf("Cantidad de argumentos incorrecta.\n");
		printf("Tip: Ingresá \"./ejecutable <archivo_objetos> <archivo_interacciones>\"\n");
		return true;
	}

	return false;
}


int main(int argc, char *argv[])
{
	if (argumentos_invalidos(argc))
		return -1;

	sala_t *sala = sala_crear_desde_archivos("objetos.txt", "interacciones.txt");
	if (sala == NULL) {
		printf("Error al crear la sala de escape.\n");
		return -1;
	}

	imprimir_pantalla_de_inicio();
	bool salir = false;
	while (!sala_escape_exitoso(sala) && !salir) {
		imprimir_comandos();
		evaluar_comando(&salir, sala);

		if (salir) {
			printf("Saliendo de la sala. ¡Gracias por jugar! :D");
			return -1;
		}	
	}

	// Destruir vectores y otras cosas
	sala_destruir(sala);

	return 0;
}