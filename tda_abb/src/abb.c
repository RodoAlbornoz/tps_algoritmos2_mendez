#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

#include <stdio.h>

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


/*
struct abb *extraer_mas_izquierdo(struct abb *raiz, struct abb **extraido)
{
	if (raiz-izquierda == NULL) {
		*extraido = raiz;
		return raiz->derecha;
	}
		
	raiz->izquierda = extraer_mas_izquierd(raiz->izquierda, extraido);
	return raiz;	
}
*/


/*
 *
 *
 */
void *abb_quitar_recursivo(nodo_abb_t *raiz, abb_comparador comparador, 
			   void *elemento_a_quitar)
{
	if (raiz == NULL)
		return NULL;

	int comparacion = comparador(elemento_a_quitar, raiz->elemento);

	if (comparacion == 0) {
		/*
		nodo_abb_t *nodo_derecho = raiz->derecha;
		nodo_abb_t *nodo_izquierda = raiz->izquierda;

		if (nodo_derecho != NULL && nodo_izquierda != NULL) {
			struct abb *extraido = NULL;
			raiz->derecha = extraer_mas_izquierdo(raiz->derecha, &extraido);
			raiz->elemento = extraido->elemento;
			return raiz;
		}

		if (nodo_derecho != NULL)
			return nodo_derecho;
		
		return nodo_izquierda;
		
		*/
		nodo_abb_t *nodo_aux = raiz;
		void *elemento_eliminado = raiz->elemento;
		raiz = NULL;
		free(nodo_aux);
		return elemento_eliminado;
	} else if (comparacion < 0)
		elemento_a_quitar = abb_quitar_recursivo(raiz->izquierda, 
						comparador, elemento_a_quitar);
	
	elemento_a_quitar = abb_quitar_recursivo(raiz->derecha, 
				    comparador, elemento_a_quitar);

	return elemento_a_quitar;
}


void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	return abb_quitar_recursivo(arbol->nodo_raiz, arbol->comparador, 
				    elemento);
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
	// VER SI SE PUEDE MEJORAR USANDO ABB_QUITAR
	free(raiz);
}


void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol == NULL)
		return;

	abb_destruir_todo_recursivo(arbol->nodo_raiz, destructor);
	free(arbol);
}


/*
 * Se recibe el puntero a una raiz, un puntero a funcion que devuelve un
 * booleano, un puntero a un elemento genérico de cualquier tipo de dato y
 * un puntero a un numero que cuenta las veces que se invocó a la función
 *
 * Se recorre el arbol en forma inorden y se devuelve la cantidad de veces
 * que se invocó a la función
 */
size_t recorrer_inorden(nodo_abb_t* raiz, bool (*funcion)(void *, void *), 
		void *aux, size_t *cantidad_invocaciones)
{
	if (raiz == NULL || !funcion(raiz->elemento, aux))
		return *cantidad_invocaciones;

	*cantidad_invocaciones = recorrer_inorden(raiz->izquierda, funcion, 
				aux, cantidad_invocaciones);

	(*cantidad_invocaciones)++;
	printf("%i \n", *(int *) raiz->elemento);
	if (!funcion(raiz->elemento, aux))
		return *cantidad_invocaciones;

	*cantidad_invocaciones = recorrer_inorden(raiz->derecha, funcion, aux, 
					cantidad_invocaciones); 

	return *cantidad_invocaciones;
}


size_t recorrer_postorden(nodo_abb_t* raiz, bool (*funcion)(void *, void *), 
		void *aux, size_t *cantidad_invocaciones)
{
	if (raiz == NULL)
		return *cantidad_invocaciones;

	*cantidad_invocaciones = recorrer_postorden(raiz->izquierda, funcion, 
				aux, cantidad_invocaciones);
	*cantidad_invocaciones = recorrer_postorden(raiz->derecha, funcion, 
				aux, cantidad_invocaciones);

	(*cantidad_invocaciones)++;
	if (!funcion(raiz->elemento, aux)) 
		return *cantidad_invocaciones;

	return *cantidad_invocaciones;
}


/*
 * Se recibe el puntero a una raiz, un puntero a funcion que devuelve un
 * booleano, un puntero a un elemento genérico de cualquier tipo de dato y
 * un puntero a un numero que cuenta las veces que se invocó a la función
 *
 * Se recorre el arbol en forma preorden y se devuelve la cantidad de veces
 * que se invocó a la función
 */
size_t recorrer_preorden(nodo_abb_t* raiz, bool (*funcion)(void *, void *), 
			 void *aux, size_t *cantidad_invocaciones)
{
	if (raiz == NULL)
		return *cantidad_invocaciones;

	(*cantidad_invocaciones)++;
	if (!funcion(raiz->elemento, aux))
		return *cantidad_invocaciones;

	*cantidad_invocaciones = recorrer_preorden(raiz->izquierda, funcion, 
						  aux, cantidad_invocaciones);
	*cantidad_invocaciones = recorrer_preorden(raiz->derecha, funcion, aux, 
						  cantidad_invocaciones);

	return *cantidad_invocaciones;
}


/*
 * Invoca la funcion con cada elemento almacenado en el mismo
 * como primer parámetro. El puntero aux se pasa como segundo parámetro a la
 * función. Si la función devuelve false, se finaliza el recorrido aun si quedan
 * elementos por recorrer. Si devuelve true se sigue recorriendo mientras queden
 * elementos.

 * Devuelve la cantidad de veces que fue invocada la función.
*/
size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || funcion == NULL)
		return 0;

	size_t cantidad_invocaciones = 0;

	if (recorrido == POSTORDEN)
		return recorrer_postorden(arbol->nodo_raiz, funcion, aux, 
					  &cantidad_invocaciones);
	else if (recorrido == INORDEN)
		return recorrer_inorden(arbol->nodo_raiz, funcion, aux, 
					&cantidad_invocaciones);
	
	return recorrer_preorden(arbol->nodo_raiz, funcion, aux, 
				 &cantidad_invocaciones);
}


/**
 * Recorre el arbol según el recorrido especificado y va almacenando los
 * elementos en el array hasta completar el recorrido o quedarse sin espacio en
 * el array.
 *
 * El array tiene un tamaño maximo especificado por tamanio_array.
 *
 * Devuelve la cantidad de elementos que fueron almacenados exitosamente en el
 * array.
 */
size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || array == NULL)
		return 0;

	return 0;
}
