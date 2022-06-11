#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>


lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (lista == NULL)
		return NULL;
	
	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;
	
	return lista;
}


/*
 * Se reciben las referencias a una lista y al elemento a insertar dentro del 
 * nuevo nodo, y una variable que dice si la lista tiene elementos o no
 * Se retorna la lista con el nuevo nodo insertado
 * 
 * Si ocurre un error en medio, se retorna -1
 */
int lista_insertar_al_final(lista_t *lista, void *elemento, 
			    bool lista_es_vacia)
{
	if (lista == NULL) {
		free(lista);
		return -1;
	}

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (nuevo_nodo == NULL) {
		free(nuevo_nodo);
		free(lista);
		return -1;
	}

    	if (lista_es_vacia)
        	lista->nodo_inicio = nuevo_nodo;
    	else
        	lista->nodo_fin->siguiente = nuevo_nodo;

	nuevo_nodo->siguiente = NULL;
	nuevo_nodo->elemento = elemento;
	lista->nodo_fin = nuevo_nodo;

	return 0;
}


lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	bool lista_es_vacia = lista_vacia(lista);
	int status_insercion = lista_insertar_al_final(lista, elemento, 
						       lista_es_vacia);
	if (status_insercion == -1)
		return NULL;

	lista->cantidad++;
	return lista;
}


/*
 * Se recibe la referencia a una lista, la posicion en donde se va a insertar 
 * un elemento y el elemento a insertar
 * Se crea el elemento sobre la lista en la posicion indicada
 * 
 * Si ocurre un error en medio, se retorna -1
 */
int lista_elemento_insertado_en_posicion(lista_t *lista, size_t posicion, 
					 void *elemento)
{
	nodo_t *nodo_a_insertar = malloc(sizeof(nodo_t));
	if (nodo_a_insertar == NULL) {
		free(nodo_a_insertar);
		free(lista);
		return -1;
	}

	if (posicion == 0) {
		nodo_a_insertar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_a_insertar;
	} else {
		nodo_t *nodo_anterior = lista->nodo_inicio;
		int i = 0;

		while (i < posicion - 1) {
			nodo_anterior = nodo_anterior->siguiente;
			i++;
		}
		nodo_a_insertar->siguiente = nodo_anterior->siguiente;
		nodo_anterior->siguiente = nodo_a_insertar;
	}

	nodo_a_insertar->elemento = elemento; 

	return 0;
}


lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	int status_insercion;
	if (posicion >= lista_tamanio(lista))
		status_insercion = lista_insertar_al_final(lista, elemento, 
							   lista_vacia(lista));
	else
		status_insercion = lista_elemento_insertado_en_posicion(lista, 
							   posicion, elemento);	

	if (status_insercion == -1)
		return NULL;

	lista->cantidad++;
	return lista;
}


/*
 * Se recibe la referencia a una lista no vacia
 *
 * Se retorna el elemento del ultimo nodo de la lista, que luego es eliminado.
 */
void *ultimo_elemento_lista(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	nodo_t *nodo_anterior = lista->nodo_inicio;
	nodo_t *nodo_a_eliminar = lista->nodo_inicio;
	int i = 0;

	while (i < lista_tamanio(lista) - 1) {
		nodo_anterior = nodo_a_eliminar;
		nodo_a_eliminar = nodo_a_eliminar->siguiente;
		i++;
	}

	lista->nodo_fin = nodo_anterior;
	nodo_anterior->siguiente = NULL;

	void *elemento_eliminado_lista = nodo_a_eliminar->elemento;
	free(nodo_a_eliminar);

	lista->cantidad--;
	return elemento_eliminado_lista;
}


void *lista_quitar(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista_vacia(lista))
		return NULL;

	return ultimo_elemento_lista(lista);
}


/*
 * Se recibe la referencia a una lista y la posicion en la cual se busca el 
 * nodo en la lista
 * 
 * Elimina el nodo en la posicion enviada y devuelve el elemento de ese nodo.
 */
