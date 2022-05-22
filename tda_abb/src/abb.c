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
 * del nodo enviado a la funcion y se lo trae
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
 * Se recibe un puntero a un nodo raiz
 *
 * Se elimina el nodo que contiene el elemento a quitar (Segun su cantidad
 * de hijos)
 */
nodo_abb_t *eliminar_nodo(nodo_abb_t *raiz)
{
	nodo_abb_t *nodo_derecho = raiz->derecha;
	nodo_abb_t *nodo_izquierda = raiz->izquierda;

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
 * genérico de cualquier tipo de dato, un doble puntero a un elemento genérico
 * que contiene al elemento que se va a quitar del arbol y un puntero a un 
 * booleano que dice si el elemento se pudo eliminar
 *
 * Se busca el nodo que contiene el elemento a quitar para borrarlo, usando
 * recursividad.
 */
nodo_abb_t *abb_quitar_recursivo(nodo_abb_t *raiz, abb_comparador comparador, 
	void *elemento, void **elemento_a_quitar, bool *se_pudo_eliminar)
{
	if (raiz == NULL)
		return NULL;

	int comparacion = comparador(elemento, raiz->elemento);
	if (comparacion == 0) {
		*elemento_a_quitar = raiz->elemento;
		*se_pudo_eliminar = true;
		return eliminar_nodo(raiz);
	} else if (comparacion < 0) {
		raiz->izquierda = abb_quitar_recursivo(raiz->izquierda, 
		comparador, elemento, elemento_a_quitar, se_pudo_eliminar);
	} else {
		raiz->derecha = abb_quitar_recursivo(raiz->derecha,
		comparador, elemento, elemento_a_quitar, se_pudo_eliminar);
	}

	return raiz;
}



void *abb_quitar(abb_t *arbol, void *elemento)
{
	if (arbol == NULL)
		return NULL;

	void *elemento_a_eliminar = NULL;
	bool se_pudo_eliminar = false;

	arbol->nodo_raiz = abb_quitar_recursivo(arbol->nodo_raiz, 
	arbol->comparador, elemento, &elemento_a_eliminar, &se_pudo_eliminar);

	if (se_pudo_eliminar)
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
	else if (comparacion < 0)
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
	if (arbol == NULL || abb_tamanio(arbol) == 0)
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


/*
 * Se recibe un puntero a un nodo raiz, el puntero a la función que se debe
 * cumplir para seguir recorriendo, el auxiliar que es el 2do parámetro de la
 * funcion, un puntero a la cantidad de invocaciones realizadas y otro a una
 * variable que dice si hay que seguir recorriendo o no
 *
 * Se recorre el ABB en forma inorden hasta que no se cumpla más la función,
 * sumando uno a la cantidad de invocaciones cada vez que se esté parado sobre
 * un nodo
 */
void recorrer_inorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), 
	void *aux, size_t *cantidad_invocaciones, bool *seguir_recorriendo)
{
	if (raiz == NULL || !*seguir_recorriendo)
		return;

	recorrer_inorden(raiz->izquierda, funcion, aux, 
				cantidad_invocaciones, seguir_recorriendo);

	if (*seguir_recorriendo) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*seguir_recorriendo = false;
			return;
		}
	}

	recorrer_inorden(raiz->derecha, funcion, aux, 
				cantidad_invocaciones, seguir_recorriendo); 
}


/*
 * Se recibe un puntero a un nodo raiz, el puntero a la función que se debe
 * cumplir para seguir recorriendo, el auxiliar que es el 2do parámetro de la
 * funcion, un puntero a la cantidad de invocaciones realizadas y otro a una
 * variable que dice si hay que seguir recorriendo o no
 *
 * Se recorre el ABB en forma postorden, hasta que no se cumpla más la función,
 * sumando uno a la cantidad de invocaciones cada vez que se esté parado sobre
 * un nodo
 */
void recorrer_postorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), 
	void *aux, size_t *cantidad_invocaciones, bool *seguir_recorriendo)
{
	if (raiz == NULL || !*seguir_recorriendo)
		return;

	recorrer_postorden(raiz->izquierda, funcion, aux,
				cantidad_invocaciones, seguir_recorriendo);
	recorrer_postorden(raiz->derecha, funcion, aux,
				cantidad_invocaciones, seguir_recorriendo);

	if (*seguir_recorriendo) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*seguir_recorriendo = false;
			return;
		}
	}
}


/*
 * Se recibe un puntero a un nodo raiz, el puntero a la función que se debe
 * cumplir para seguir recorriendo, el auxiliar que es el 2do parámetro de la
 * funcion, un puntero a la cantidad de invocaciones realizadas y otro a una
 * variable que dice si hay que seguir recorriendo o no
 *
 * Se recorre el ABB en forma preorden, hasta que no se cumpla más la función,
 * sumando uno a la cantidad de invocaciones cada vez que se esté parado sobre
 * un nodo
 */
