#include "objeto.h"
#include "estructuras.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ASIBLE 6
#define FORMATO_LECTURA_OBJETOS "%[^;];%[^;];%[^\n]"

/*
 * Se recibe un string que solo puede ser true o false, que dice si el objeto 
 * es asible o no.
 *
 * Se retorna un booleano que dice si el objeto es asible (true) o no (false)
 */
bool objeto_es_asible(char asible[MAX_ASIBLE])
{
	return strcmp(asible, "true") == 0;
}


struct objeto *objeto_crear_desde_string(const char *string)
{
	if (string == NULL)
		return NULL;

	char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
	char asible[MAX_ASIBLE];

	int elementos_leidos = sscanf(string, FORMATO_LECTURA_OBJETOS, nombre, 
				      descripcion, asible);
	if (elementos_leidos != 3)
		return NULL;

	struct objeto *objeto = malloc(sizeof(struct objeto));
	if (objeto == NULL)
		return NULL;

	strcpy(objeto->nombre, nombre);
	strcpy(objeto->descripcion, descripcion);

	if((strcmp(asible, "true") != 0) && (strcmp(asible, "false") != 0)) {
		free(objeto);
		return NULL;
	}
	objeto->es_asible = objeto_es_asible(asible);

	return objeto;
}