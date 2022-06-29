#include "estructuras.h"
#include "sala.h"
#include "interaccion.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FORMATO_LECTURA_INTERACCIONES "%[^;];%[^;];%[^;];%c:%[^:]:%[^\n]"

/*
 * Se recibe el caracter de un tipo de accion
 *
 * Se devuelve el tipo de accion que corresponde al caracter leido (Si el 
 * caracter NO corresponde a ninguna accion, la accion es inválida)
 */
enum tipo_accion accion_segun_caracter(char tipo_accion)
{
	enum tipo_accion accion_objeto;

	switch (tipo_accion) {
	case 'd':
		accion_objeto = DESCUBRIR_OBJETO;
		break;
	case 'r':
		accion_objeto = REEMPLAZAR_OBJETO;
		break;
	case 'e':
		accion_objeto = ELIMINAR_OBJETO;
		break;
	case 'm':
		accion_objeto = MOSTRAR_MENSAJE;
		break;
	case 'g':
		accion_objeto = ESCAPAR;
	default:
		accion_objeto = ACCION_INVALIDA;
		break;
	}
	
	return accion_objeto;
}


/*
 * Se recibe un string del nombre de algun objeto
 * 
 * Se devuelve un string vacio si el string del nombre es "_" (Nombre de objeto 
 * vacio) y si no, se devuelve el mismo string del nombre.
 */
const char *objeto_interaccion(char objeto[MAX_NOMBRE])
{
	if(strcmp(objeto, "_") == 0)
		return "";

	return objeto;
}


struct interaccion *interaccion_crear_desde_string(const char *string)
{
	if (string == NULL)
		return NULL;

	char objeto[MAX_NOMBRE];
	char verbo[MAX_VERBO];
	char objeto_parametro[MAX_NOMBRE];
	char tipo_de_accion;
	char objeto_accion[MAX_NOMBRE];
	char mensaje[MAX_TEXTO];

	int elementos_leidos = sscanf(string, FORMATO_LECTURA_INTERACCIONES, 
				      objeto, verbo, objeto_parametro, 
				      &tipo_de_accion, objeto_accion, mensaje);
	if (elementos_leidos != 6)
		return NULL;

	struct interaccion *interaccion = malloc(sizeof(struct interaccion));
	if (interaccion == NULL)
		return NULL;

	strcpy(interaccion->objeto, objeto);
	strcpy(interaccion->verbo, verbo);
	strcpy(interaccion->objeto_parametro, 
	       objeto_interaccion(objeto_parametro));	

	interaccion->accion.tipo = accion_segun_caracter(tipo_de_accion);
	if (interaccion->accion.tipo == ACCION_INVALIDA) {
		free(interaccion);
		return NULL;
	}

	strcpy(interaccion->accion.objeto, objeto_interaccion(objeto_accion));
	strcpy(interaccion->accion.mensaje, mensaje);

	return interaccion;
}