#include "funciones_para_pruebas.h"
#include <stddef.h>

nodo_abb_t *buscar_nodo(nodo_abb_t *raiz, abb_comparador comparador, 
			void *elemento)
{
	if (raiz == NULL)
		return NULL;
		
	int comparacion = comparador(elemento, raiz->elemento);
	if (comparacion == 0)
		return raiz;
	if (comparacion < 0)
		raiz->izquierda =buscar_nodo(raiz->izquierda, comparador, elemento);
	raiz->derecha = buscar_nodo(raiz->derecha, comparador, elemento);

        return raiz;
}