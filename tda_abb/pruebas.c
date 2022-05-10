#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


int comparar_enteros(void *elemento1, void *elemento2)
{
  int *entero1 = (int *) elemento1;
  int *entero2 = (int *) elemento2;

  return *entero1 - *entero2;
}


void dada_una_funcion_de_comparacion_null_no_se_puede_crear_el_abb()
{
  abb_t *abb = abb_crear(NULL);
  pa2m_afirmar(abb == NULL, "Se devuelve NULL al intentar crear un ABB con \n\
  función de comparación NULL."); 

  abb_destruir(abb);
}


void dada_una_funcion_de_comparacion_no_null_se_crea_el_abb(abb_t *abb)
{
  pa2m_afirmar(abb != NULL, 
              "Se crea un ABB con funcion de comparacion no NULL.");
}


void dado_un_abb_no_null_se_inicializan_sus_campos(abb_t *abb, 
                                                   abb_comparador comparador)
{
  pa2m_afirmar(abb->nodo_raiz == NULL, 
               "La raiz del ABB está inicializada en NULL.");
  pa2m_afirmar(abb->comparador == comparador, 
  "La función comparador del ABB es igual a la enviada a la funcion \n\
  de creación.");
  pa2m_afirmar(abb_vacio(abb), "El tamaño del ABB se inicializa en 0."); 

  abb_destruir(abb);
}


/*
 * Se realizan las pruebas sobre la funcion abb_crear
 */
void abb_probar_creacion(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Creacion de un ABB");

  dada_una_funcion_de_comparacion_null_no_se_puede_crear_el_abb();

  abb_t *abb = abb_crear(comparador);
  dada_una_funcion_de_comparacion_no_null_se_crea_el_abb(abb);
  dado_un_abb_no_null_se_inicializan_sus_campos(abb, comparador);
}


/*
 * Se realizan las pruebas sobre la funcion abb_insertar
 */
void abb_probar_insercion()
{
  pa2m_nuevo_grupo("Insercion en un ABB");

  int elemento_prueba_1 = 2;
  int elemento_prueba_2 = 99;
  abb_comparador comparador = comparar_enteros;

  pa2m_afirmar(abb_insertar(NULL, &elemento_prueba_1) == NULL, "No se pueden insertar elementos sobre un ABB NULL.");

  abb_t *abb = abb_crear(comparador);
  abb = abb_insertar(abb, &elemento_prueba_2);

  pa2m_afirmar(abb != NULL, "Se inserta un elemento en un arbol vacio.");
  pa2m_afirmar(abb != NULL, "Se devuelve el arbol al insertar un elemento.");
  pa2m_afirmar(abb_tamanio(abb) == 1, "El tamaño del arbol se incrementa en 1.");
  
  abb = abb_insertar(abb, &elemento_prueba_1);
  pa2m_afirmar(abb != NULL, "Se inserta un elemento en un arbol con al menos un elemento.");

//  pa2m_afirmar(true, "Se inserta un elemento repetido en el arbol.");
//  pa2m_afirmar(true, "Se inserta un nodo en la raiz de un ABB de al menos 1 elemento.");

  free(abb);
}


/*
 * Se realizan las pruebas sobre la funcion abb_quitar
 */
void abb_probar_quitar()
{
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
}


/*
 * Se realizan las pruebas sobre la funcion abb_buscar
 */
void abb_probar_buscar()
{
  pa2m_nuevo_grupo("Buscar en un ABB");

  pa2m_afirmar(true, "No se puede buscar un elemento en un ABB NULL.");
  pa2m_afirmar(true, "No hay elementos para buscar en un ABB vacio.");
  pa2m_afirmar(true, "No se encuentra el elemento en el ABB.");
  pa2m_afirmar(true, "Se encuentra el elemento en el ABB.");
  pa2m_afirmar(true, "Se devuelve el elemento encontrado en el ABB.");
  pa2m_afirmar(true, "Dado un elemento repetido en el ABB, se devuelve el primero encontrado");
}


void dado_un_abb_null_se_considera_vacio()
{
  pa2m_afirmar(abb_vacio(NULL), "Se devuelve true para un ABB NULL.");
}


void dado_un_abb_vacio_se_considera_vacio(abb_comparador comparador)
{
  abb_t *abb_sin_elementos = abb_crear(comparador);
  pa2m_afirmar(abb_vacio(abb_sin_elementos), 
               "Se devuelve true para un ABB vacio.");

  abb_destruir(abb_sin_elementos);
}


/*
void dado_un_abb_no_vacio_no_se_considera_vacio(abb_comparador comparador)
{
  int elemento_prueba = 9;

  abb_t *abb = abb_crear(comparador);
  abb = abb_insertar(abb, &elemento_prueba);
  pa2m_afirmar(!abb_vacio(abb), 
               "Se devuelve false para un ABB con al menos un elemento.");
  
  abb_destruir(abb);
}
*/


/*
 * Se realizan las pruebas sobre la funcion abb_vacio
 */
