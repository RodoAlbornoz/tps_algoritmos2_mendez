#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


/*
 * Se realizan las pruebas sobre la funcion abb_crear
 */
void abb_probar_creacion()
{
  pa2m_nuevo_grupo("Creacion de un ABB");

  abb_t *abb1 = abb_crear(comparador);
  abb_t *abb2 = abb_crear(NULL);

  pa2m_afirmar(abb1 != NULL, "Se crea un ABB con funcion de comparacion no NULL.");
  pa2m_afirmar(abb2 == NULL, "Se devuelve NULL al intentar crear un ABB con función de comparación NULL."); 
  pa2m_afirmar(abb1->nodo_raiz = NULL, "La raiz del ABB está inicializada en NULL.");
  pa2m_afirmar(abb1->comparador == comparador_enteros, "La función comparador del ABB es igual a la enviada a la funcion.");
  pa2m_afirmar(abb1->tamanio == 0, "El tamaño del ABB se inicializa en 0."); 

  abb_destruir(abb1);
  abb_destruir(abb2);
}









/*
 * Se realizan las pruebas sobre la funcion abb_vacio
 */
void abb_probar_vacio()
{
  pa2m_nuevo_grupo("ABB vacio");

  pa2m_afirmar(abb_vacio(NULL), "Se devuelve true para un ABB NULL.");
  
  abb_t *abb_sin_elementos = abb_crear(comparador);
  pa2m_afirmar(abb_vacio(abb_sin_elementos), "Se devuelve true para un ABB vacio.");

  abb_t *abb = abb_crear(comparador);
  abb = abb_insertar(abb, elemento);
  pa2m_afirmar(!abb_vacio(abb), "Se devuelve false para un ABB con al menos un elemento.");

  abb_destruir(abb_sin_elementos);
  abb_destruir(abb);
}


/*
 * Se realizan las pruebas sobre la funcion abb_amanio
 */
void abb_probar_tamanio()
{
  pa2m_nuevo_grupo("Tamaño de un ABB");

  pa2m_afirmar(abb_tamanio(NULL), "Se devuelve 0 elementos para un ABB NULL.");

  abb_t *abb_sin_elementos = abb_crear(comparador);
  size_t tamanio_abb = abb_tamanio(abb_sin_elementos);
  pa2m_afirmar(tamanio_abb == 0, "Se devuelve 0 elementos para un ABB vacio.");

  abb_t *abb = abb_crear(comparador);
  abb = abb_insertar(abb, elemento);
  tamanio_abb = abb_tamanio(abb);
  pa2m_afirmar(tamanio_abb > 0, "Se devuelve la cantidad de elementos para un ABB con al menos un elemento.");

  abb_destruir(abb_sin_elementos);
  abb_destruir(abb);
}


int main()
{
  abb_probar_creacion();


  abb_probar_vacio();
  abb_probar_tamanio();


  pa2m_nuevo_grupo("Insercion en un ABB");
  pa2m_afirmar(true, "No se pueden insertar elementos sobre un ABB NULL.");
  pa2m_afirmar(true, "Se inserta un elemento en un arbol vacio.");
  pa2m_afirmar(true, "Se inserta un elemento en un arbol con al menos un elemento.");
  pa2m_afirmar(true, "Se devuelve el arbol al insertar un elemento.");
  pa2m_afirmar(true, "El tamaño del arbol se incrementa en 1.");
  pa2m_afirmar(true, "Se inserta un elemento repetido en el arbol.");



  pa2m_nuevo_grupo("Eliminación en un ABB");
  pa2m_afirmar(true, "No se pueden eliminar elementos sobre un ABB NULL.");
  pa2m_afirmar(true, "No hay elementos para quitar en un ABB vacio.");
  pa2m_afirmar(true, "No se encuentra el elemento a eliminar en el arbol.");
  pa2m_afirmar(true, "Se encuentra el elemento a eliminar en el arbol.");
  pa2m_afirmar(true, "Se devuelve el elemento eliminado del arbol.");
  pa2m_afirmar(true, "La cantidad de elementos del arbol se reduce en 1.");
  pa2m_afirmar(true, "Dado un elemento repetido en el arbol, se elimina el primero encontrado"); // ??
  pa2m_afirmar(true, "Se elimina un nodo sin hijos del arbol.");
  pa2m_afirmar(true, "Se elimina un nodo con un solo hijo del arbol.");
  pa2m_afirmar(true, "Se elimina un nodo con 2 hijos del arbol.");
  pa2m_afirmar(true, "Se reemplaza el nodo eliminado con su predecesor inorden.");


  pa2m_nuevo_grupo("Buscar en un ABB");
  pa2m_afirmar(true, "No se puede buscar un elemento en un ABB NULL.");
  pa2m_afirmar(true, "No hay elementos para buscar en un ABB vacio.");
  pa2m_afirmar(true, "No se encuentra el elemento en el ABB.");
  pa2m_afirmar(true, "Se encuentra el elemento en el ABB.");
  pa2m_afirmar(true, "Se devuelve el elemento encontrado en el ABB.");
  pa2m_afirmar(true, "Dado un elemento repetido en el ABB, se devuelve el primero encontrado");








  pa2m_nuevo_grupo("Iterador interno y recorridos en un ABB");
  pa2m_afirmar(true, "No se puede recorrer un ABB NULL.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "La funcion enviada es NULL y no se recorre el ABB.");
  pa2m_afirmar(true, "No se recorre ningun elemento del ABB con la funcion dada.");
  pa2m_afirmar(true, "Se recorre mas de un elemento del ABB con la funcion dada.");
  pa2m_afirmar(true, "Se recorren todos los elementos del ABB con la funcion dada.");



  pa2m_nuevo_grupo("Recorrido y almacenamiento de un ABB en un vector");
  pa2m_afirmar(true, "No se puede recorrer y almacenar un ABB NULL.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se devuelve la cantidad de elementos almacenados.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se devuelve la cantidad de elementos almacenados.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se devuelve la cantidad de elementos ralmacenados.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "tamanio array es 0 y no se almacenan elementos en el array ni se recorre el ABB.");
  pa2m_afirmar(true, "Se recibe un array NULL.");
  pa2m_afirmar(true, "Se recorre el ABB y se guardan elementos en el array, pero este se queda sin espacio.");



  pa2m_nuevo_grupo("Destruccion de un ABB");
  pa2m_afirmar(true, "Se libera un ABB NULL.");
  pa2m_afirmar(true, "Se libera un ABB vacio.");
  pa2m_afirmar(true, "Se libera un ABB junto con todos sus elementos.");



  pa2m_nuevo_grupo("Destruccion de un ABB y de sus elementos");
  pa2m_afirmar(true, "Se libera un ABB NULL.");
  pa2m_afirmar(true, "Se libera un ABB vacio.");
  pa2m_afirmar(true, "Se libera un ABB junto con todos sus elementos.");
  pa2m_afirmar(true, "Solo se destruye el ABB y sus nodos enviando una funcion destructora NULL.");
  pa2m_afirmar(true, "Se destruye el ABB junto a todos sus nodos y elementos con una funcion destructora no NULL.");

  return pa2m_mostrar_reporte();
}