void recorrer_preorden(nodo_abb_t *raiz, bool (*funcion)(void *, void *), 
	void *aux, size_t *cantidad_invocaciones, bool *seguir_recorriendo)
{
	if (raiz == NULL || !*seguir_recorriendo)
		return;

	if (*seguir_recorriendo) {
		(*cantidad_invocaciones)++;
		if (!funcion(raiz->elemento, aux)) {
			*seguir_recorriendo = false;
			return;
		}
	}

	recorrer_preorden(raiz->izquierda, funcion, aux,
			cantidad_invocaciones, seguir_recorriendo);
	recorrer_preorden(raiz->derecha, funcion, aux,
			cantidad_invocaciones, seguir_recorriendo);
}



size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	if (arbol == NULL || funcion == NULL)
		return 0;
	
	size_t cantidad_invocaciones = 0;
	bool seguir_recorriendo = true;

	if (recorrido == POSTORDEN)
		recorrer_postorden(arbol->nodo_raiz, funcion, aux, 
				&cantidad_invocaciones, &seguir_recorriendo);
	else if (recorrido == INORDEN)
		recorrer_inorden(arbol->nodo_raiz, funcion, aux, 
				 &cantidad_invocaciones, &seguir_recorriendo);
	else 
		recorrer_preorden(arbol->nodo_raiz, funcion, aux,
				  &cantidad_invocaciones, &seguir_recorriendo);

	return cantidad_invocaciones;
}


/*
 * Se recibe un puntero a un nodo raiz, el tamaño máximo del array, un puntero 
 * a la cantidad de elementos que se almacenaron por el momento en el array, y
 * el puntero al array de punteros.
 *
 * Se recorre el ABB en forma postorden, guardando cada elemento leido en el 
 * array hasta superar la capacidad del arreglo o recorrer todo el ABB.
 */
void guardar_elementos_postorden(nodo_abb_t *raiz, size_t tamanio_max_array, 
				 size_t *cantidad_almacenados, void **array)
{
	if (raiz == NULL)
		return;

	guardar_elementos_postorden(raiz->izquierda, tamanio_max_array, 
				    cantidad_almacenados, array);
	guardar_elementos_postorden(raiz->derecha, tamanio_max_array, 
				    cantidad_almacenados, array);

	if (*cantidad_almacenados == tamanio_max_array)
		return;
	array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;
}


/*
 * Se recibe un puntero a un nodo raiz, el tamaño máximo del array, un puntero 
 * a la cantidad de elementos que se almacenaron por el momento en el array, y
 * el puntero al array de punteros.
 *
 * Se recorre el ABB en forma inorden, guardando cada elemento leido en el 
 * array hasta superar la capacidad del arreglo o recorrer todo el ABB.
 */
void guardar_elementos_inorden(nodo_abb_t *raiz, size_t tamanio_max_array, 
			       size_t *cantidad_almacenados, void **array)
{
	if (raiz == NULL)
		return;

	guardar_elementos_inorden(raiz->izquierda, tamanio_max_array, 
				  cantidad_almacenados, array);

	if (*cantidad_almacenados == tamanio_max_array)
		return;
	array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;

	guardar_elementos_inorden(raiz->derecha, tamanio_max_array, 
				  cantidad_almacenados, array);
}


/*
 * Se recibe un puntero a un nodo raiz, el tamaño máximo del array, un puntero 
 * a la cantidad de elementos que se almacenaron por el momento en el array, y
 * el puntero al array de punteros.
 *
 * Se recorre el ABB en forma preorden, guardando cada elemento leido en el 
 * array hasta superar la capacidad del arreglo o recorrer todo el ABB.
 */
void guardar_elementos_preorden(nodo_abb_t *raiz, size_t tamanio_max_array, 
				size_t *cantidad_almacenados, void **array)
{
	if (raiz == NULL)
		return;

	if (*cantidad_almacenados == tamanio_max_array)
		return;
	array[*cantidad_almacenados] = raiz->elemento;
	(*cantidad_almacenados)++;

	guardar_elementos_preorden(raiz->izquierda, tamanio_max_array, 
				   cantidad_almacenados, array);

	guardar_elementos_preorden(raiz->derecha, tamanio_max_array, 
				   cantidad_almacenados, array);
}


size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	if (arbol == NULL || array == NULL)
		return 0;

	size_t cantidad_almacenados = 0;

	if (recorrido == POSTORDEN)
		guardar_elementos_postorden(arbol->nodo_raiz, tamanio_array, 
					    &cantidad_almacenados, array);
	else if (recorrido == INORDEN)
		guardar_elementos_inorden(arbol->nodo_raiz, tamanio_array, 
					  &cantidad_almacenados, array);
	else 
		guardar_elementos_preorden(arbol->nodo_raiz, tamanio_array, 
					   &cantidad_almacenados, array);

	return cantidad_almacenados;
}