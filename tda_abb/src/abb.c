#include "abb.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#define SEGUIR_RECORRIENDO 1
#define DEJAR_DE_RECORRER 0


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
 * Se crea un nodo hoja, reservando memoria, cuyo elemento es el enviado a la 
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


/*
 * Se recibe un puntero a un nodo raiz, y un doble puntero a un nodo, que es el
 * que se va a eliminar del arbol
 *
 * Dentro del arbol, se busca el nodo que es el predecesor inorden del padre
 * del nodo enviado a la funcion
 */
nodo_abb_t *buscar_predecesor_inorden(nodo_abb_t *raiz, nodo_abb_t **extraido)
{
	if (raiz->derecha == NULL) {
		*extraido = raiz;
		return raiz->izquierda;
	}
		
	raiz->derecha = buscar_predecesor_inorden(raiz->derecha, extraido);
	return raiz;
}


/*
 * Se recibe un puntero a un nodo raiz y un doble puntero a un elemento 
 * genérico que contiene al elemento que se va a quitar del arbol
 *
 * Se elimina el nodo que contiene el elemento a quitar (Segun si tiene o no
 * hijos)
 */
nodo_abb_t *eliminar_nodo(nodo_abb_t *raiz, void **elemento_a_quitar)
{
	nodo_abb_t *nodo_derecho = raiz->derecha;
	nodo_abb_t *nodo_izquierda = raiz->izquierda;
	*elemento_a_quitar = raiz->elemento;

	if (nodo_derecho != NULL && nodo_izquierda != NULL) {
		nodo_abb_t *extraido = NULL;
		raiz->izquierda = buscar_predecesor_inorden(raiz->izquierda, 
							    &extraido);
		raiz->elemento = extraido->elemento;
		free(extraido);
		return raiz;
	}
		
	free(raiz);
	if (nodo_derecho != NULL)
		return nodo_derecho;
	return nodo_izquierda;
}


/*
 * Se recibe un puntero a un nodo raiz, un comparador, un puntero a un elemento
 * genérico de cualquier tipo de dato y un doble puntero a un elemento genérico
 * que contiene al elemento que se va a quitar del arbol
 *
 * Se busca el nodo que contiene el elemento a quitar para borrarlo, usando
 * recursividad.
 */
nodo_abb_t *abb_quitar_recursivo(nodo_abb_t *raiz, abb_comparador comparador, 
			   void *elemento, void **elemento_a_quitar)
{
	if (raiz == NULL)
		return NULL;

	int comparacion = comparador(elemento, raiz->elemento);
	if (comparacion == 0)
		return eliminar_nodo(raiz, elemento_a_quitar);
	else if (comparacion < 0)
		raiz->izquierda = abb_quitar_recursivo(raiz->izquierda, 
			comparador, elemento, elemento_a_quitar);
		
	raiz->derecha = abb_quitar_recursivo(raiz->derecha,
			comparador, elemento, elemento_a_quitar);

	return raiz;
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	void *elemento_a_eliminar = NULL;

	arbol->nodo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, 
			arbol->comparador, elemento, &elemento_a_eliminar);

	if (elemento_a_eliminar != NULL)
		arbol->tamanio--;

	return elemento_a_eliminar;
}


/*
 * Se recibe un puntero a un nodo raiz, un comparador y un puntero a un
 * elemento genérico de cualquier tipo de dato
 * 
 * Se busca un elemento dentro del arbol, usando recursividad.
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

	abb_destruir_todo(arbol, NULL);
}


/*
 * Se recibe el puntero a la raiz de un arbol y un puntero a una funcion
 *
 * Se destruyen los nodos, el arbol y sus elementos (Si la funcion destructora
 * no es NULL), usando recursividad
 */
void abb_destruir_todo_recursivo(nodo_abb_t *raiz, void (*destructor)(void *))
{
	if (raiz == NULL)
		return;

	abb_destruir_todo_recursivo(raiz->izquierda, destructor);
	abb_destruir_todo_recursivo(raiz->derecha, destructor);
	
	if (destructor != NULL)
		destructor(raiz->elemento);
	free(raiz);
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;

	abb_destruir_todo_recursivo(arbol->nodo_raiz, destructor);
	free(arbol);
}

//////////////////////////////////////////////////////////////////////////// REVISAR
/*
 *
 *
 */
nodo_abb_t *recorrer_inorden(nodo_abb_t *raiz, 
bool (*funcion)(void *, void *), void *aux, size_t *cantidad_invocaciones, 
int *status_recorrido)
{
	if (raiz == NULL || *status_recorrido == DEJAR_DE_RECORRER)
		return raiz;

	raiz->izquierda = recorrer_inorden(raiz->izquierda, funcion, aux, 
				cantidad_invocaciones, status_recorrido);

	if (*status_recorrido == SEGUIR_RECORRIENDO) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*status_recorrido = DEJAR_DE_RECORRER;
			return raiz;
		}
	}

	raiz->derecha = recorrer_inorden(raiz->derecha, funcion, aux, 
				cantidad_invocaciones, status_recorrido); 

	return raiz;
}


/*
 *
 *
 */