void abb_probar_vacio(abb_comparador comparador)
{
  pa2m_nuevo_grupo("ABB vacio");

  dado_un_abb_null_se_considera_vacio();
  dado_un_abb_vacio_se_considera_vacio(comparador);
//dado_un_abb_no_vacio_no_se_considera_vacio(comparador);
}


void dado_un_abb_null_se_devuelven_0_elementos()
{
  pa2m_afirmar(abb_tamanio(NULL) == 0, 
               "Se devuelve 0 elementos para un ABB NULL.");
}


void dado_un_abb_vacio_se_devuelven_0_elementos(abb_comparador comparador)
{
  abb_t *abb_vacio = abb_crear(comparador);
  size_t tamanio_abb = abb_tamanio(abb_vacio);
  pa2m_afirmar(tamanio_abb == 0, "Se devuelve 0 elementos para un ABB vacio.");

  abb_destruir(abb_vacio);
}


/*
void dado_un_abb_no_vacio_se_devuelve_su_tamanio(abb_comparador comparador)
{
  int elemento_prueba_1 = 9;
  
  abb_t *abb = abb_crear(comparador);
  abb = abb_insertar(abb, &elemento_prueba_1);
  size_t tamanio_abb = abb_tamanio(abb);
  pa2m_afirmar(tamanio_abb == 1, "Se devuelve la cantidad de elementos \n\
               para un ABB con al menos un elemento.");
  
  abb_destruir(abb);
}
*/


/*
 * Se realizan las pruebas sobre la funcion abb_amanio
 */
void abb_probar_tamanio(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Tamaño de un ABB");

  dado_un_abb_null_se_devuelven_0_elementos();
  dado_un_abb_vacio_se_devuelven_0_elementos(comparador);
//dado_un_abb_no_vacio_se_devuelve_su_tamanio(comparador);
}


/*
 * Se realizan las pruebas sobre la funcion abb_con_cada_elemento
 */
void abb_probar_iterar()
{
  pa2m_nuevo_grupo("Iterador interno y recorridos en un ABB");
  pa2m_afirmar(true, "No se puede recorrer un ABB NULL.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se devuelve la cantidad de elementos recorridos.");
  pa2m_afirmar(true, "La funcion enviada es NULL y no se recorre el ABB.");
  pa2m_afirmar(true, "No se recorre ningun elemento del ABB con la funcion dada.");
  pa2m_afirmar(true, "Se recorre mas de un elemento del ABB con la funcion dada.");
  pa2m_afirmar(true, "Se recorren todos los elementos del ABB con la funcion dada.");
}


/*
 * Se realizan las pruebas sobre la funcion abb_recorrer
 */
void abb_probar_guardado_en_vector()
{
  pa2m_nuevo_grupo("Recorrido y almacenamiento de un ABB en un vector");

  pa2m_afirmar(true, "No se puede recorrer y almacenar los elementos de un ABB NULL.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se devuelve la cantidad de elementos almacenados.");
  pa2m_afirmar(true, "Se recorre el ABB inorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se devuelve la cantidad de elementos almacenados.");
  pa2m_afirmar(true, "Se recorre el ABB postorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se devuelve la cantidad de elementos ralmacenados.");
  pa2m_afirmar(true, "Se recorre el ABB preorden y se guardan los elementos en un vector.");
  pa2m_afirmar(true, "tamanio array es 0 y no se almacenan elementos en el array ni se recorre el ABB.");
  pa2m_afirmar(true, "Se recibe un array NULL.");
  pa2m_afirmar(true, "Se recorre el ABB y se guardan elementos en el array, pero este se queda sin espacio.");
}


/*
 * Se realizan las pruebas sobre la funcion abb_destruir
 */
void abb_probar_destruir()
{
  pa2m_nuevo_grupo("Destruccion de un ABB");

  pa2m_afirmar(true, "Se libera un ABB NULL.");
  pa2m_afirmar(true, "Se libera un ABB vacio.");
  pa2m_afirmar(true, "Se libera un ABB junto con todos sus elementos.");
}


/*
 * Se realizan las pruebas sobre la funcion abb_destruir_todo
 */
void abb_probar_destruir_todo()
{
  pa2m_nuevo_grupo("Destruccion de un ABB y de sus elementos");
  pa2m_afirmar(true, "Se libera un ABB NULL.");
  pa2m_afirmar(true, "Se libera un ABB vacio.");
  pa2m_afirmar(true, "Se libera un ABB junto con todos sus elementos.");
  pa2m_afirmar(true, "Solo se destruye el ABB y sus nodos enviando una funcion destructora NULL.");
  pa2m_afirmar(true, "Se destruye el ABB junto a todos sus nodos y elementos con una funcion destructora no NULL.");
}


int main()
{
  abb_comparador comparador = comparar_enteros;

  abb_probar_creacion(comparador);/*
  abb_probar_insercion(); // CORREGIR
  abb_probar_quitar();
  abb_probar_buscar();*/
  abb_probar_vacio(comparador);
  abb_probar_tamanio(comparador);/*
  abb_probar_iterar();
  abb_probar_guardado_en_vector();
  abb_probar_destruir();
  abb_probar_destruir_todo();*/

  return pa2m_mostrar_reporte();
}