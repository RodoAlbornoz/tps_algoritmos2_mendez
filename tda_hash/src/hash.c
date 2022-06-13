#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LIMITE_FACTOR_DE_CARGA 0.75

typedef struct par {
	char *clave;
	void *valor;
} par_t;

struct hash {
	lista_t **tabla;
	size_t capacidad;
	size_t almacenados;
};


hash_t *hash_crear(size_t capacidad)
{
	struct hash *hash = malloc(sizeof(struct hash));
	if (hash == NULL)
		return NULL;

	hash->capacidad = capacidad < 3? 3 : capacidad;

	hash->tabla = malloc(hash->capacidad * sizeof(lista_t *));
	if (hash->tabla == NULL) {
		free(hash);
		return NULL;
	}

	for (int i = 0; i < hash->capacidad; i++)
		hash->tabla[i] = NULL;

	hash->almacenados = 0;

	return hash;
}


/*
 * Se recibe una clave como un string
 *
 * Se devuelve un entero igual a la suma de los valores en ascii
 * de cada caracter del string
 */
size_t funcion_hash(const char *clave) {

	size_t suma_valores_ascii = 0;
	for (int i = 0; i < strlen(clave); i++)
		suma_valores_ascii += (size_t) clave[i];

	return suma_valores_ascii;
}


/*
 * Se recibe un puntero a un par clave-valor y un puntero a una clave
 *
 * Se retorna un booleano que dice si la clave del par y la clave del segundo
 * parámetro no son iguales o si lo son
 */
bool claves_no_iguales(void *par_clave_valor, void *clave)
{
	par_t *par = par_clave_valor;	
	char **clave_hash = clave;
	return strcmp(par->clave, *clave_hash) != 0;
}


char *duplicar_string(const char *s)
{
	if (!s)
		return NULL;

	char *p = malloc(strlen(s) + 1);
	if (!p)
		return NULL;

	strcpy(p, s);
	return p;
}


par_t *crear_par(const char *clave, void *elemento)
{
	par_t *par = malloc(sizeof(par_t));
	if (par == NULL)
		return NULL;

 	par->clave = duplicar_string(clave);
	par->valor = elemento;

	return par;
}


hash_t *rehashear(hash_t *hash)
{
	hash_t *nuevo_hash = hash_crear(hash->capacidad * 2);
	
	//Recorro hash y reinserto las claves en nuevo_hash
	nodo_t *nodo_aux = NULL;
	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;
		for (int j = 0; j < lista_tamanio(hash->tabla[i]); j++) {
			par_t *par = nodo_aux->elemento;
			hash_insertar(nuevo_hash, par->clave, par->valor, NULL);
			nodo_aux = nodo_aux->siguiente;
		}
	}
	
	hash_t temporal;
	temporal = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = temporal;
	hash_destruir(nuevo_hash);

	return hash;
}


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	float factor_de_carga = 0;
	for (int i = 0; i < hash->capacidad; i++) {
		factor_de_carga = ((float) lista_tamanio(hash->tabla[i])) / ((float) hash->capacidad);
		if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA)
			hash = rehashear(hash);
	}

	par_t *par = crear_par(clave, elemento);

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;
	if (hash->tabla[posicion_tabla] == NULL)
		hash->tabla[posicion_tabla] = lista_crear();

	if (!hash_contiene(hash, clave)) {
		if (anterior != NULL)
			*anterior = NULL;

		hash->tabla[posicion_tabla] = lista_insertar(
					hash->tabla[posicion_tabla], par);
		hash->almacenados++;
		return hash;
	}

	if (anterior != NULL)
		*anterior = hash_obtener(hash, clave);

	nodo_t *nodo_actual = hash->tabla[posicion_tabla]->nodo_inicio;
	int i = 0;
	bool nodo_encontrado = false;
	
	while (i < lista_tamanio(hash->tabla[posicion_tabla]) && !nodo_encontrado) {
		if (!claves_no_iguales(nodo_actual->elemento, &clave))
			nodo_encontrado = true;
		else 
			nodo_actual = nodo_actual->siguiente;
		i++;
	};

	nodo_actual->elemento = par;

	return hash;
}


void *hash_quitar(hash_t *hash, const char *clave)
{	
	if (hash == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	if (!hash_contiene(hash, clave))
		return NULL;

	void *elemento_a_eliminar = hash_obtener(hash, clave);
	size_t posicion_a_eliminar = lista_con_cada_elemento(hash->tabla[posicion_tabla], claves_no_iguales, &clave) - 1;
	
	par_t *par_a_eliminar = lista_quitar_de_posicion(hash->tabla[posicion_tabla], posicion_a_eliminar);
	free(par_a_eliminar);

	hash->almacenados--;
	return elemento_a_eliminar;
}


/*
 * Se recibe un puntero a un par clave-valor y un puntero a una clave
 *
 * Se retorna el resultado de la comparacion entre la clave del par y la clave
 * del segundo parámetro, donde 0 significa que son iguales, y cualquier otra 
 * cosa significa que son distintas
 */
int comparar_claves(void *par_clave_valor, void *clave)
{
	par_t *par = par_clave_valor;
	char **clave_hash = clave;
	return strcmp(par->clave, *clave_hash);
}


void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	par_t *par = lista_buscar_elemento(hash->tabla[posicion_tabla], 
	       				   comparar_claves, &clave);

	if (par == NULL)
		return NULL;
	return par->valor;
}


bool hash_contiene(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return false;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	return lista_buscar_elemento(hash->tabla[posicion_tabla], 
	    			     comparar_claves, &clave) != NULL;
}


size_t hash_cantidad(hash_t *hash)
{
	if (hash == NULL)
		return 0;

	return hash->almacenados;
}


void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
}


void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (hash == NULL)
		return;

	for (int i = 0; i < hash->capacidad; i++)
		lista_destruir_todo(hash->tabla[i], destructor);

	free(hash->tabla);
	free(hash);
}


/*
 * Recorre cada una de las claves almacenadas en la tabla de hash e invoca a la
 * función f, pasandole como parámetros la clave, el valor asociado a la clave y
 * el puntero auxiliar.
 *
 * Mientras que queden mas claves o la funcion retorne true, la
 * iteración continúa. Cuando no quedan mas claves o la función
 * devuelve false, la iteración se corta y la función principal
 * retorna.
 *
 * Devuelve la cantidad de claves totales iteradas (la cantidad de
 * veces que fue invocada la función) o 0 en caso de error.
 *
 */

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (hash == NULL)
		return 0;

	par_t *par;
	nodo_t *nodo_aux;
	int j;
	bool seguir_iterando = true;
	size_t cantidad_iterados = 0;

	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL) {
			nodo_aux = hash->tabla[i]->nodo_inicio;

			j = 0;
			while (j < lista_tamanio(hash->tabla[i]) && seguir_iterando) {
				par = nodo_aux->elemento;
				if (!f(par->clave, par->valor, aux))
					seguir_iterando = false;

				cantidad_iterados++;
			}
			
			seguir_iterando = true;
		}
	}

	return cantidad_iterados;
}