#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (comparador == NULL)
		return NULL;

	abb_t *abb = malloc(sizeof(abb_t));
	if (abb == NULL)
		return NULL;

	abb->nodo_raiz = NULL;
	abb->comparador = comparador;
	abb->tamanio = 0;

	return abb;
}


/*
 * Se recibe un puntero a un elemento genérico de cualquier tipo de dato
 *
 * Se crea nodo hoja, reservando memoria, cuyo elemento es el enviado a la 
 * función. Se devuelve ese nodo hoja.
 */
nodo_abb_t *crear_nodo_hoja(void *elemento)
{
	nodo_abb_t *nodo_hoja = malloc(sizeof(nodo_abb_t));
	if (nodo_hoja == NULL)
		return NULL;

	nodo_hoja->elemento = elemento;
	nodo_hoja->izquierda = NULL;
	nodo_hoja->derecha = NULL;

	return nodo_hoja;
}


/*
 * Se recibe un puntero a un nodo raiz, un comparador y un puntero a un
 * elemento genérico de cualquier tipo de dato
 * 
 * Se inserta un nodo dentro del arbol, usando recursividad.
 */
nodo_abb_t *abb_insertar_recursivo(nodo_abb_t *raiz, abb_comparador comparador, 
				   void *elemento_a_insertar)
{
	if (raiz == NULL)
		return crear_nodo_hoja(elemento_a_insertar);

	int comparacion = comparador(elemento_a_insertar, raiz->elemento);
	if (comparacion <= 0)
		raiz->izquierda = abb_insertar_recursivo(raiz->izquierda, 
					comparador, elemento_a_insertar);
	else 
		raiz->derecha = abb_insertar_recursivo(raiz->derecha, 
				    comparador, elemento_a_insertar);

	return raiz;
}


abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	arbol->nodo_raiz = abb_insertar_recursivo(arbol->nodo_raiz, 
						  arbol->comparador, elemento);

	arbol->tamanio++;
	return arbol;
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL || abb_vacio(arbol))
		return NULL;

	return NULL;
}


/*
 * Se recibe un puntero a un nodo raiz, un comparador y un puntero a un
 * elemento genérico de cualquier tipo de dato
 * 
 * Se inserta busca un elemento dentro del arbol, usando recursividad.
 */
void *abb_buscar_recursivo(nodo_abb_t *raiz, abb_comparador comparador, 
			   void *elemento_a_buscar)
{
	if (raiz == NULL)
		return NULL;
		
	int comparacion = comparador(elemento_a_buscar, raiz->elemento);
	if (comparacion == 0)
		return raiz->elemento;
	if (comparacion < 0)
		return abb_buscar_recursivo(raiz->izquierda, comparador,
					    elemento_a_buscar);

	return abb_buscar_recursivo(raiz->derecha, comparador, 
				    elemento_a_buscar);
}


void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	return abb_buscar_recursivo(arbol->nodo_raiz, arbol->comparador, 
				    elemento);
}


bool abb_vacio(abb_t *arbol)
{
	if (arbol == NULL || arbol->tamanio == 0)
		return true;

	return false;
}


size_t abb_tamanio(abb_t *arbol)
{
	if (arbol == NULL)
		return 0;

	return arbol->tamanio;
}


void abb_destruir(abb_t *arbol)
{
	if (arbol == NULL)
		return;

	free(arbol);
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;

	free(arbol);
}


size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL)
		return 0;

	return 0;
}


size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL)
		return 0;

	return 0;
}
