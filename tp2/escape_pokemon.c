#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMANDO 50

void imprimir_pantalla_de_inicio()
{
	printf("¡Bienvenido al juego de Escape Pokemon jugador! :D\n");
	printf("Te despertas en una sala desconocida y no sabes qué hacer.\n");
	printf("Tu objetivo es escapar de esta sala interactuando con los objetos de la misma\n");
	printf("Empezas con un primer objeto y a partir de él tenes que buscar la forma de abrir la puerta y salir.\n");
}


void imprimir_comandos()
{
	printf("1. Ayuda.\n");
	printf("2. Agarrar <objeto>.\n");
	printf("3. Describir <objeto>.\n");
	printf("4. Información conocida (Imprime la información conocida de la sala).");
	printf("5. Salir.\n");
}


void imprimir_ayuda()
{
	printf("a. Recordá que, para agarrar un objeto, debes al menos conocerlo, y no podees poseerlo ya.\n");
	printf("b. Para describir un objeto, necesitas conocerlo o poseerlo.\n\n");

	printf("INTERACCIONES\n");
	printf("Acciones posibles:\n"); // Imprimir segundo campo de archivo de interacciones
	printf("Si tiene un objeto, deben tener el formato: accion objeto_1.\n");
	printf("Ejemplo: Examinar habitación.");
	printf("Si tiene 2, deben tener el formato: \n"); // COMPLETAR
	printf("Ejemplo: Usar ");
}


void imprimir_informacion_conocida(sala_t *sala)
{
	int cantidad_conocidos = 0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	if (conocidos == NULL) {
		printf("Error al obtener los nombres de los objetos conocidos.");
		return;
	}

	int cantidad_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	if (poseidos == NULL) {
		printf("Error al obtener los nombres de los objetos poseidos.");
		return;
	}

	printf("Los objetos que conoces son: \n");
	for (int i = 0; i < cantidad_conocidos; i++)
		printf("%i. %s", i, conocidos[i]);

	printf("Los objetos que posees son: \n");
	for (int i = 0; i < cantidad_poseidos; i++)
		printf("%i. %s", i, poseidos[i]);

	free(conocidos);
	free(poseidos);
}


void imprimir_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}


void evaluar_comando(bool *salir, sala_t *sala)
{
	char *comando;
	printf("Ingrese comando:");
	fgets(comando, MAX_COMANDO, stdin); 

	int cant_palabras = 0;
	char caracter = comando[0];
	if (caracter != ' ')
		cant_palabras++;

	int i = 0;
	while (caracter != '\0') {
		if (comando[i] == ' ')
			cant_palabras++;

		i++;
		caracter = comando[i];
	}

	if (strcmp(accion, "ayuda") == 0 || strcmp(accion, "Ayuda") == 0 || strcmp(accion, "1") == 0) {
		imprimir_ayuda();

	} else if (strcmp(accion, "agarrar") == 0 || 
		   strcmp(accion, "Agarrar") == 0) {
		sala_agarrar_objeto(sala, nombre);

	} else if (strcmp(accion, "describir") == 0 || 
		   strcmp(accion, "Describir") == 0) {
		sala_describir_objeto(sala, nombre);

	} else if ((strcmp(accion, "Informacion") == 0 || 
		    strcmp(accion, "informacion") == 0) &&
		   (strcmp(aux, "conocida") == 0 ||
		    strcmp(aux, "Conocida") == 0)) {
		imprimir_informacion_conocida();

	} else if (/*Es algun comando del archivo de interacciones*/) {
		sala_ejecutar_interaccion();

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
		printf("Tip: Ingresá \"make escape\"\n");
		printf("Y luego \"./escape_pokemon <archivo_objetos> <archivo_interacciones>.\"\n")
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

	int cantidad_acciones = 0;
	imprimir_pantalla_de_inicio();
	bool salir = false;
	while (!sala_escape_exitoso(sala)) {
		cantidad_acciones++;
		imprimir_comandos();
		evaluar_comando(&salir, sala);

		if (salir) {
			printf("Saliendo de la sala. ¡Gracias por jugar! :D");
			return -1;
		}	
	}

	printf("¡Pudiste escapar! Y te tomó %i acciones", cantidad_acciones);
	sala_destruir(sala);
	return 0;
}