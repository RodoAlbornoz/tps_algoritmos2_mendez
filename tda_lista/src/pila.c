#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{	
	return (pila_t *) lista_crear();
}


pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	return (pila_t *) lista_insertar((lista_t *) pila, elemento);
}


void *pila_desapilar(pila_t *pila)
{
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	return lista_quitar((lista_t *) pila);
}


void *pila_tope(pila_t *pila)
{	
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	return lista_ultimo((lista_t *) pila);
}


size_t pila_tamanio(pila_t *pila)
{	
	if (pila == NULL) {
		free(pila);
		return 0;
	}

	return lista_tamanio((lista_t *) pila);
}


bool pila_vacia(pila_t *pila)
{	
	if (pila == NULL) {
		free(pila);
		return true;
	}

	return lista_vacia((lista_t *) pila);
}


void pila_destruir(pila_t *pila)
{
	if (pila == NULL) {
		free(pila);
		return;
	}

	lista_destruir((lista_t *) pila);
}