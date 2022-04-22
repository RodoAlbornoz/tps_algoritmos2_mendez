#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{/*
	lista_t *pila = malloc(sizeof(lista_t));
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	pila->nodo_inicio = NULL;
	pila->nodo_fin = NULL;
	pila->cantidad = 0;

	return lista_crear();*/
	return NULL;
}


pila_t *pila_apilar(pila_t *pila, void *elemento)
{/*
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) {
		free(nuevo_nodo);
		free(pila);
		return NULL;
	}

	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = pila->nodo_inicio;
	pila->nodo_inicio = nuevo_nodo;

	pila->cantidad++;

	return pila;*/
	return NULL;
}


void *pila_desapilar(pila_t *pila)
{
	return NULL;
}


void *pila_tope(pila_t *pila)
{	/*
	if (pila == NULL) {
		free(pila);
		return NULL;
	}

	return pila->nodo_inicio;*/
	return NULL;
}


size_t pila_tamanio(pila_t *pila)
{	/*
	if (pila == NULL) {
		free(pila);
		return 0;
	}

	return pila->cantidad;*/
	return 0;
}


bool pila_vacia(pila_t *pila)
{	/*
	if (pila == NULL) {
		free(pila);
		return true;
	}

	if (pila->cantidad == 0)
		return true;

	return false;*/
	return false;
}


void pila_destruir(pila_t *pila)
{

}