nodo_abb_t *recorrer_postorden(nodo_abb_t *raiz,
bool (*funcion)(void *, void *), void *aux, size_t *cantidad_invocaciones, 
int *status_recorrido)
{
	if (raiz == NULL || *status_recorrido == DEJAR_DE_RECORRER)
		return raiz;

	raiz->izquierda = recorrer_postorden(raiz->izquierda, funcion, aux,
				cantidad_invocaciones, status_recorrido);
	raiz->derecha = recorrer_postorden(raiz->derecha, funcion, aux,
				cantidad_invocaciones, status_recorrido);

	if (*status_recorrido == SEGUIR_RECORRIENDO) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*status_recorrido = DEJAR_DE_RECORRER;
			return raiz;
		}
	}

	return raiz;
}


/*
 *
 *
 */
nodo_abb_t *recorrer_preorden(nodo_abb_t *raiz, 
bool (*funcion)(void *, void *), void *aux, size_t *cantidad_invocaciones, 
int *status_recorrido)
{
	if (raiz == NULL || *status_recorrido == DEJAR_DE_RECORRER)
		return raiz;

	if (*status_recorrido == SEGUIR_RECORRIENDO) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*status_recorrido = DEJAR_DE_RECORRER;
			return raiz;
		}
	}

	raiz->izquierda = recorrer_preorden(raiz->izquierda, funcion, aux,
			cantidad_invocaciones, status_recorrido);
	raiz->derecha = recorrer_preorden(raiz->derecha, funcion, aux,
			cantidad_invocaciones, status_recorrido);

	return raiz;
}



size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{	// CORREGIR: RECORREN ELEMENTOS DE MAS AL NO CUMPLIRSE LA FUNCION
	if (arbol == NULL || funcion == NULL)
		return 0;
	
	size_t cantidad_invocaciones = 0;
	int status_recorrido = SEGUIR_RECORRIENDO;

	if (recorrido == POSTORDEN)
		arbol->nodo_raiz = recorrer_postorden(arbol->nodo_raiz, 
		funcion, aux, &cantidad_invocaciones, &status_recorrido);
	else if (recorrido == INORDEN)
		arbol->nodo_raiz = recorrer_inorden(arbol->nodo_raiz, funcion,
				aux, &cantidad_invocaciones, &status_recorrido);
	else 
		arbol->nodo_raiz = recorrer_preorden(arbol->nodo_raiz, funcion,
				aux, &cantidad_invocaciones, &status_recorrido);

	return cantidad_invocaciones;
}


/*
 *
 *
 */
nodo_abb_t *guardar_elementos_postorden(nodo_abb_t *raiz, size_t tamanio_max, 
				   size_t *cantidad_almacenados, void ***array)
{
	if (raiz == NULL)
		return raiz;

	raiz->izquierda = guardar_elementos_postorden(raiz->izquierda, 
				tamanio_max, cantidad_almacenados, array);
	raiz->derecha = guardar_elementos_postorden(raiz->derecha, 
				tamanio_max, cantidad_almacenados, array);

	if (*cantidad_almacenados == tamanio_max)
		return raiz;
	*array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;

	return raiz;
}


/*
 *
 *
 */
nodo_abb_t *guardar_elementos_inorden(nodo_abb_t *raiz, size_t tamanio_max, 
				 size_t *cantidad_almacenados, void ***array)
{
	if (raiz == NULL)
		return raiz;

	raiz->izquierda = guardar_elementos_inorden(raiz->izquierda, 
				tamanio_max, cantidad_almacenados, array);

	if (*cantidad_almacenados == tamanio_max)
		return raiz;
	*array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;

	raiz->derecha = guardar_elementos_inorden(raiz->derecha, 
				tamanio_max, cantidad_almacenados, array);

	return raiz;
}


/*
 *
 *
 */
nodo_abb_t *guardar_elementos_preorden(nodo_abb_t *raiz, size_t tamanio_max, 
				  size_t *cantidad_almacenados, void ***array)
{
	if (raiz == NULL)
		return raiz;

	if (*cantidad_almacenados == tamanio_max)
		return raiz;
	*array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;

	raiz->izquierda = guardar_elementos_preorden(raiz->izquierda, 
				tamanio_max, cantidad_almacenados, array);

	raiz->derecha = guardar_elementos_preorden(raiz->derecha, 
				tamanio_max, cantidad_almacenados, array);

	return raiz;
}


size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || array == NULL)
		return 0;

	size_t cantidad_almacenados = 0;

	if (recorrido == POSTORDEN)
		arbol->nodo_raiz = guardar_elementos_preorden(arbol->nodo_raiz, 
				tamanio_array, &cantidad_almacenados, &array);
	else if (recorrido == INORDEN)
		arbol->nodo_raiz = guardar_elementos_inorden(arbol->nodo_raiz, 
				tamanio_array, &cantidad_almacenados, &array);
	else 
		arbol->nodo_raiz = guardar_elementos_postorden(arbol->
		nodo_raiz, tamanio_array, &cantidad_almacenados, &array);

	return cantidad_almacenados;
}
//////////////////////////////////////////////////////////////////////////// REVISAR