#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

#include <stdbool.h>

#include "hash.h"
#include "lista.h"
#include "sala.h"

struct sala {
	hash_t *objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *interacciones;
	bool escapado;
};

/*
 * Se recibe un puntero a sala
 *
 * Se devuelve la cantidad de objetos en la sala
 */
size_t cantidad_objetos(sala_t *sala);


/*
 * Se recibe un puntero a sala
 *
 * Se devuelve la cantidad de interacciones posibles en la sala
 */
size_t cantidad_interacciones(sala_t *sala);


/*
 * Se recibe un puntero a la sala y un nombre
 *
 * Se retorna si la sala contiene un objeto cuyo nombre es igual al
 * enviado a la funcion
 */
bool sala_contiene_objeto(sala_t *sala, const char *nombre);


#endif /* __AUXILIAR_H__ */
