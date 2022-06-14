#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
// #include <time.h>

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
 * Se devuelve un entero
 */
size_t funcion_hash(const char *clave) 
{
	size_t suma_caracteres_ascii = 0;

	for (int i = 0; i < strlen(clave); i++)
		suma_caracteres_ascii += (size_t) clave[i];
	return suma_caracteres_ascii;

//	srand((unsigned int) time(NULL));
//	return (size_t) rand() % (strlen(clave) + 1);
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


/*
 * Se recibe un string
 *
 * Se retorna una copia del mismo
 */
char *string_duplicado(const char *s)
{
	if (!s)
		return NULL;

	char *p = malloc(strlen(s) + 1);
	if (!p)
		return NULL;

	strcpy(p, s);
	return p;
}


/*
 * Se recibe un string y un puntero a un valor
 *
 * Se retorna un par clave-valor formado por la clave y valor
 * enviados a la funcion
 */
par_t *crear_par(const char *clave, void *valor)
{
	par_t *par = malloc(sizeof(par_t));
	if (par == NULL)
		return NULL;

 	par->clave = string_duplicado(clave);
	par->valor = valor;

	return par;
}


hash_t *rehashear(hash_t *hash)
{
	hash_t *nuevo_hash = hash_crear(hash->capacidad * 2);
	
	nodo_t *nodo_aux = NULL;
	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;
		for (int j = 0; j < lista_tamanio(hash->tabla[i]); j++) {
			par_t *par = nodo_aux->elemento;
			char *clave_duplicada = string_duplicado(par->clave);
			nuevo_hash = hash_insertar(nuevo_hash, 
			clave_duplicada, par->valor, NULL);
			nodo_aux = nodo_aux->siguiente;
			free(clave_duplicada);
		}
	}
	
	hash_t temporal = *hash;
	*hash = *nuevo_hash;
	*nuevo_hash = temporal;
	hash_destruir(nuevo_hash);

	return hash;
}


/*
 *
 *
 */
bool factor_de_carga_excedido(hash_t *hash)
{
	float factor_de_carga = 0;
	int i = 0;
	bool factor_excedido = false;
	
	while (i < hash->capacidad && !factor_excedido) {
		factor_de_carga = (float) lista_tamanio(hash->tabla[i]) / 
				  (float) hash->capacidad;
		if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA)
			factor_excedido = true;
		i++;
	}

	return factor_excedido;
}


/*
 *
 *
 */
lista_t *almacenar_nuevo_elemento(lista_t *lista_hash, par_t *par)
{
	if (par == NULL)
		return NULL;

	lista_hash = lista_insertar(lista_hash, par);
	return lista_hash;
}


/*
 *
 *
 */
lista_t *actualizar_elemento(lista_t *lista_hash, const char *clave, 
			    void *elemento)
{
	par_t *par_anterior = lista_buscar_elemento(lista_hash, 
						    comparar_claves, &clave);

	par_anterior->valor = elemento;
	return lista_hash;
}



hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	if (factor_de_carga_excedido(hash))
		hash = rehashear(hash);

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;
	if (hash->tabla[posicion_tabla] == NULL)
		hash->tabla[posicion_tabla] = lista_crear();

	if (anterior != NULL)
		*anterior = hash_obtener(hash, clave);

	if (!hash_contiene(hash, clave)) {
		par_t *par = crear_par(clave, elemento);
		hash->tabla[posicion_tabla] = almacenar_nuevo_elemento(
					hash->tabla[posicion_tabla], par);
		hash->almacenados++;
	} else {
		hash->tabla[posicion_tabla] = actualizar_elemento(
				hash->tabla[posicion_tabla], clave, elemento);
	}

	return hash;
}


void *hash_quitar(hash_t *hash, const char *clave)
{	
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	if (!hash_contiene(hash, clave))
		return NULL;

	size_t posicion_a_eliminar = lista_con_cada_elemento(
		hash->tabla[posicion_tabla], claves_no_iguales, &clave) - 1;
	
	par_t *par_a_eliminar = lista_quitar_de_posicion(
			hash->tabla[posicion_tabla], posicion_a_eliminar);

	void *elemento_a_eliminar = par_a_eliminar->valor;
	free(par_a_eliminar->clave);
	free(par_a_eliminar);

	hash->almacenados--;
	return elemento_a_eliminar;
}


void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL || clave == NULL)
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
	if (hash == NULL || clave == NULL)
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

	par_t *par;
	nodo_t *nodo_aux = NULL;
	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;
		for (int j = 0; j < lista_tamanio(hash->tabla[i]); j++) {
			par = nodo_aux->elemento;
			if (destructor != NULL)
				destructor(par->valor);
			free(par->clave);
			free(par);
			nodo_aux = nodo_aux->siguiente;
		}

		lista_destruir(hash->tabla[i]);
	}
				
	free(hash->tabla);
	free(hash);
}


size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{	
	if (hash == NULL || f == NULL)
		return 0;

	bool seguir_iterando = true;
	size_t cantidad_iterados = 0;
	nodo_t *nodo_aux = NULL;

	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;

		int j = 0;
		while (j < lista_tamanio(hash->tabla[i]) && seguir_iterando && nodo_aux != NULL) {
			par_t *par = nodo_aux->elemento;
			if (!f(par->clave, par->valor, aux))
				seguir_iterando = false;

			cantidad_iterados++;
			nodo_aux = nodo_aux->siguiente;
		}	
		seguir_iterando = true;
	}

	return cantidad_iterados;
}