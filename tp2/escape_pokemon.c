#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCIA 50
#define MAX_COMANDO 20

void imprimir_pantalla_de_inicio()
{
	printf("¡Bienvenido al juego de Escape Pokemon jugador :D!\n");
	printf("Te despertas en una sala desconocida. Tu objetivo es escapar de la misma interactuando con sus objetos.\n");
	printf("Empezas conociendo un objeto y a partir de él tenes que buscar la forma de abrir la puerta y salir.\n");
	printf("Las acciones no son conocidas, pero tenés que ir averiguandolas ;)\n");
}


void imprimir_comandos()
{
	printf("\nINGRESÁ UN COMANDO\n");
	printf("1. Ayuda.\n");
	printf("2. Agarrar <objeto>.\n");
	printf("3. Describir <objeto>.\n");
	printf("4. Información conocida (Imprime la información conocida de la sala).\n");
	printf("5. Salir.\n");
}


void imprimir_ayuda()
{
	printf("\na. Recordá que, para agarrar un objeto, debes al menos conocerlo, y no podees poseerlo ya.\n");
	printf("b. Para describir un objeto, necesitas conocerlo o poseerlo.\n");

	printf("INTERACCIONES\n");
	printf("Si tiene un objeto, deben tener el formato: accion objeto_1.\n");
	printf("Ejemplo: Examinar habitación.");
	printf("Si tiene 2, deben tener el formato: \n"); // COMPLETAR
	printf("Ejemplo: Usar \n");
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

// CORREGIR ESTE
void imprimir_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}


bool comando_es_ayuda(char primer_palabra[MAX_COMANDO])
{
	return (strcmp(primer_palabra, "ayuda") == 0 || strcmp(primer_palabra, "Ayuda") == 0 || 
		strcmp(primer_palabra, " ayuda") == 0 || strcmp(primer_palabra, " Ayuda") == 0 ||
		strcmp(primer_palabra, "ayuda ") == 0 || strcmp(primer_palabra, "Ayuda ") == 0);
}


bool comando_es_agarrar(char accion[MAX_COMANDO], char objeto[MAX_COMANDO])
{
	return ((strcmp(accion, "agarrar") == 0 || strcmp(accion, "Agarrar") == 0 || 
		strcmp(accion, " agarrar") == 0 || strcmp(accion, " Agarrar") == 0));	
}


bool comando_es_describir(char accion[MAX_COMANDO], char objeto[MAX_COMANDO])
{
	return ((strcmp(accion, "describir") == 0 || strcmp(accion, "Describir") == 0 || 
		 strcmp(accion, " describir") == 0 || strcmp(accion, " Describir") == 0));	
}


bool comando_es_informacion_conocida(char palabra1[MAX_COMANDO], char palabra2[MAX_COMANDO])
{
	return ((strcmp(palabra1, "informacion") == 0 || strcmp(palabra1, "Informacion") == 0 || 
		 strcmp(palabra1, " informacion") == 0 || strcmp(palabra1, " Informacion") == 0 ||
		 strcmp(palabra1, "información") == 0 || strcmp(palabra1, "Información") == 0) &&
		(strcmp(palabra2, "conocida") == 0 || strcmp(palabra2, "Conocida") == 0 || 
		 strcmp(palabra2, "conocida ") == 0 || strcmp(palabra2, "Conocida ") == 0));
}


bool comando_es_salir(char primer_palabra[MAX_COMANDO])
{
	return (strcmp(primer_palabra, "salir") == 0 || strcmp(primer_palabra, "Salir") == 0 || 
		strcmp(primer_palabra, " salir") == 0 || strcmp(primer_palabra, " Salir") == 0 ||
		strcmp(primer_palabra, "salir ") == 0 || strcmp(primer_palabra, "Salir ") == 0);
}


int cantidad_palabras(char primer_palabra[MAX_COMANDO], char segunda_palabra[MAX_COMANDO], char tercera_palabra[MAX_COMANDO]) 
{
        int cantidad = 0;

        if (strcmp(primer_palabra, "") != 0)
                cantidad++;

        if (strcmp(segunda_palabra, "") != 0)
                cantidad++;

        if (strcmp(tercera_palabra, "") != 0)
                cantidad++;

        return cantidad;
}


