#include "lista.h"
#include <stddef.h>
#include <stdlib.h>


lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		free(lista);
		return NULL;
	}
	
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;
	
	return lista;
}


/*
 * Se recibe una lista sin elementos y la referencia a un elemento.
 * Se inserta el elemento a la lista, y se retorna la lista con el nuevo elemento.
 * 
 * Si hubo un error en el medio, se retorna NULL
 */
lista_t *lista_vacia_insertar_elemento(lista_t *lista, void *elemento)
{
	lista->nodo_inicio = malloc(sizeof(nodo_t));
	if (lista->nodo_inicio == NULL) {
		free(lista->nodo_inicio);
		free(lista);
		return NULL;
	}

	lista->nodo_inicio->siguiente = NULL;
	lista->nodo_inicio->elemento = elemento;
	lista->nodo_fin = lista->nodo_inicio;

	return lista;
}


lista_t *insertar_elemento_al_final(lista_t *lista, nodo_t *nuevo_nodo, void *elemento)
{
	nuevo_nodo = malloc(sizeof(nodo_t));

	if (nuevo_nodo == NULL) {
		free(nuevo_nodo);
		free(lista);
		return NULL;
	}

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = elemento;
	lista->nodo_fin = nuevo_nodo;

	return lista;
}


lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0) {
		if (insertar_elemento_al_final(lista, lista->nodo_inicio, elemento) == NULL)
			return NULL;
	} else {
		if (insertar_elemento_al_final(lista, lista->nodo_fin->siguiente, elemento) == NULL)
			return NULL;
	}

	lista->cantidad++;
	return lista;
}


lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0)
		lista_vacia_insertar_elemento(lista, elemento);
	
	if (posicion == 0) {
		nodo_t *nodo_a_insertar = malloc(sizeof(nodo_t));
		if (nodo_a_insertar == NULL) {
			free(nodo_a_insertar);
			free(lista);
			return NULL;
		}

		nodo_a_insertar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_insertar;
		nodo_a_insertar->elemento = elemento;
	}

	if (posicion > lista->cantidad) {
		lista->nodo_fin->siguiente = malloc(sizeof(nodo_t));
		if (lista->nodo_fin->siguiente == NULL) {
			free(lista->nodo_fin->siguiente);
			free(lista);
			return NULL;
		}

		lista->nodo_fin->siguiente->siguiente = NULL;
		lista->nodo_fin->siguiente->elemento = elemento;
		lista->nodo_fin = lista->nodo_fin->siguiente;
	}
	
	lista->cantidad++;
	return lista;
}


void *lista_quitar(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0)
		return NULL;

	nodo_t *nodo_aux = lista->nodo_fin;
	lista->nodo_fin = lista->nodo_inicio;
	while (lista->nodo_fin->siguiente != nodo_aux)
		lista->nodo_fin = lista->nodo_fin->siguiente;

	void *elemento_eliminado = lista->nodo_fin->siguiente->elemento;
	free(lista->nodo_fin->siguiente);
	lista->nodo_fin->siguiente = NULL;

	lista->cantidad--;
	return elemento_eliminado;
}


void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0)
		return NULL;

	if (posicion == 0) {
		nodo_t *nodo_aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		nodo_aux->siguiente = NULL;
		free(nodo_aux->siguiente);
	}
	/*
	nodo_t *nodo_inicio_aux;
	nodo_t *nodo_a_eliminar_aux;
	int i = 0;

	nodo_inicio_aux = lista->nodo_inicio;
	while (i <= posicion) {
		if (i == posicion)
			nodo_a_eliminar_aux = nodo_inicio_aux;

		nodo_inicio_aux = nodo_inicio_aux->siguiente;
		i++;
	}
	*/
	// 1. Auxiliar apunta a nodo a eliminar
	// 2. El nodo anterior al nodo a eliminar apunta al siguiente nodo al nodo a eliminar
	// 3. El siguiente elemento del auxiliar al nodo a eliminar apunta a NULL
	lista->cantidad--;
	return NULL;
}


void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (posicion > lista->cantidad - 1 || lista->cantidad == 0)
		return NULL;

	int cantidad_nodos_recorridos = 0;
	nodo_t *nodo_aux = lista->nodo_inicio;

	while (cantidad_nodos_recorridos < posicion) {
		nodo_aux = nodo_aux->siguiente;
		cantidad_nodos_recorridos++;
	}

	return nodo_aux->elemento;
}


void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}


void *lista_primero(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0)
		return NULL;

	return lista->nodo_inicio->elemento;
}


void *lista_ultimo(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista->cantidad == 0)
		return NULL;

	return lista->nodo_fin->elemento;
}


bool lista_vacia(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return true;
	}

	if (lista->cantidad == 0)
		return true;

	return false;
}


size_t lista_tamanio(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return 0;
	}

	return lista->cantidad;
}


void lista_destruir(lista_t *lista)
{

}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

}


lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}


bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}


void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}


void lista_iterador_destruir(lista_iterador_t *iterador)
{

}


size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
