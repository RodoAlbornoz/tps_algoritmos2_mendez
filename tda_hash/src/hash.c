#include "hash.h"
#include "lista.h"



typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

typedef struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad;
} lista_t;


typedef struct clave_valor {
	char *clave;
	void *valor;
	int borrado; // ESTA BIEN?
} clave_valor_t;


typedef struct hash {
	lista_t **tabla;
	int capacidad;
	int almacenados;
} hash_t;


float factor_de_carga(hash_t hash)
{
	return hash.capacidad / hash.almacenados;
}


hash_t *hash_crear(size_t capacidad)
{
	hash_t *hash = malloc(sizeof(hash_t));

	if (hash == NULL)
		return NULL;

	// INICIALIZAR TABLA

	if (capacidad < 3)
		hash->capacidad = 3;
	else 
		hash->capacidad = capacidad;

	hash->almacenados = 0;

	return hash;
}


hash_t *hash_crear(size_t capacidad);


hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{	
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
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
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	return 0;
}
