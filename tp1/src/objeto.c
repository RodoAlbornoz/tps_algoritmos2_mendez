#include "objeto.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_ASIBLE 6

/*
 * PRE: Se recibe un string que solo puede ser true o false, que dice si el objeto es asible o no.
 * POST: Se retorna un bolleano que dice si el objeto es asible (true) o no (false)
 */
bool objeto_es_asible(char asible[MAX_ASIBLE])
{
	if (strcmp(asible, "true") == 0)
		return true;
		
	return false;
}


struct objeto *objeto_crear_desde_string(const char *string)
{
	if (string == NULL)
		return NULL;

	char nombre[MAX_NOMBRE];
	char descripcion[MAX_TEXTO];
	char asible[MAX_ASIBLE];

	int elementos_leidos = sscanf(string, "%[^;];%[^;];%[^\n]", nombre, descripcion, asible);
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