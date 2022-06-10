#include "hash.h"
#include "lista.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LIMITE_FACTOR_DE_CARGA 0.70

typedef struct clave_valor {
	char *clave;
	void *valor;
} clave_valor_t;


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
 * Se devuelve una posicion en la tabla de hash
 */
int funcion_hash(const char *clave) {

	int suma_valores_ascii = 0;
	for (int i = 0; i < strlen(clave); i++)
		suma_valores_ascii += clave[i];

	return suma_valores_ascii
}


/*
hash_t *rehashear()
{
	return hash;
}
*/


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{	/*
	float factor_de_carga = lista_tamanio(hash->tabla[i]) / hash->capacidad;
	hash->almacenados / hash->capacidad;

	if (factor_de_carga >= LIMITE_FACTOR_DE_CARGA)
		hash = rehashear();
	*/

	int posicion_tabla = funcion_hash(clave) % hash->capacidad;

	hash->tabla[posicion_tabla]->elemento = elemento;

	return hash;
}

/*
void *hash_quitar(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return NULL;
}
*/


void *hash_obtener(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return NULL;
}


bool hash_contiene(hash_t *hash, const char *clave)
{
	if (hash == NULL)
		return false;

	int posicion_tabla = funcion_hash(clave, hash->capacidad);
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


size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}
