#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
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
 * Se retorna un numero positivo dado por la funcion de hash
 */
uint32_t funcion_hash(const char *str)
{
    uint32_t hash = 5381;
    uint8_t c;
    while ((c = (uint8_t) *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
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
 * Se retorna un par clave-valor formado por una copia de la clave y el 
 * valor enviados a la funcion
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


/*
 * Se recibe un puntero a hash, una clave, un puntero a un valor y la posicion
 * de la tabla en donde se va a insertar
 * 
 * Se almacena en el hash un valor cuya clave no existia previamente, y se 
 * retorna el hash
 */
hash_t *almacenar_nuevo_valor(hash_t *hash, const char *clave, void *elemento,
			     size_t posicion_tabla)
{
	if (hash->tabla[posicion_tabla] == NULL)
		hash->tabla[posicion_tabla] = lista_crear();

	par_t *par = crear_par(clave, elemento);
	if (par == NULL)
		return NULL;

	hash->tabla[posicion_tabla] = lista_insertar(
				      hash->tabla[posicion_tabla], par);
	hash->almacenados++;
	return hash;
}


/*
 * Se recibe un puntero a hash
 *
 * Se crea un nuevo hash con mayor capacidad que el hash enviado, se
 * insertan dentro los elementos del viejo hash, y se retorna el nuevo hash
 * con mayor capacidad
 */
hash_t *rehashear(hash_t *hash)
{	
	hash_t *nuevo_hash = hash_crear(hash->capacidad * 2);
	
	nodo_t *nodo_aux = NULL;
	for (int i = 0; i < hash->capacidad; i++) {
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;

		size_t tamanio_actual = lista_tamanio(hash->tabla[i]);
		for (int j = 0; j < tamanio_actual; j++) {
			par_t *par = nodo_aux->elemento;
			char *clave_duplicada = string_duplicado(par->clave);
			size_t posicion_tabla = funcion_hash(par->clave) % 
						nuevo_hash->capacidad;
			nuevo_hash = almacenar_nuevo_valor(nuevo_hash, 
				clave_duplicada, par->valor, posicion_tabla);
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


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;
	par_t *par = lista_buscar_elemento(hash->tabla[posicion_tabla], 
					   comparar_claves, &clave);

	if (par != NULL) {
		if (anterior != NULL)
			*anterior = par->valor;

		par->valor = elemento;
		return hash;
	}

	if (anterior != NULL)
		*anterior = NULL;

	float factor_de_carga = (float) hash_cantidad(hash) / 
				(float) hash->capacidad;
	if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA) {
		hash = rehashear(hash);
		posicion_tabla = funcion_hash(clave) % hash->capacidad;
	}

	hash = almacenar_nuevo_valor(hash, clave, elemento, posicion_tabla);
	return hash;
}		


void *hash_quitar(hash_t *hash, const char *clave)
{	
	if (hash == NULL || clave == NULL)
		return NULL;

	size_t posicion_tabla = funcion_hash(clave) % hash->capacidad;

	size_t posicion_a_eliminar = lista_con_cada_elemento(
		hash->tabla[posicion_tabla], claves_no_iguales, &clave) - 1;
	
	par_t *par_a_eliminar = lista_quitar_de_posicion(
			hash->tabla[posicion_tabla], posicion_a_eliminar);

	if (par_a_eliminar == NULL)
		return NULL;

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

	for (int i = 0; i < hash->capacidad; i++) {
		size_t tamanio_lista = lista_tamanio(hash->tabla[i]);
		for (int j = 0; j < tamanio_lista; j++) {
			par_t *par = lista_quitar_de_posicion(hash->tabla[i], 
							      0);
			if (destructor != NULL)
				destructor(par->valor);
			free(par->clave);
			free(par);
		}
		free(hash->tabla[i]);
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

	int j, i = 0;
	while (i < hash->capacidad && seguir_iterando) {
		j = 0;
		if (hash->tabla[i] != NULL)
			nodo_aux = hash->tabla[i]->nodo_inicio;

		size_t tamanio_lista = lista_tamanio(hash->tabla[i]);
		while (j < tamanio_lista && seguir_iterando && 
		       nodo_aux != NULL) {
			par_t *par = nodo_aux->elemento;
			if (!f(par->clave, par->valor, aux))
				seguir_iterando = false;

			nodo_aux = nodo_aux->siguiente;
			cantidad_iterados++;
		}
		i++;	
	}

	return cantidad_iterados;
}