void *elemento_eliminado_en_posicion(lista_t *lista, size_t posicion)
{
	nodo_t *nodo_a_eliminar = lista->nodo_inicio;

	if (posicion == 0) {
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
	} else {
		nodo_t *nodo_anterior;

		int i = 0;
		while (i < posicion) {
			nodo_anterior = nodo_a_eliminar;
			nodo_a_eliminar = nodo_a_eliminar->siguiente;
			i++;
		}
		nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
	}	
			
	void *elemento_eliminado = nodo_a_eliminar->elemento;
	nodo_a_eliminar->siguiente = NULL;
	free(nodo_a_eliminar);

	lista->cantidad--;
	return elemento_eliminado;	
}


void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista_vacia(lista))
		return NULL;

	if (posicion >= lista_tamanio(lista) - 1)
		return ultimo_elemento_lista(lista);	
	
	return elemento_eliminado_en_posicion(lista, posicion);
}


void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (posicion > lista_tamanio(lista) - 1 || lista_vacia(lista))
		return NULL;

	if (posicion == lista_tamanio(lista) - 1)
		return lista_ultimo(lista);

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
	if (lista == NULL)
		return NULL;

	if (comparador == NULL)
		return NULL;

	bool encontrado = false;
	void *elemento_encontrado;
	nodo_t *nodo_aux = lista->nodo_inicio;
	int i = 0;

	while (i < lista_tamanio(lista) && !encontrado) {
		if (comparador(nodo_aux->elemento, contexto) == 0) {
			encontrado = true;
			elemento_encontrado = nodo_aux->elemento;
		} else {
			nodo_aux = nodo_aux->siguiente;
			i++;
		}
	}

	if (encontrado)
		return elemento_encontrado;

	return NULL;
}


void *lista_primero(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista_vacia(lista))
		return NULL;

	return lista->nodo_inicio->elemento;
}


void *lista_ultimo(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista_vacia(lista))
		return NULL;

	return lista->nodo_fin->elemento;
}


bool lista_vacia(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return true;
	}

	if (lista_tamanio(lista) == 0)
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
	if (lista == NULL || lista_vacia(lista)) {
		free(lista);
		return;
	}	

	while (!lista_vacia(lista))
		lista_quitar_de_posicion(lista, 0);

	free(lista);
}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (lista == NULL || lista_vacia(lista)) {
		free(lista);
		return;
	}	

	if (funcion == NULL) {
		lista_destruir(lista);
		return;
	}

	while (!lista_vacia(lista)) {
		funcion(lista->nodo_inicio->elemento);
		lista_quitar_de_posicion(lista, 0);
	}
	free(lista);
}


lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (iterador == NULL) {
		free(iterador);
		free(lista);
		return NULL;
	}

	iterador->corriente = lista->nodo_inicio;
	iterador->lista = lista;

	return iterador;
}


bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		free(iterador);
		return false;
	}

	if (lista_vacia(iterador->lista)) 
		return false;

	return iterador->corriente != NULL;
}


bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		free(iterador);
		return false;
	}

	if (lista_vacia(iterador->lista) || iterador->corriente == NULL) 
		return false;

	iterador->corriente = iterador->corriente->siguiente;

	if (iterador->corriente == NULL)
		return false;

	return true;
}


void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		free(iterador);
		return NULL;
	}

	if (lista_vacia(iterador->lista) || iterador->corriente == NULL) 
		return NULL;

	return iterador->corriente->elemento;
}


void lista_iterador_destruir(lista_iterador_t *iterador)
{
	free(iterador);
}


size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (lista == NULL) {
		free(lista);
		return 0;
	}

	if (funcion == NULL || lista_vacia(lista))
		return 0;

	nodo_t *nodo_aux = lista->nodo_inicio;
	size_t cantidad_iteradada = 0;

	bool seguir_iterando = true;
	while (cantidad_iteradada < lista_tamanio(lista) && seguir_iterando) {
		if (!funcion(nodo_aux->elemento, contexto))
			seguir_iterando = false;
		cantidad_iteradada++;
		nodo_aux = nodo_aux->siguiente;
	}

	return cantidad_iteradada;
}