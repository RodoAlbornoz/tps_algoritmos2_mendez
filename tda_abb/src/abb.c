#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;

	abb_t *abb = malloc(sizeof(abb_t));
	if (abb == NULL) {
		free(abb);
		return NULL;
	}

	abb->nodo_raiz = NULL;
	abb->comparador = comparador;
	abb->tamanio = 0;

	return abb;
}


/*
 *
 *
 */
abb_t *insertar_en_arbol(abb_t *arbol, void *elemento)
{
	arbol->nodo_raiz = malloc(sizeof(nodo_abb_t));
	if (arbol->nodo_raiz == NULL) {
		free(arbol->nodo_raiz);
		free(arbol);
		return NULL;
	}

	arbol->nodo_raiz->elemento = elemento;
	arbol->nodo_raiz->izquierda = NULL;
	arbol->nodo_raiz->derecha = NULL;

	arbol->tamanio++;
	return arbol;
}


abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		free(arbol);
		return NULL;
	}

	if (arbol->nodo_raiz == NULL)
		return insertar_en_arbol(arbol, elemento);

	if (arbol->comparador(elemento, arbol->nodo_raiz->elemento) > 0)
		arbol->nodo_raiz = arbol->nodo_raiz->derecha;
	else if (arbol->comparador(elemento, arbol->nodo_raiz->elemento) < 0)
		arbol->nodo_raiz = arbol->nodo_raiz->izquierda;
//	else 

	return abb_insertar(arbol, elemento);
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		free(arbol);
		return NULL;
	}

	if (abb_vacio(arbol))
		return NULL;

	return NULL;
}


void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL) {
		free(arbol);
		return NULL;
	}

	if (abb_vacio(arbol))
		return NULL;

	return NULL;
}


bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL) {
		free(arbol);
		return true;
	}

	if (arbol->tamanio == 0)
		return true;

	return false;
}


size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL) {
		free(arbol);
		return 0;
	}

	return arbol->tamanio;
}


void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL) {
		free(arbol);
		return;
	}

	free(arbol);
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL) {
		free(arbol);
		return;
	}

	free(arbol);
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL) {
		free(arbol);
		return 0;
	}

	return 0;
}


size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL) {
		free(arbol);
		return 0;
	}

	return 0;
}
