#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// #define LIMITE_FACTOR_DE_CARGA 0.70

typedef struct par {
	char *clave;
	void *valor;
} par_t;

struct hash {
	lista_t **tabla;
	size_t capacidad;
	size_t almacenados;
};


/*
 * Se recibe un puntero a un elemento del hash (Que contiene una clave y un
 * valor) y un puntero a una clave
 *
 * Se retorna el resultado de la comparacion entre las 2 claves, donde ==0 
 * significa que son iguales, y cualquier otro resultado significa que son
 * distintos
 */
int comparar_claves(void *elemento_hash, void *clave)
{
	par_t *par = elemento_hash;
	return strcmp(par->clave, clave);
}


/*
 * Se recibe un puntero a un elemento del hash (Que contiene una clave y un
 * valor) y un puntero a una clave
 *
 * Se retorna un booleano que dice si las claves no son iguales (!= 0) o si lo
 * son (== 0)
 */
bool claves_no_iguales(void *elemento_hash, void *clave)
{
	par_t *par = elemento_hash;	
	return strcmp(par->clave, clave) != 0;
}


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


nodo_t *nodo_en_posicion(lista_t *lista, size_t posicion_nodo)
{
	size_t posicion_lista = 0;

	bool encontrado = false;
	nodo_t *nodo_aux = lista->nodo_inicio;

	while (!encontrado) {
		if (posicion_lista == posicion_nodo)
			encontrado = true;
		else
			nodo_aux = nodo_aux->siguiente;
	}

	return nodo_aux;
}


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{	
	if (hash == NULL)
		return NULL;
	/*
	float factor_de_carga = lista_tamanio(hash->tabla[i]) / hash->capacidad;
	hash->almacenados / hash->capacidad;

	if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA)
		hash = rehashear();
	*/

	int posicion_tabla = funcion_hash(clave) % hash->capacidad;
	size_t posicion_en_lista = lista_con_cada_elemento(
	hash->tabla[posicion_tabla], claves_no_iguales, &clave) - 1;

	par_t *par;
	par->clave = clave;
	par->valor = elemento;

	if (posicion_en_lista == lista_tamanio(hash->tabla[posicion_tabla])) {
		if (anterior != NULL)
			*anterior = NULL;
		return lista_insertar(hash->tabla[posicion_tabla], par);
	}

	if (anterior != NULL)
		*anterior = lista_elemento_en_posicion(
			    hash->tabla[posicion_tabla], posicion_en_lista);

	nodo_t *nodo_a_sobreescribir = nodo_en_posicion(
			hash->tabla[posicion_tabla], posicion_en_lista);
	nodo_a_sobreescribir->elemento = par;

	return hash;
}


void *hash_quitar(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;
	size_t posicion_en_lista = lista_con_cada_elemento(
	hash->tabla[posicion_tabla], claves_no_iguales, &clave) - 1;

	if (posicion_en_lista == lista_tamanio(hash->tabla[posicion_tabla]))
		return NULL;

	return lista_quitar_de_posicion(hash->tabla[posicion_tabla], 
					posicion_en_lista);
}


void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	return lista_buscar_elemento(hash->tabla[posicion_tabla], 
	       comparar_claves, &clave);
}


bool hash_contiene(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return false;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	if (lista_buscar_elemento(hash->tabla[posicion_tabla], 
	    comparar_claves, &clave) != NULL)
		return true;

	return false;
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

	for (int i = 0; i < hash_cantidad(hash); i++)
		lista_destruir_todo(hash->tabla[i], destructor); // VER SI ESTÁ BIEN

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
	return 0;
}