void evaluar_comando(bool *salir, sala_t *sala)
{
	char comando[MAX_SENTENCIA];
        char primer_palabra[MAX_COMANDO] = "";
        char segunda_palabra[MAX_COMANDO] = "";
        char tercer_palabra[MAX_COMANDO] = "";

        if (fgets(comando, MAX_COMANDO, stdin) == NULL) {
		printf("Error en lectura de comando. Volvé a intentarlo.\n");
		return;
	}

        sscanf(comando, "%s %s %s\n", primer_palabra, segunda_palabra, tercer_palabra);
	int cantidad_de_palabras = cantidad_palabras(primer_palabra, segunda_palabra, tercer_palabra);

	sala_ejecutar_interaccion(sala, primer_palabra, segunda_palabra, tercer_palabra, imprimir_mensaje, NULL); // SEGURO NO ES NULL

	if (cantidad_de_palabras == 0) {
		printf("No ingresaste nada. Por favor, ingresá al menos una palabra.\n");
		printf("Tip: Si necesitas ayuda, escribi <ayuda>\n");
	} else if (cantidad_de_palabras == 1) {
		if (comando_es_ayuda(primer_palabra))
			imprimir_ayuda(); // COMPLETAR

		else if(comando_es_salir(primer_palabra))
			*salir = true; 	

	} else if (cantidad_de_palabras == 2) {
		if (comando_es_agarrar(primer_palabra, segunda_palabra) && sala_agarrar_objeto(sala, segunda_palabra))
			printf("Ahora posees: %s\n", segunda_palabra);

		else if (comando_es_describir(primer_palabra, segunda_palabra))
			printf("%s\n", sala_describir_objeto(sala, segunda_palabra)); // ERROR

		else if (comando_es_informacion_conocida(primer_palabra, segunda_palabra))
			imprimir_informacion_conocida(sala); // ERROR

//		else if (sala_es_interaccion_valida(sala, primer_palabra, segunda_palabra, tercer_palabra))
//			sala_ejecutar_interaccion(sala, primer_palabra, segunda_palabra, tercer_palabra, imprimir_mensaje, NULL); // SEGURO NO ES NULL

//	} else if (cantidad_de_palabras == 3) {
//		if (sala_es_interaccion_valida(sala, primer_palabra, segunda_palabra, tercer_palabra))
//			sala_ejecutar_interaccion(sala, primer_palabra, segunda_palabra, tercer_palabra, imprimir_mensaje, NULL); // SEGURO NO ES NULL
	} else {
		printf("El o las palabras ingresadas NO son válidas.\n");
		printf("Por favor, ingresa un comando valido o escribí \"ayuda\"");
		printf(" para conocer el formato o significado de cada comando.\n");
	}
}


bool argumentos_invalidos(int argc)
{
	if (argc != 3) {
		printf("Cantidad de argumentos incorrecta.\n");
		printf("Tip: Ingresá \"make escape\" y luego \"./escape_pokemon <archivo_objetos> <archivo_interacciones>.\"\n");
		return true;
	}

	return false;
}


int main(int argc, char *argv[])
{
	if (argumentos_invalidos(argc))
		return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	if (sala == NULL) {
		printf("Error al crear la sala de escape. Por favor intentá de nuevo.\n");
		return -1;
	}

	imprimir_pantalla_de_inicio();

	int cantidad_acciones = 0;
	bool salir = false;
	while (!sala_escape_exitoso(sala)) {
		cantidad_acciones++;
		imprimir_comandos();
		evaluar_comando(&salir, sala);

		if (salir) {
			printf("Saliendo del juego. ¡Gracias por jugar! :D \n");
			return -1;
		}	
	}

	printf("¡Pudiste escapar! Y te tomó %i acciones", cantidad_acciones);
	sala_destruir(sala);

	return 0;
}