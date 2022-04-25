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
	int status_insercion = lista_insertar_al_final(lista, elemento, lista_es_vacia);
	if (status_insercion == -1)
		return NULL;

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

	// 1. Lista vacia
	// 2. Se inserta al final
	// 3. Se inserta al principio
	// 4. Se inserta al medio

	bool lista_es_vacia = lista_vacia(lista);

	if (lista_vacia(lista)) {
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
void *ultimo_elemento_lista(lista_t *lista)
{
	if (lista == NULL) {
		free(lista);
		return NULL;
	}

	nodo_t *nodo_aux = lista->nodo_fin;
	
	if (lista->cantidad != 1) {
		lista->nodo_fin = lista->nodo_inicio;
		while (lista->nodo_fin->siguiente != nodo_aux)
			lista->nodo_fin = lista->nodo_fin->siguiente;
	}

	void *elemento_eliminado_lista = nodo_aux->elemento;
	free(nodo_aux);

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
 * Se recibe la referencia a una lista y la posicion a partir de la cual se busca el nodo en una lista
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
		nodo_anterior->siguiente = nodo_anterior->siguiente->siguiente;
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

	if (lista_vacia(lista) || posicion >= lista->cantidad)
		return NULL;

	if (posicion == lista_tamanio(lista) - 1)
		return ultimo_elemento_lista(lista);	
	
	return elemento_eliminado_en_posicion(lista, posicion);
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


/*
 * Se recibe la referencia a una lista, un booleano que dice si la función destructora es NULL, y la función destructora
 * de los elementos de la lista
 *
 * Se retorna si se pudo destruir la lista, y en caso afirmativo, libera todos sus nodos y sus elementos si la función
 * destructora no es NULL
 */
bool lista_se_puede_destruir (lista_t *lista, bool destructora_es_null, void (*destructora)(void *))
{
	if (lista == NULL || lista->cantidad == 0) {
		free(lista);
		return false;
	}	

	nodo_t *nodo_aux = lista->nodo_inicio;
	if (lista->cantidad == 1) {
		if (!destructora_es_null)
			destructora(lista->nodo_inicio->elemento);
		free(nodo_aux);
		lista->cantidad--;
	} else {
		while (lista->nodo_inicio != NULL) {
			if (!destructora_es_null)
				destructora(lista->nodo_inicio->elemento);
			lista->nodo_inicio = lista->nodo_inicio->siguiente;
			free(nodo_aux);
			nodo_aux = lista->nodo_inicio;
			lista->cantidad--;
		}
	}

	return true;
}


void lista_destruir(lista_t *lista)
{
	if (!lista_se_puede_destruir(lista, true, NULL))
		return;
	free(lista);
}


void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	bool destructora_es_null = false;
	if (funcion == NULL)
		destructora_es_null = true;

	if(!lista_se_puede_destruir(lista, destructora_es_null, funcion))
		return;
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

	if (iterador->lista->cantidad == 0) 
		return false;

	return iterador->corriente->siguiente != NULL;
}


bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		free(iterador);
		return false;
	}

	if (iterador->lista->cantidad == 0 || iterador->corriente->siguiente == NULL) 
		return false;

	iterador->corriente = iterador->corriente->siguiente;
	return true;
}


void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (iterador == NULL) {
		free(iterador);
		return NULL;
	}

	if (iterador->corriente == iterador->lista->nodo_fin)
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

	if (funcion == NULL || lista->cantidad == 0)
		return 0;

	nodo_t *nodo_aux = lista->nodo_inicio;
	size_t cant_elementos_iterados = 0;

	while (cant_elementos_iterados < lista->cantidad && funcion(nodo_aux->elemento, contexto)) {
		cant_elementos_iterados++;
		nodo_aux = nodo_aux->siguiente;
	}

	return cant_elementos_iterados;
}