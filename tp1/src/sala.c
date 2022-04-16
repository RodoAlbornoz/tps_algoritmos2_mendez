#include "estructuras.h"
#include "sala.h"
#include "objeto.h"
#include "interaccion.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LARGO_MAX_LINEA 1024


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
		struct objeto **bloque_objeto = realloc(*ref_vector_objetos, (unsigned) ((*cantidad_objetos)+1) * sizeof(struct objeto));
		if (bloque_objeto == NULL) {
			fclose(archivo_objetos);
			return -1;
		}

		struct objeto *objeto_sala = objeto_crear_desde_string(linea_objetos);
		if (objeto_sala == NULL) {
			free(bloque_objeto);
			fclose(archivo_objetos);
			return -1;
		}

		bloque_objeto[*cantidad_objetos] = objeto_sala;
		(*cantidad_objetos)++;
		*ref_vector_objetos = bloque_objeto;

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
		struct interaccion **bloque_interaccion = realloc(*ref_vector_interacciones, (unsigned) ((*cantidad_interacciones)+1) * sizeof(struct interaccion));
		if (bloque_interaccion == NULL) {
			fclose(archivo_interacciones);
			return -1;
		}

		struct interaccion *interaccion_sala = interaccion_crear_desde_string(linea_interacciones);
		if (interaccion_sala == NULL) {
			free(bloque_interaccion);
			fclose(archivo_interacciones);
			return -1;
		}

		bloque_interaccion[*cantidad_interacciones] = interaccion_sala;
		(*cantidad_interacciones)++;
		*ref_vector_interacciones = bloque_interaccion;

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

	sala->cantidad_objetos = 0;
	sala->cantidad_interacciones = 0;

	sala->objetos = malloc(sizeof(struct objeto*));
	sala->interacciones = malloc(sizeof(struct interaccion*));
        if (sala->objetos == NULL || sala->interacciones == NULL) {
		sala_destruir(sala);
                return NULL;
	}

	if ((lectura_archivo_objetos(objetos, &(sala->objetos), &(sala->cantidad_objetos)) == -1) ||
	   (lectura_archivo_interacciones(interacciones, &(sala->interacciones), &(sala->cantidad_interacciones)) == -1) ||
	   (sala->cantidad_objetos == 0) || (sala->cantidad_interacciones == 0)) {
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

	return vector_nombres;
}


bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, const char *objeto1,
				const char *objeto2)
{
	if (sala == NULL || verbo == NULL || objeto1 == NULL || objeto2 == NULL)
		return false;

	for (int i = 0; i < sala->cantidad_interacciones; i++) {
		if ((strcmp(objeto1, sala->interacciones[i]->objeto) == 0) && 
		   (strcmp(objeto2, sala->interacciones[i]->objeto_parametro) == 0) && 
		   (strcmp(verbo, sala->interacciones[i]->verbo) == 0))
			return true;
	}
	return false;
}


void sala_destruir(sala_t *sala)
{
	if (sala == NULL)
		return;

	for (int i = 0; i < sala->cantidad_objetos; i++)
		free(sala->objetos[i]); 

	for (int j = 0; j < sala->cantidad_interacciones; j++)
		free(sala->interacciones[j]);

	if (sala->objetos != NULL)
		free(sala->objetos);

	if (sala->interacciones != NULL)
		free(sala->interacciones);

	free(sala);
}