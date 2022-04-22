#include "lista.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>


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
 * Se reciben las referencias a una lista y al elemento a insertar dentro del nuevo nodo, y una variable que dice si la 
 * lista tiene elementos o no
 * Se retorna la lista con el nuevo nodo insertado
 * 
 * Si ocurre un error en medio (La lista, el nuevo nodo o el elemento son NULL, o no se pudo reservar memoria), 
 * se retorna -1
 */
int lista_insertar_al_final(lista_t *lista, void *elemento, bool lista_es_vacia)
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
	if (lista_es_vacia) {
		if (lista_insertar_al_final(lista, elemento, lista_es_vacia) == -1)
			return NULL;
	} else { 
		if (lista_insertar_al_final(lista, elemento, lista_es_vacia) == -1)
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

	bool lista_es_vacia = lista_vacia(lista);
	if (lista_es_vacia) {
		if (lista_insertar_al_final(lista, elemento, lista_es_vacia) == -1)
			return NULL;
	} else if (!lista_es_vacia && posicion >= lista->cantidad) {
		if (lista_insertar_al_final(lista, elemento, lista_es_vacia) == -1)
			return NULL;
	} else {
		nodo_t *nodo_a_insertar = malloc(sizeof(nodo_t));
		if (nodo_a_insertar == NULL) {
			free(nodo_a_insertar);
			free(lista);
			return NULL;
		}

		if (posicion == 0) {
			nodo_a_insertar->siguiente = lista->nodo_inicio;
			lista->nodo_inicio = nodo_a_insertar;
			nodo_a_insertar->elemento = elemento;
		} else {
			nodo_t *nodo_aux = lista->nodo_inicio;
			int i = 0;

			while (i < posicion - 1) {
				nodo_aux = nodo_aux->siguiente;
				i++;
			}
			nodo_a_insertar->siguiente = nodo_aux->siguiente; // VER POR QUÉ FUNCIONA ASÍ
			nodo_aux->siguiente = nodo_a_insertar;
			nodo_a_insertar->elemento = elemento; 
		}	
	}
	
	lista->cantidad++;
	return lista;
}


/*
 * Se recibe la referencia a una lista no vacia
 *
 * Se retorna el elemento del ultimo nodo de la lista, que luego es eliminado.
 */
void *ultimo_elemento_eliminado(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	nodo_t *nodo_aux = lista->nodo_fin;
	lista->nodo_fin = lista->nodo_inicio;
	while (lista->nodo_fin->siguiente != nodo_aux)
		lista->nodo_fin = lista->nodo_fin->siguiente;

	void *elemento_eliminado_lista = nodo_aux->elemento;
	free(nodo_aux);
	lista->nodo_fin->siguiente = NULL;

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

	lista->cantidad--;
	return ultimo_elemento_eliminado(lista);
}


void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (lista_vacia(lista))
		return NULL;

	void *elemento_eliminado;
	if (posicion >= lista->cantidad) {
		return NULL;
	} else if (posicion == 0) {
		nodo_t *nodo_a_eliminar = lista->nodo_inicio;
		elemento_eliminado = nodo_a_eliminar->elemento;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		nodo_a_eliminar->siguiente = NULL;
		free(nodo_a_eliminar);
	} else if (posicion == lista->cantidad - 1) {
		elemento_eliminado = ultimo_elemento_eliminado(lista);
	} else {
		nodo_t *nodo_a_eliminar = lista->nodo_inicio;
		nodo_t *nodo_anterior;

		int i = 0;
		while (i < posicion) {
			nodo_anterior = nodo_a_eliminar;
			nodo_a_eliminar = nodo_a_eliminar->siguiente;
			i++;
		}
		nodo_anterior->siguiente = nodo_anterior->siguiente->siguiente;
		elemento_eliminado = nodo_a_eliminar->elemento;
		nodo_a_eliminar->siguiente = NULL;
		free(nodo_a_eliminar);
	}

	lista->cantidad--;
	return elemento_eliminado;
}


void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (posicion > lista->cantidad - 1 || lista_vacia(lista))
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
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	if (comparador == NULL)
		return NULL;

	bool encontrado = false;
	void *elemento_encontrado;
	nodo_t *nodo_aux = lista->nodo_inicio;
	int i = 0;

	while (i < lista->cantidad && !encontrado) {
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
	if (lista == NULL || lista->cantidad == 0) {
		free(lista);
		return;
	}

	if (lista->cantidad == 1) {
		free(lista->nodo_inicio);
		lista->cantidad--;
	} else {
		nodo_t *nodo_aux = lista->nodo_inicio;
		while (lista->nodo_inicio != NULL) {
			lista->nodo_inicio = lista->nodo_inicio->siguiente;
			free(nodo_aux);
			nodo_aux = lista->nodo_inicio;
			lista->cantidad--;
		}
	}

	free(lista);
}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (lista == NULL || lista->cantidad == 0) {
		free(lista);
		return;
	}

	bool destructora_es_null = funcion == NULL? true : false;

	if (lista->cantidad == 1) {
		if (!destructora_es_null)
			funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->cantidad--;
	} else {
		nodo_t *nodo_aux = lista->nodo_inicio;
		while (lista->nodo_inicio != NULL) {
			if (!destructora_es_null)
				funcion(lista->nodo_inicio->elemento);
			lista->nodo_inicio = lista->nodo_inicio->siguiente;
			free(nodo_aux);
			nodo_aux = lista->nodo_inicio;
			lista->cantidad--;
		}
	}

	free(lista);
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