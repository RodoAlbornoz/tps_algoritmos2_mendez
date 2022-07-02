#ifndef __AUXILIAR_H__
#define __AUXILIAR_H__

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


#endif /* __AUXILIAR_H__ */
