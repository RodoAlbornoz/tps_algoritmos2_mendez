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
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_crear
 */
void abb_probar_creacion(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Creacion de un ABB");

  abb_t *abb = abb_crear(comparador);

  dada_una_funcion_de_comparacion_null_no_se_puede_crear_el_abb();
  dada_una_funcion_de_comparacion_no_null_se_crea_el_abb(abb);
  dado_un_abb_no_null_se_inicializan_sus_campos(abb, comparador);

  abb_destruir(abb);
}


void dado_un_abb_null_no_se_puede_insertar_dentro_de_el(int elemento_prueba)
{
  pa2m_afirmar(abb_insertar(NULL, &elemento_prueba) == NULL, 
               "No se pueden insertar elementos sobre un ABB NULL.");
}


void dado_un_abb_vacio_se_inserta_dentro_de_el(abb_t *abb, 
                                               int elemento_a_insertar)
{
  abb = abb_insertar(abb, &elemento_a_insertar);
  // Corregir abb != NULL por abb_buscar(arbol, elemento_a_insertar) == &elemento_insertado
  pa2m_afirmar(abb != NULL, 
               "Se inserta un elemento en un arbol vacio.");
  pa2m_afirmar(abb_tamanio(abb) == 1, 
               "El tamaño del arbol se incrementa en 1.");
}


