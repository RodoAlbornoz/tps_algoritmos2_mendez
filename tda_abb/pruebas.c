#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"

int main()
{
  pa2m_nuevo_grupo("Creacion de ABB");
  pa2m_afirmar(true, "Se crea un ABB exitosamente con una funcion de comparacion no NULL.");
  pa2m_afirmar(true, "No se puede crear un ABB con una función de comparación NULL, y se devuelve NULL.");
  pa2m_afirmar(true, "La raiz del arbol está inicializada en NULL.");
  pa2m_afirmar(true, "El tamaño del arbol inicialmente es 0.");



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



  pa2m_nuevo_grupo("ABB vacio");
  pa2m_afirmar(true, "Se devuelve true para un ABB NULL.");
  pa2m_afirmar(true, "Se devuelve true para un ABB vacio.");
  pa2m_afirmar(true, "Se devuelve false para un ABB con al menos un elemento.");



  pa2m_nuevo_grupo("Tamaño de un ABB");
  pa2m_afirmar(true, "Se devuelve 0 elementos para un ABB NULL.");
  pa2m_afirmar(true, "Se devuelve 0 elementos para un ABB vacio.");
  pa2m_afirmar(true, "Se devuelve la cantidad de elementos para un ABB con al menos un elemento.");



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
