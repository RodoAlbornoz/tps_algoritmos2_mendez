#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SENTENCIA 50
#define MAX_COMANDO 30


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
	printf("\nSOBRE COMANDOS\n");
	printf("*Ayuda: Brinda información sobre cada comando y el formato de las interacciones.\n");
	printf("*Agarrar objeto: Posee un objeto (Tip: Para interacciones entre 2 objetos, tenés que poseer el primero).\n");
	printf("*Describir objeto: Da la descripción de un objeto. Esto podría ayudarte con las acciones posibles sobre el mismo ;)\n");
	printf("*Informacion conocida: Permite saber cuáles objetos se conocen y cuáles se poseen actualmente.\n");
	printf("*Salir: Termina el juego.\n\n");

	printf("TIPS\n");
	printf("a. Para agarrar un objeto, al menos debes conocerlo y no poseerlo ya.\n");
	printf("b. Para describir un objeto, necesitas conocerlo o poseerlo.\n\n");

	printf("INTERACCIONES\n");
	printf("Si tiene un objeto, deben tener el formato: verbo objeto1.");
	printf(" Ejemplo: Examinar habitación.\n");
	printf("Si tiene 2, deben tener el formato: verbo objeto1 objeto2.");
	printf(" Ejemplo: Usar llave cajon\n");
}


void imprimir_informacion_conocida(sala_t *sala)
{
	int cantidad = 0;
	char **objetos = sala_obtener_nombre_objetos(sala, &cantidad);
	if (objetos == NULL) {
		printf("Error al obtener los nombres de los objetos de la sala.");
		return;
	}

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

	printf("\nLos objetos de la sala son: \n");
	for (int i = 0; i < cantidad; i++)
		printf("%i. %s\n", i + 1, objetos[i]);

	printf("\nLos objetos que conoces son: \n");
	for (int i = 0; i < cantidad_conocidos; i++)
		printf("%i. %s\n", i + 1, conocidos[i]);

	printf("\nLos objetos que posees son: \n");
	for (int i = 0; i < cantidad_poseidos; i++)
		printf("%i. %s\n", i + 1, poseidos[i]);

	free(objetos);
	free(conocidos);
	free(poseidos);
}


/*
 * Se recibe un mensaje, el tipo de accion y un puntero auxiliar
 *
 * Se imprime el mensaje asociado a una interaccion una vez ejecutada
 */
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


/*
 * Se reciben las palabras del comando insertado en el juego
 *
 * Se retorna cuántas palabras ingresó el jugador (Si no ingresó alguna, se toma como string vacio)
 */
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
	bool tip_ayuda = false;

        if (fgets(comando, MAX_COMANDO, stdin) == NULL) {
		printf("Error en lectura de comando. Volvé a intentarlo.\n");
		return;
	}

        sscanf(comando, "%s %s %s\n", primer_palabra, segunda_palabra, tercer_palabra);
	int cantidad_de_palabras = cantidad_palabras(primer_palabra, segunda_palabra, tercer_palabra);

	int ejecuciones = sala_ejecutar_interaccion(sala, primer_palabra, segunda_palabra, tercer_palabra, imprimir_mensaje, NULL); // SEGURO NO ES NULL

	if (cantidad_de_palabras == 1) {
		if (comando_es_ayuda(primer_palabra))
			imprimir_ayuda();
		
		else if(comando_es_salir(primer_palabra))
			*salir = true; 	
		
		else 
			tip_ayuda = true;

	} else if (cantidad_de_palabras == 2) {
		if (comando_es_agarrar(primer_palabra, segunda_palabra)) {
			if (sala_agarrar_objeto(sala, segunda_palabra))
				printf("Ahora posees: %s\n", segunda_palabra);
			else 
				printf("No puedo agarrar ese objeto. No existe, no lo conozco, no lo poseo o no es asible.\n");
		
		} else if (comando_es_describir(primer_palabra, segunda_palabra)) {
			char *descripcion = sala_describir_objeto(sala, segunda_palabra);
			if (descripcion != NULL)
				printf("Descripcion objeto: %s\n", descripcion);
			else 
				printf("No existe el objeto, no lo conozco o no lo poseo.\n");
		
		} else if (comando_es_informacion_conocida(primer_palabra, segunda_palabra))
			imprimir_informacion_conocida(sala);
		
		else if (ejecuciones == 0)
			tip_ayuda = true;

	} else if (cantidad_de_palabras == 0 || (cantidad_de_palabras >= 3 && 
		   !sala_es_interaccion_valida(sala, primer_palabra, segunda_palabra, tercer_palabra))) {
		tip_ayuda = true;
	}

	if (tip_ayuda) {
		printf("\nComando inválido.\n");
		printf("Tip: Escribi <ayuda> para conocer el formato de las interacciones o el significado de cada comando\n");
	}
}


/*
 * Se recibe la cantidad de argumentos recibidos al ejecutar el programa
 *
 * Se retorna si la cantidad de argumentos es inválida o no
 */
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
		printf("Error al crear la sala de escape. Por favor verificá que los archivos existan o sean correctos.\n");
		return -1;
	}

	imprimir_pantalla_de_inicio();

	int cantidad_acciones = 0;
	bool salir = false;
	while (!sala_escape_exitoso(sala)) {
		cantidad_acciones++;
		imprimir_comandos();
		evaluar_comando(&salir, sala);

		printf("*--------------------------------------*");

		if (salir) {
			printf("\nSaliendo del juego. ¡Gracias por jugar! :D\n");
			return -1;
		}	
	}

	printf("\n¡Pudiste escapar! Y te tomó %i intentos\n", cantidad_acciones);
	sala_destruir(sala);

	return 0;
}