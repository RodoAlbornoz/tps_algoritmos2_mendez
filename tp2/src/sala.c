#include "estructuras.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interaccion.h"
#include "objeto.h"
#include "TDAs/lista.h"
#include "TDAs/hash.h"

#define LARGO_MAX_LINEA 1024

struct sala {
	hash_t *objetos;
	lista_t *interacciones;
	bool escapado;
};

/*
 * PRE: Se recibe el path al archivo de texto objetos, la referencia a objetos->sala, y la referencia a la cantidad de objetos
 * POST: Se devuelve un status sobre cómo se proceso la lectura del archivo (-1 es porque algo falló)
 */
int lectura_archivo_objetos(const char *objetos, struct objeto ***ref_vector_objetos, int* cantidad_objetos)
{
	FILE *archivo_objetos = fopen(objetos, "r");
	if(!archivo_objetos)
		return -1;

	char linea_objetos[LARGO_MAX_LINEA];
	char *leida_objetos = fgets(linea_objetos, LARGO_MAX_LINEA, archivo_objetos);

	while (leida_objetos) {
		// ARREGLAR DESDE ACA
		struct objeto **bloque_objeto = realloc(*ref_vector_objetos, (unsigned) ((*cantidad_objetos)+1) * sizeof(struct objeto));
		if (bloque_objeto == NULL) {
			fclose(archivo_objetos);
			return -1;
		}
		// HASTA ACA

		struct objeto *objeto_sala = objeto_crear_desde_string(linea_objetos);
		if (objeto_sala == NULL) {
			free(bloque_objeto);
			fclose(archivo_objetos);
			return -1;
		}

		// ARREGLAR DESDE ACA
		bloque_objeto[*cantidad_objetos] = objeto_sala;
		(*cantidad_objetos)++;
		*ref_vector_objetos = bloque_objeto;
		// HASTA ACA

		leida_objetos = fgets(linea_objetos, LARGO_MAX_LINEA, archivo_objetos);
	}

	fclose(archivo_objetos);
	return 0;
}


/*
 * PRE: Se recibe el path al archivo de texto interacciones, la referencia a objetos->interacciones, y la referencia a la cantidad de interacciones
 * POST: Se devuelve un status sobre cómo se proceso la lectura del archivo (-1 es porque algo falló)
 */
int lectura_archivo_interacciones(const char *interacciones, struct interaccion ***ref_vector_interacciones, int* cantidad_interacciones)
{
	FILE *archivo_interacciones = fopen(interacciones, "r");
	if(!archivo_interacciones)
		return -1;

	char linea_interacciones[LARGO_MAX_LINEA];
	char *leida_interacciones = fgets(linea_interacciones, LARGO_MAX_LINEA, archivo_interacciones);

	while (leida_interacciones) {
		// ARREGLAR DESDE ACA
		struct interaccion **bloque_interaccion = realloc(*ref_vector_interacciones, (unsigned) ((*cantidad_interacciones)+1) * sizeof(struct interaccion));
		if (bloque_interaccion == NULL) {
			fclose(archivo_interacciones);
			return -1;
		}
		// HASTA ACA

		struct interaccion *interaccion_sala = interaccion_crear_desde_string(linea_interacciones);
		if (interaccion_sala == NULL) {
			free(bloque_interaccion);
			fclose(archivo_interacciones);
			return -1;
		}

		// ARREGLAR DESDE ACA
		bloque_interaccion[*cantidad_interacciones] = interaccion_sala;
		(*cantidad_interacciones)++;
		*ref_vector_interacciones = bloque_interaccion;
		// HASTA ACA

		leida_interacciones = fgets(linea_interacciones, LARGO_MAX_LINEA, archivo_interacciones);
	}

	fclose(archivo_interacciones);
	return 0;
}


sala_t *sala_crear_desde_archivos(const char *objetos, const char *interacciones)
{
	sala_t *sala = malloc(sizeof(struct sala));
	if (sala == NULL)
		return NULL;

	sala->escapado = false;
	sala->objetos = hash_crear(10); // POR QUÉ 10?
	sala->interacciones = lista_crear();
	if (sala->objetos == NULL || sala->interacciones == NULL) {
		sala_destruir(sala);
		return NULL;
	}

	int status_objetos = lectura_archivo_objetos(objetos, 
						     &(sala->objetos));
	int status_interacciones = lectura_archivo_interacciones(interacciones, 
						&(sala->interacciones));
	size_t cantidad_objetos = hash_cantidad(sala->objetos);
	size_t cantidad_interacciones = lista_tamanio(sala->interacciones);

	if (status_objetos == -1 || status_interacciones == -1 || 
	    cantidad_objetos == 0 || cantidad_interacciones == 0) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}


char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	// ARREGLAR DESDE ACA
	char **vector_nombres = malloc((unsigned) sala->cantidad_objetos * sizeof(char *));
	if (vector_nombres == NULL) {
		free(sala);
		if (cantidad != NULL)
			*cantidad = -1; 
		return NULL;
	}

	for (int i = 0; i < sala->cantidad_objetos; i++)
		vector_nombres[i] = sala->objetos[i]->nombre;

	if (cantidad != NULL)
		*cantidad = sala->cantidad_objetos;
	// HASTA ACA

	return vector_nombres;
}


/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente conocidos por el jugador en la sala de escape.
 * No incluye los objetos poseidos por el jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{

}


/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente en posesión del jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{

}


/*
 * Hace que un objeto conocido y asible pase a estar en posesión del jugador.
 *
 * Devuelve true si pudo agarrar el objeto o false en caso de error (por ejemplo
 * el objeto no existe o existe pero no es asible o si dicho objeto ya está en
 * posesión del jugador).
 */
bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{

}


/*
 * Obtiene la descripción de un objeto conocido o en posesión del usuario.
 *
 * Devuelve NULL en caso de error.
 */
char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{

}


/*
 * Ejecuta una o mas interacciones en la sala de escape. Cuando una interacción
 * tenga un mensaje para mostrar por pantalla, se invocará la función
 * mostrar_mensaje (si no es NULL) con el mensaje a mostrar, el tipo de acción que representa el
 * mensaje y un puntero auxiliar del usuario.
 *
 * Devuelve la cantidad de interacciones que pudo ejecutar o 0 en caso de error.
 *
 */
int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux);
{

}


bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	if (sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL)
		return false;

	// ARREGLAR DESDE ACA
	for (int i = 0; i < sala->cantidad_interacciones; i++) {
		if ((strcmp(objeto1, sala->interacciones[i]->objeto) == 0) && 
		   (strcmp(objeto2, sala->interacciones[i]->objeto_parametro) == 0) && 
		   (strcmp(verbo, sala->interacciones[i]->verbo) == 0))
			return true;
	}
	// HASTA ACA

	return false;
}


/*
 * Devuelve true si se pudo escapar de la sala. False en caso contrario o si no existe la sala.
 */
bool sala_escape_exitoso(sala_t *sala)
{
	if (sala == NULL)
		return false;

	return sala->escapado;
}


void sala_destruir(sala_t *sala)
{
	if (sala == NULL)
		return;

	// ARREGLAR DESDE ACA
	for (int i = 0; i < sala->cantidad_objetos; i++)
		free(sala->objetos[i]); 

	for (int j = 0; j < sala->cantidad_interacciones; j++)
		free(sala->interacciones[j]);

	if (sala->objetos != NULL)
		free(sala->objetos);

	if (sala->interacciones != NULL)
		free(sala->interacciones);
	// HASTA ACA

	free(sala);
}