void dado_un_abb_con_un_elemento_se_inserta_un_elemento_repetido(abb_t *abb, 
                                                     int elemento_a_insertar)
{
  abb = abb_insertar(abb, &elemento_a_insertar);
  // Corregir abb != NULL por abb_buscar(arbol, elemento_insertado) == &elemento_insertado
  pa2m_afirmar(abb != NULL, 
               "Se inserta un elemento en un arbol con al menos un elemento.");
  pa2m_afirmar(abb->nodo_raiz->izquierda->elemento == abb->nodo_raiz->elemento, 
               "Se inserta un elemento repetido en el arbol.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_insertar
 */
void abb_probar_insercion(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Insercion en un ABB");

  int elemento_prueba = 2;
  abb_t *abb = abb_crear(comparador);

  dado_un_abb_null_no_se_puede_insertar_dentro_de_el(elemento_prueba);
  dado_un_abb_vacio_se_inserta_dentro_de_el(abb, elemento_prueba);
  dado_un_abb_con_un_elemento_se_inserta_un_elemento_repetido(abb, 
                                                              elemento_prueba);

  free(abb->nodo_raiz->izquierda); // CORREGIR
  free(abb->nodo_raiz); // CORREGIR
  abb_destruir(abb);
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


void dado_un_abb_null_no_se_pueden_buscar_elementos(int elemento_prueba)
{
  pa2m_afirmar(abb_buscar(NULL, &elemento_prueba) == NULL, 
               "No se puede buscar un elemento en un ABB NULL.");
}


void dado_un_abb_vacio_no_hay_elementos_para_buscar(abb_t *abb,
                                                    int elemento_prueba)
{
  pa2m_afirmar(abb_buscar(abb, &elemento_prueba) == NULL, 
               "No hay elementos para buscar en un ABB vacio.");
}


void dado_un_abb_no_vacio_no_se_encuentra_el_elemento(abb_t *abb,
                                int elemento_a_insertar, int elemento_a_buscar)
{
  abb_insertar(abb, &elemento_a_insertar);
  pa2m_afirmar(abb_buscar(abb, &elemento_a_buscar) == NULL, 
               "No se encuentra el elemento en el ABB.");
}


void dado_un_abb_no_vacio_se_encuentra_el_elemento(abb_t *abb,
                                                   int elemento_a_buscar)
{
  pa2m_afirmar(abb_buscar(abb, &elemento_a_buscar) == &elemento_a_buscar, 
               "Se encuentra el elemento en el ABB.");
}


void dado_un_abb_no_vacio_se_encuentra_un_elemento_repetido(abb_t *abb, 
                                                    int elemento_repetido)
{
  abb = abb_insertar(abb, &elemento_repetido);
  pa2m_afirmar(abb_buscar(abb, &elemento_repetido) == &elemento_repetido, 
  "Dado un elemento repetido en el ABB, se devuelve su primera aparición.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_buscar
 */
void abb_probar_buscar(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Buscar en un ABB");

  int elemento_prueba_1 = 18;
  int elemento_prueba_2 = 88;
  abb_t *abb = abb_crear(comparador);

  dado_un_abb_null_no_se_pueden_buscar_elementos(elemento_prueba_1);
  dado_un_abb_vacio_no_hay_elementos_para_buscar(abb, elemento_prueba_1);
  dado_un_abb_no_vacio_no_se_encuentra_el_elemento(abb, elemento_prueba_1, 
                                                   elemento_prueba_2);
  dado_un_abb_no_vacio_se_encuentra_el_elemento(abb, elemento_prueba_2);
  dado_un_abb_no_vacio_se_encuentra_un_elemento_repetido(abb, 
                                                         elemento_prueba_2);

  free(abb->nodo_raiz->izquierda); // CORREGIR
  free(abb->nodo_raiz); // CORREGIR
  abb_destruir(abb);
}


void dado_un_abb_null_se_considera_vacio()
{
  pa2m_afirmar(abb_vacio(NULL), "Se devuelve true para un ABB NULL.");
}


void dado_un_abb_vacio_se_considera_vacio(abb_t *abb, 
                                          abb_comparador comparador)
{
  pa2m_afirmar(abb_vacio(abb), "Se devuelve true para un ABB vacio.");
}


void dado_un_abb_no_vacio_no_se_considera_vacio(abb_t *abb, 
                                                abb_comparador comparador)
{
  int elemento_prueba = 9;
  
  abb = abb_insertar(abb, &elemento_prueba);
  pa2m_afirmar(!abb_vacio(abb), 
               "Se devuelve false para un ABB con al menos un elemento.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_vacio
 */
void abb_probar_vacio(abb_comparador comparador)
{
  pa2m_nuevo_grupo("ABB vacio");

  abb_t *abb = abb_crear(comparador);

  dado_un_abb_null_se_considera_vacio();
  dado_un_abb_vacio_se_considera_vacio(abb, comparador);
  dado_un_abb_no_vacio_no_se_considera_vacio(abb, comparador);

  free(abb->nodo_raiz); // CORREGIR
  abb_destruir(abb);
}


void dado_un_abb_null_se_devuelven_0_elementos()
{
  pa2m_afirmar(abb_tamanio(NULL) == 0, 
               "Se devuelve 0 elementos para un ABB NULL.");
}


void dado_un_abb_vacio_se_devuelven_0_elementos(abb_t *abb, 
                                                abb_comparador comparador)
{
  pa2m_afirmar(abb_tamanio(abb) == 0, 
               "Se devuelve 0 elementos para un ABB vacio.");
}


void dado_un_abb_no_vacio_se_devuelve_su_tamanio(abb_t *abb, 
                                                 abb_comparador comparador)
{
  int elemento_prueba_1 = 9;
  int elemento_prueba_2 = 17;
  
  abb = abb_insertar(abb, &elemento_prueba_1);
  abb = abb_insertar(abb, &elemento_prueba_2);
  pa2m_afirmar(abb_tamanio(abb) == 2, 
  "Se devuelve la cantidad de elementos para un ABB de al menos un elemento.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_amanio
 */
void abb_probar_tamanio(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Tamaño de un ABB");

  abb_t *abb = abb_crear(comparador);

  dado_un_abb_null_se_devuelven_0_elementos();
  dado_un_abb_vacio_se_devuelven_0_elementos(abb, comparador);
  dado_un_abb_no_vacio_se_devuelve_su_tamanio(abb, comparador);

  free(abb->nodo_raiz->derecha); // CORREGIR
  free(abb->nodo_raiz); // CORREGIR
  abb_destruir(abb);
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

  abb_probar_creacion(comparador);
  abb_probar_insercion(comparador); 
//abb_probar_quitar();
  abb_probar_buscar(comparador);
  abb_probar_vacio(comparador);
  abb_probar_tamanio(comparador);/*
  abb_probar_iterar();
  abb_probar_guardado_en_vector();
  abb_probar_destruir();
  abb_probar_destruir_todo();*/

  return pa2m_mostrar_reporte();
}