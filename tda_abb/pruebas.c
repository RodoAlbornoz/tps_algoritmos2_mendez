#include "src/abb.h"
#include <stdio.h>
#include "pa2mm.h"
#include "string.h"


/*
 * Se reciben 2 punteros genéricos que apuntan a cualquier tipo de dato
 *
 * Se devuelve un entero de la comparacion de 2 enteros (=0 si 
 * elemento1 = elemento2, <0 si elemento1 < elemento2 y >0 si 
 * elemento1 > elemento2)
 */
int comparar_enteros(void *elemento1, void *elemento2)
{
  int *entero1 = (int *) elemento1;
  int *entero2 = (int *) elemento2;

  return *entero1 - *entero2;
}


/*
 * Se reciben 2 punteros genéricos que apuntan a cualquier tipo de dato
 *
 * Se devuelve un entero de la comparacion de 2 punteros a memoria (= 0 si
 * el tamaño de elemento1 es igual al de elemento2, >0 si el tamaño de
 * elemento1 es mayor al de elemento2, y <0 si el tamaño de elemento2 es
 * mayor al elemento1
 */
int comparar_punteros_a_memoria(void *elemento1, void *elemento2)
{
  int bytes_en_memoria1 = sizeof(elemento1);
  int bytes_en_memoria2 = sizeof(elemento2);

  return bytes_en_memoria1 - bytes_en_memoria2;
}


/*
 * Se reciben punteros a elementos genéricos de cualquier tipo de dato
 *
 * Se devuelve si ese numero es par o no
 */
bool elemento_es_par(void *numero, void *extra)
{
  int *entero = (int *) numero;
	return (((*entero) % 2) == 0);
}


/*
 * Se reciben punteros a elementos genéricos de cualquier tipo de dato
 *
 * Se devuelve si ese numero es impar o no
 */
bool elemento_es_impar(void *numero, void *extra)
{
  int *entero = (int *) numero;
	return (((*entero) % 2) != 0);
}


void con_comparador_null_no_se_puede_crear_el_abb()
{
  pa2m_afirmar(abb_crear(NULL) == NULL, 
  "No se puede crear un ABB con funcion de comparacion NULL.");
}


void con_comparador_no_null_se_crea_el_abb(abb_t *abb)
{
  pa2m_afirmar(abb != NULL, 
              "Se crea un ABB con funcion de comparacion no NULL.");
}


void se_inicializan_los_campos_de_un_abb_no_null(abb_t *abb)
{
  pa2m_afirmar(abb->nodo_raiz == NULL, 
               "La raiz del ABB está inicializada en NULL.");
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

  con_comparador_null_no_se_puede_crear_el_abb();
  con_comparador_no_null_se_crea_el_abb(abb);
  se_inicializan_los_campos_de_un_abb_no_null(abb);

  abb_destruir(abb);
}


void en_un_abb_null_no_se_insertan_elementos(int elemento_prueba)
{
  pa2m_afirmar(abb_insertar(NULL, &elemento_prueba) == NULL, 
               "No se pueden insertar elementos en un ABB NULL.");
}


void en_un_abb_vacio_se_inserta_un_elemento(abb_t *abb, 
                                            int elemento_a_insertar)
{
  abb = abb_insertar(abb, &elemento_a_insertar);
  pa2m_afirmar(abb_buscar(abb, &elemento_a_insertar) == &elemento_a_insertar, 
               "Se inserta un elemento en un arbol vacio.");
  pa2m_afirmar(abb_tamanio(abb) == 1, 
               "El tamaño del arbol se incrementa en 1.");
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

  en_un_abb_null_no_se_insertan_elementos(elemento_prueba);
  en_un_abb_vacio_se_inserta_un_elemento(abb, elemento_prueba);

  abb_destruir(abb);
}


void en_un_abb_null_no_se_pueden_eliminar_elementos()
{
  int elemento_prueba = 2;
  pa2m_afirmar(abb_quitar(NULL, &elemento_prueba) == NULL, 
               "No se pueden eliminar elementos en un ABB NULL.");
}


void en_un_abb_vacio_no_hay_elementos_para_eliminar(abb_t *abb)
{
  int elemento_prueba = 4;
  pa2m_afirmar(abb_quitar(abb, &elemento_prueba) == NULL, 
               "No hay elementos para quitar en un ABB vacio.");
}


void en_un_abb_no_vacio_no_se_encuentra_el_elemento_a_eliminar(abb_t *abb)
{
  int elemento_prueba = 99;
  pa2m_afirmar(abb_quitar(abb, &elemento_prueba) == NULL, 
               "No se encuentra el elemento a eliminar en el arbol.");
}


void en_un_abb_no_vacio_se_elimina_un_nodo_hoja(abb_t *abb, 
                                                int *elemento_a_eliminar)
{
  nodo_abb_t *nodo_a_eliminar = abb->nodo_raiz->derecha->derecha->derecha->
                                derecha;
  nodo_abb_t *nodo_a_eliminar_izquierda = nodo_a_eliminar->izquierda;
  nodo_abb_t *nodo_a_eliminar_derecha = nodo_a_eliminar->derecha;

  size_t tamanio_original_abb = abb_tamanio(abb);

  pa2m_afirmar(abb_quitar(abb, elemento_a_eliminar) == elemento_a_eliminar, 
               "Se elimina un elemento del arbol y se lo devuelve.");
  pa2m_afirmar(abb_tamanio(abb) == tamanio_original_abb - 1, 
               "La cantidad de elementos del arbol se reduce en 1.");
  pa2m_afirmar(nodo_a_eliminar_izquierda == NULL && 
               nodo_a_eliminar_derecha == NULL, 
               "Se elimina un nodo sin hijos del arbol.");
}


void en_un_abb_no_vacio_se_elimina_un_nodo_con_un_hijo(abb_t *abb,
                                                       int *elemento_a_eliminar)
{
  nodo_abb_t *nodo_a_eliminar = abb->nodo_raiz->derecha->derecha;
  nodo_abb_t *nodo_a_eliminar_izquierda = nodo_a_eliminar->izquierda;
  nodo_abb_t *nodo_a_eliminar_derecha = nodo_a_eliminar->derecha;

  pa2m_afirmar(abb_quitar(abb, elemento_a_eliminar) == elemento_a_eliminar &&
               nodo_a_eliminar_derecha != NULL && 
               nodo_a_eliminar_izquierda == NULL,
              "Se elimina del arbol un nodo con un solo hijo.");
}


void en_un_abb_no_vacio_se_elimina_un_nodo_con_dos_hijos_y_predecesor_sin_hijo
                                        (abb_t *abb, int *elemento_a_eliminar)
{ 
  nodo_abb_t *nodo_a_eliminar = abb->nodo_raiz;
  nodo_abb_t *nodo_a_eliminar_izquierda = nodo_a_eliminar->izquierda;
  nodo_abb_t *nodo_a_eliminar_derecha = nodo_a_eliminar->derecha;
  void *elemento_de_la_raiz = abb->nodo_raiz->elemento;

  void *elemento_eliminado = abb_quitar(abb, elemento_a_eliminar);

  pa2m_afirmar(elemento_eliminado == elemento_a_eliminar &&
               nodo_a_eliminar_izquierda != NULL && 
               nodo_a_eliminar_derecha != NULL,
  "Se elimina del arbol un nodo con 2 hijos y con predecesor inorden sin \n\
  hijo.");

  pa2m_afirmar(elemento_eliminado == elemento_de_la_raiz,
               "Se elimina la raiz del arbol.");
}


void en_un_abb_no_vacio_se_elimina_un_nodo_con_dos_hijos_y_predecesor_con_hijo
                                        (abb_t *abb, int *elemento_a_eliminar)
{ 
  nodo_abb_t *nodo_a_eliminar = abb->nodo_raiz->derecha;
  nodo_abb_t *nodo_a_eliminar_izquierda = nodo_a_eliminar->izquierda;
  nodo_abb_t *nodo_a_eliminar_derecha = nodo_a_eliminar->derecha;

  void *elemento_hijo_predecesor = abb->nodo_raiz->derecha->izquierda->
                                   derecha->derecha->izquierda->elemento;
  void *elemento_eliminado = abb_quitar(abb, elemento_a_eliminar);

  pa2m_afirmar(elemento_eliminado == elemento_a_eliminar &&
               nodo_a_eliminar_izquierda != NULL && 
               nodo_a_eliminar_derecha != NULL,
  "Se elimina un nodo con 2 hijos del arbol y con predecesor inorden con un \n\
  hijo.");

  void *elemento_nuevo_predecesor = abb->nodo_raiz->derecha->izquierda->
                                    derecha->derecha->elemento;
  pa2m_afirmar(elemento_nuevo_predecesor == elemento_hijo_predecesor,
  "El elemento del que antes era el predecesor inorden es reemplazado por \n\
  el elemento de su hijo.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_quitar
 */
void abb_probar_quitar(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Eliminación en un ABB");

  int elemento_prueba_1 = 2;
  int elemento_prueba_2 = 1;
  int elemento_prueba_3 = 11;
  int elemento_prueba_4 = 13;
  int elemento_prueba_5 = 4;
  int elemento_prueba_6 = 8;
  int elemento_prueba_7 = 10;
  int elemento_prueba_8 = 9;
  int elemento_prueba_9 = 15;
  int elemento_prueba_10 = 18;
  abb_t *abb = abb_crear(comparador);

  en_un_abb_null_no_se_pueden_eliminar_elementos();
  en_un_abb_vacio_no_hay_elementos_para_eliminar(abb);

  abb = abb_insertar(abb, &elemento_prueba_1);
  abb = abb_insertar(abb, &elemento_prueba_2);
  abb = abb_insertar(abb, &elemento_prueba_3);
  abb = abb_insertar(abb, &elemento_prueba_4);
  abb = abb_insertar(abb, &elemento_prueba_5);
  abb = abb_insertar(abb, &elemento_prueba_6);
  abb = abb_insertar(abb, &elemento_prueba_7);
  abb = abb_insertar(abb, &elemento_prueba_8);
  abb = abb_insertar(abb, &elemento_prueba_9);
  abb = abb_insertar(abb, &elemento_prueba_10);

  en_un_abb_no_vacio_no_se_encuentra_el_elemento_a_eliminar(abb);
  en_un_abb_no_vacio_se_elimina_un_nodo_hoja(abb, &elemento_prueba_10);
  en_un_abb_no_vacio_se_elimina_un_nodo_con_un_hijo(abb, &elemento_prueba_4);                                          
  en_un_abb_no_vacio_se_elimina_un_nodo_con_dos_hijos_y_predecesor_sin_hijo
                                                      (abb, &elemento_prueba_1);
  en_un_abb_no_vacio_se_elimina_un_nodo_con_dos_hijos_y_predecesor_con_hijo
                                                      (abb, &elemento_prueba_3);
                                                      
  abb_destruir(abb);
}


void en_un_abb_null_no_se_buscan_elementos(int elemento_prueba)
{
  pa2m_afirmar(abb_buscar(NULL, &elemento_prueba) == NULL, 
               "No se puede buscar un elemento en un ABB NULL.");
}


void en_un_abb_vacio_no_hay_elementos_para_buscar(abb_t *abb,
                                                    int elemento_prueba)
{
  pa2m_afirmar(abb_buscar(abb, &elemento_prueba) == NULL, 
               "No hay elementos para buscar en un ABB vacio.");
}


void no_se_encuentra_el_elemento_en_un_abb_no_vacio(abb_t *abb,
                                                    int *elemento_a_buscar)
{
  pa2m_afirmar(abb_buscar(abb, elemento_a_buscar) == NULL, 
               "No se encuentra el elemento en el ABB.");
}


void se_encuentra_el_elemento_en_un_abb_no_vacio(abb_t *abb,
                                                 int *elemento_a_buscar)
{
  pa2m_afirmar(abb_buscar(abb, elemento_a_buscar) == elemento_a_buscar, 
               "Se encuentra el elemento en el ABB.");
}


void en_un_abb_no_vacio_se_busca_un_elemento_repetido(abb_t *abb, 
                                                      int *elemento_repetido)
{
  pa2m_afirmar(abb_buscar(abb, elemento_repetido) == elemento_repetido &&
  abb->nodo_raiz->elemento == abb->nodo_raiz->izquierda->elemento, 
  "Se devuelve la primera aparicion de un elemento repetido en el ABB.");
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

  en_un_abb_null_no_se_buscan_elementos(elemento_prueba_1);
  en_un_abb_vacio_no_hay_elementos_para_buscar(abb, elemento_prueba_1);

  abb_insertar(abb, &elemento_prueba_1);
  no_se_encuentra_el_elemento_en_un_abb_no_vacio(abb, &elemento_prueba_2);
  se_encuentra_el_elemento_en_un_abb_no_vacio(abb, &elemento_prueba_1);

  abb = abb_insertar(abb, &elemento_prueba_1);
  en_un_abb_no_vacio_se_busca_un_elemento_repetido(abb, &elemento_prueba_1);

  abb_destruir(abb);
}


void en_un_abb_null_se_devuelve_true_para_vacio()
{
  pa2m_afirmar(abb_vacio(NULL), "Se devuelve true para un ABB NULL.");
}


void en_un_abb_vacio_se_devuelve_true_para_vacio(abb_t *abb)
{
  pa2m_afirmar(abb_vacio(abb), "Se devuelve true para un ABB vacio.");
}


void en_un_abb_no_vacio_se_devuelve_false_para_vacio(abb_t *abb)
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

  en_un_abb_null_se_devuelve_true_para_vacio();
  en_un_abb_vacio_se_devuelve_true_para_vacio(abb);
  en_un_abb_no_vacio_se_devuelve_false_para_vacio(abb);

  abb_destruir(abb);
}


void en_un_abb_null_se_devuelven_0_elementos()
{
  pa2m_afirmar(abb_tamanio(NULL) == 0, 
               "Se devuelve 0 elementos para un ABB NULL.");
}


void en_un_abb_vacio_se_devuelven_0_elementos(abb_t *abb)
{
  pa2m_afirmar(abb_tamanio(abb) == 0, 
               "Se devuelve 0 elementos para un ABB vacio.");
}


void en_un_abb_no_vacio_se_devuelve_el_tamanio(abb_t *abb)
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

  en_un_abb_null_se_devuelven_0_elementos();
  en_un_abb_vacio_se_devuelven_0_elementos(abb);
  en_un_abb_no_vacio_se_devuelve_el_tamanio(abb);

  abb_destruir(abb);
}


void en_un_abb_null_se_recorren_0_elementos()
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(NULL, INORDEN, 
                                                       elemento_es_par, NULL);

  pa2m_afirmar(cantidad_invocaciones == 0, 
  "Para un ABB NULL, no se invoca a la funcion ni una vez ni se recorren \n\
  elementos.");
}


void en_un_abb_vacio_se_recorren_0_elementos(abb_t *abb)
{
  int elemento_extra = 1;
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, PREORDEN, 
                                            elemento_es_par, &elemento_extra);
  pa2m_afirmar(cantidad_invocaciones == 0, 
  "No se invoca a la funcion ni una vez ni se recorren elementos en un ABB \n\
  vacio.");
}


void con_funcion_null_se_recorren_0_elementos(abb_t *abb)
{
  int elemento_extra = 7;
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, POSTORDEN, 
                                                       NULL, &elemento_extra);
  pa2m_afirmar(cantidad_invocaciones == 0, 
  "No se invoca a la funcion ni una vez ni se recorren elementos con una \n\
  funcion NULL.");
}


void se_recorre_un_elemento_en_un_recorrido_postorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, POSTORDEN, 
                                                      elemento_es_impar, NULL);
  pa2m_afirmar(cantidad_invocaciones == 1, 
  "Se invoca a la funcion una sola vez con funcion no NULL y recorrido \n\
  postorden, recorriendo un solo nodo.");
}


void se_recorre_un_elemento_en_un_recorrido_preorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, PREORDEN,
                                                       elemento_es_par, NULL);

  pa2m_afirmar(cantidad_invocaciones == 1, 
  "Se invoca a la funcion una sola vez con funcion no NULL y recorrido \n\
  preorden, recorriendo un solo nodo.");
}


void se_recorre_un_elemento_en_un_recorrido_inorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, INORDEN,
                                                       elemento_es_par, NULL);

  pa2m_afirmar(cantidad_invocaciones == 1, 
  "Se invoca a la funcion una sola vez con funcion no NULL y recorrido \n\
  inorden, recorriendo un solo nodo.");
}


void se_recorre_al_menos_un_elemento_en_un_recorrido_postorden(abb_t *abb) 
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, POSTORDEN, 
                                                       elemento_es_par, NULL);
  pa2m_afirmar(cantidad_invocaciones == 2, 
  "Se invoca a la funcion 2 veces con funcion no NULL y recorrido \n\
  postorden, recorriendo 2 nodos.");
}


void se_recorre_al_menos_un_elemento_en_un_recorrido_preorden(abb_t *abb) 
{
    size_t cantidad_invocaciones = abb_con_cada_elemento(abb, PREORDEN, 
                                                      elemento_es_impar, NULL);
  pa2m_afirmar(cantidad_invocaciones == 3, 
  "Se invoca a la funcion 3 veces con funcion no NULL y recorrido \n\
  preorden, recorriendo 3 nodos.");
}


void se_recorre_al_menos_un_elemento_en_un_recorrido_inorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, INORDEN, 
                                                      elemento_es_impar, NULL);
  pa2m_afirmar(cantidad_invocaciones == 2, 
  "Se invoca a la funcion 2 veces con funcion no NULL y recorrido \n\
  inorden, recorriendo 2 nodos.");
}


void se_recorre_todo_el_abb_en_un_recorrido_preorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, PREORDEN, 
                                                       elemento_es_par, NULL);
  pa2m_afirmar(cantidad_invocaciones == abb_tamanio(abb), 
  "Se recorren en forma preorden todos los elementos del ABB con la funcion \n\
  dada.");
}


void se_recorre_todo_el_abb_en_un_recorrido_postorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, POSTORDEN, 
                                                       elemento_es_par, NULL);

  pa2m_afirmar(cantidad_invocaciones == abb_tamanio(abb), 
  "Se recorren en forma postorden todos los elementos del ABB con la \n\
  funcion dada.");
}


void se_recorre_todo_el_abb_en_un_recorrido_inorden(abb_t *abb)
{
  size_t cantidad_invocaciones = abb_con_cada_elemento(abb, INORDEN, 
                                                       elemento_es_par, NULL);    

  pa2m_afirmar(cantidad_invocaciones == abb_tamanio(abb), 
  "Se recorren en forma inorden todos los elementos del ABB con la funcion \n\
  dada.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_con_cada_elemento
 */
void abb_probar_iterar(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Iterador interno de un ABB");

  int elemento_prueba_1 = 7;
  int elemento_prueba_2 = 10;
  int elemento_prueba_3 = 1;
  int elemento_prueba_4 = 8;
  int elemento_prueba_5 = 4;
  int elemento_prueba_6 = 16;
  abb_t *abb = abb_crear(comparador);

  en_un_abb_null_se_recorren_0_elementos();
  en_un_abb_vacio_se_recorren_0_elementos(abb);
 
  abb = abb_insertar(abb, &elemento_prueba_1);
  abb = abb_insertar(abb, &elemento_prueba_4);
  abb = abb_insertar(abb, &elemento_prueba_2);
  abb = abb_insertar(abb, &elemento_prueba_3);
  abb = abb_insertar(abb, &elemento_prueba_5);

  con_funcion_null_se_recorren_0_elementos(abb);
  se_recorre_un_elemento_en_un_recorrido_postorden(abb);
  se_recorre_un_elemento_en_un_recorrido_preorden(abb);
  se_recorre_un_elemento_en_un_recorrido_inorden(abb);
  se_recorre_al_menos_un_elemento_en_un_recorrido_postorden(abb);
  se_recorre_al_menos_un_elemento_en_un_recorrido_preorden(abb);
  se_recorre_al_menos_un_elemento_en_un_recorrido_inorden(abb);
  
  abb_t *abb_elementos_pares = abb_crear(comparador);
  abb_elementos_pares = abb_insertar(abb_elementos_pares, &elemento_prueba_4);
  abb_elementos_pares = abb_insertar(abb_elementos_pares, &elemento_prueba_5);
  abb_elementos_pares = abb_insertar(abb_elementos_pares, &elemento_prueba_2);
  abb_elementos_pares = abb_insertar(abb_elementos_pares, &elemento_prueba_6);

  se_recorre_todo_el_abb_en_un_recorrido_preorden(abb_elementos_pares);
  se_recorre_todo_el_abb_en_un_recorrido_postorden(abb_elementos_pares);
  se_recorre_todo_el_abb_en_un_recorrido_inorden(abb_elementos_pares);

  abb_destruir(abb_elementos_pares);
  abb_destruir(abb);
}


void en_un_abb_null_no_se_almacenan_elementos()
{
  size_t cantidad_almacenados = abb_recorrer(NULL, PREORDEN, NULL, 5);
  pa2m_afirmar(cantidad_almacenados == 0, 
               "No se almacenan elementos de un ABB NULL.");
}


void con_array_null_no_se_almacenan_elementos(abb_t *abb)
{
  size_t cantidad_almacenados = abb_recorrer(abb, PREORDEN, NULL, 2);
  pa2m_afirmar(cantidad_almacenados == 0, 
               "No se almacenan elementos con un array NULL.");
}


void recorriendo_postorden_no_se_almacenan_elementos_en_array_vacio(abb_t *abb)
{
  void *arreglo[1]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, POSTORDEN, 
                                             arreglo_de_elementos, 0);

  pa2m_afirmar(cantidad_almacenados == 0, 
  "No se almacenan elementos recorriendo postorden con un array de tamaño 0."); 
}


void recorriendo_preorden_no_se_almacenan_elementos_en_array_vacio(abb_t *abb)
{
  void *arreglo[1]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, PREORDEN, 
                                             arreglo_de_elementos, 0);

  pa2m_afirmar(cantidad_almacenados == 0, 
  "No se almacenan elementos recorriendo preorden con un array de tamaño 0.");
}


void recorriendo_inorden_no_se_almacenan_elementos_en_array_vacio(abb_t *abb)
{
  void *arreglo[1]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, INORDEN, 
                                             arreglo_de_elementos, 0);

  pa2m_afirmar(cantidad_almacenados == 0, 
  "No se almacenan elementos recorriendo inorden con un array de tamaño 0.");
}


/*
 * Se reciben 2 punteros a vectores de punteros (Cuyos punteros apuntan a int)
 * y un entero positivo con la cantidad de elementos en ambos vectores
 * 
 * Se retorna una variable booleana que dice si los vectores a punteros son
 * iguales
 */
bool arrays_son_iguales(void **array1, void **array2, size_t tamanio_arrays)
{
  bool arrays_iguales = true;
  int i = 0;

  while (i < tamanio_arrays && arrays_iguales) {
    if (*(int *)array1[i] != *(int*)array2[i])
      arrays_iguales = false;
    i++;
  }

  return arrays_iguales;
}


void se_recorre_el_abb_inorden_y_se_almacenan_todos_sus_elementos(abb_t *abb, 
                                                        void **arreglo_inorden)
{
  void *arreglo[abb_tamanio(abb)]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, INORDEN, 
                                      arreglo_de_elementos, abb_tamanio(abb));

  pa2m_afirmar(cantidad_almacenados == abb_tamanio(abb), 
  "Se recorre el ABB inorden y se almacena la cantidad correcta de \n\
  elementos dentro del array.");

  pa2m_afirmar(arrays_son_iguales(arreglo_inorden, arreglo_de_elementos, 5),
  "Se recorre el ABB y se guardan correctamente todos sus elementos en \n\
  forma inorden en un array.");
}


void se_recorre_el_abb_postorden_y_se_almacenan_todos_sus_elementos(abb_t *abb, 
                                                      void **arreglo_postorden)
{
  void *arreglo[abb_tamanio(abb)]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, POSTORDEN, 
                                      arreglo_de_elementos, abb_tamanio(abb));

  pa2m_afirmar(cantidad_almacenados == abb_tamanio(abb), 
  "Se recorre el ABB postorden y se almacena la cantidad correcta de \n\
  elementos dentro del array.");

  pa2m_afirmar(arrays_son_iguales(arreglo_postorden, arreglo_de_elementos, 5),
  "Se recorre el ABB y se guardan correctamente todos sus elementos en \n\
  forma postorden en un array.");
}


void se_recorre_el_abb_preorden_y_se_almacenan_todos_sus_elementos(abb_t *abb, 
                                                      void **arreglo_preorden)
{
  void *arreglo[abb_tamanio(abb)]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, PREORDEN, 
                                      arreglo_de_elementos, abb_tamanio(abb));

  pa2m_afirmar(cantidad_almacenados == abb_tamanio(abb), 
  "Se recorre el ABB preorden y se almacena la cantidad correcta de \n\
  elementos dentro del array.");

  pa2m_afirmar(arrays_son_iguales(arreglo_preorden, arreglo_de_elementos, 5),
  "Se recorre el ABB y se guardan correctamente todos sus elementos en \n\
  forma preorden en un array.");
}


void se_supera_la_capacidad_del_array_al_insertar_en_el_mismo(abb_t *abb,
                                                      void **arreglo_parcial)
{
  void *arreglo[3]; 
  void **arreglo_de_elementos = arreglo;

  size_t cantidad_almacenados = abb_recorrer(abb, INORDEN, 
                                             arreglo_de_elementos, 3);

  pa2m_afirmar(cantidad_almacenados == 3, 
  "La cantidad de elementos del ABB es mayor que el tamaño del array, por \n\
  lo que solo se guardan algunos elementos del ABB dentro del mismo.");

  pa2m_afirmar(arrays_son_iguales(arreglo_parcial, arreglo_de_elementos, 3),
  "Se recorre parcialmente un ABB y se guarda una cantidad de elementos \n\
  hasta superar el tamaño del array.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_recorrer
 */
void abb_probar_guardado_en_vector(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Recorrido y almacenamiento de elementos de un ABB en un vector");

  int elemento_1 = 7;
  int elemento_2 = 10;
  int elemento_3 = 1;
  int elemento_4 = 8;
  int elemento_5 = 4;

  abb_t *abb = abb_crear(comparador);

  abb = abb_insertar(abb, &elemento_1);
  abb = abb_insertar(abb, &elemento_4);
  abb = abb_insertar(abb, &elemento_2);
  abb = abb_insertar(abb, &elemento_3);
  abb = abb_insertar(abb, &elemento_5);

  en_un_abb_null_no_se_almacenan_elementos();
  con_array_null_no_se_almacenan_elementos(abb);

  recorriendo_postorden_no_se_almacenan_elementos_en_array_vacio(abb);
  recorriendo_preorden_no_se_almacenan_elementos_en_array_vacio(abb);
  recorriendo_inorden_no_se_almacenan_elementos_en_array_vacio(abb);

  void *arreglo_inorden[] = {&elemento_3, &elemento_5, &elemento_1, 
                             &elemento_4, &elemento_2}; 
  void **arreglo_de_elementos_inorden = arreglo_inorden;
  se_recorre_el_abb_inorden_y_se_almacenan_todos_sus_elementos(abb,
                                                arreglo_de_elementos_inorden);

  void *arreglo_postorden[] = {&elemento_5, &elemento_3, &elemento_2, 
                               &elemento_4, &elemento_1}; 
  void **arreglo_de_elementos_postorden = arreglo_postorden;
  se_recorre_el_abb_postorden_y_se_almacenan_todos_sus_elementos(abb,
                                              arreglo_de_elementos_postorden);

  void *arreglo_preordeon[] = {&elemento_1, &elemento_3, &elemento_5, 
                               &elemento_4, &elemento_2}; 
  void **arreglo_de_elementos_preorden = arreglo_preordeon;
  se_recorre_el_abb_preorden_y_se_almacenan_todos_sus_elementos(abb,
                                                arreglo_de_elementos_preorden);

  void *arreglo_inorden_parcial[] = {&elemento_3, &elemento_5, &elemento_1}; 
  se_supera_la_capacidad_del_array_al_insertar_en_el_mismo(abb, 
                                                      arreglo_inorden_parcial);

  abb_destruir(abb);
}

void se_destruye_un_abb_null()
{
  bool abb_destruido = false;
  abb_destruir(NULL);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Se libera un ABB NULL.");
}


void se_destruye_un_abb_vacio(abb_comparador comparador)
{
  abb_t *abb = abb_crear(comparador);

  bool abb_destruido = false;
  abb_destruir(abb);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Se libera un ABB vacio.");
}


void se_destruye_un_abb_no_vacio_y_sus_nodos(abb_comparador comparador)
{
  int elemento_prueba_1 = 7;
  int elemento_prueba_2 = 15;
  int elemento_prueba_3 = 1;
  abb_t *abb = abb_crear(comparador);

  abb = abb_insertar(abb, &elemento_prueba_1);
  abb = abb_insertar(abb, &elemento_prueba_2);
  abb = abb_insertar(abb, &elemento_prueba_3);

  bool abb_destruido = false;
  abb_destruir(abb);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Se libera un ABB junto con todos sus nodos.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_destruir
 */
void abb_probar_destruir(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Destruccion de un ABB");

  se_destruye_un_abb_null();
  se_destruye_un_abb_vacio(comparador);
  se_destruye_un_abb_no_vacio_y_sus_nodos(comparador);
}


void se_destruye_un_abb_null_con_destruir_todo()
{
  bool abb_destruido = false;
  abb_destruir_todo(NULL, free);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Se libera un ABB NULL.");
}


void se_destruye_un_abb_vacio_con_destruir_todo(abb_comparador comparador)
{
  abb_t *abb = abb_crear(comparador);

  bool abb_destruido = false;
  abb_destruir_todo(abb, NULL);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Se libera un ABB vacio.");
}


void con_destructor_null_no_se_liberan_elementos_del_abb(abb_comparador 
                                                             comparador)
{
  int elemento_prueba_1 = 8;
  int elemento_prueba_2 = 4;
  int elemento_prueba_3 = 5;
  abb_t *abb = abb_crear(comparador);

  abb = abb_insertar(abb, &elemento_prueba_1);
  abb = abb_insertar(abb, &elemento_prueba_2);
  abb = abb_insertar(abb, &elemento_prueba_3);

  bool abb_destruido = false;
  abb_destruir_todo(abb, NULL);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Con funcion destructora NULL, solo se libera \n\
  el ABB y sus nodos.");
}


void con_destructor_no_null_se_liberan_elementos_del_abb(abb_comparador 
                                                             comparador)
{
  int *elemento_prueba_1 = malloc(8);
  int *elemento_prueba_2 = malloc(15);
  int *elemento_prueba_3 = malloc(2);
  abb_t *abb = abb_crear(comparador);

  abb = abb_insertar(abb, elemento_prueba_1);
  abb = abb_insertar(abb, elemento_prueba_2);
  abb = abb_insertar(abb, elemento_prueba_3);

  bool abb_destruido = false;
  abb_destruir_todo(abb, free);
  abb_destruido = true;

  pa2m_afirmar(abb_destruido, "Con funcion destructora no NULL, se destruye \n\
  el ABB junto a todos sus nodos y elementos.");
}


/*
 * Se recibe una función para comparar los elementos dentro del arbol
 *
 * Se realizan las pruebas sobre la funcion abb_destruir_todo
 */
void abb_probar_destruir_todo(abb_comparador comparador)
{
  pa2m_nuevo_grupo("Destruccion de un ABB y de sus elementos");

  se_destruye_un_abb_null_con_destruir_todo();
  se_destruye_un_abb_vacio_con_destruir_todo(comparador);
  con_destructor_null_no_se_liberan_elementos_del_abb(comparador);

  abb_comparador nuevo_comparador = comparar_punteros_a_memoria;
  con_destructor_no_null_se_liberan_elementos_del_abb(nuevo_comparador);
}


int main()
{
  abb_comparador comparador = comparar_enteros;

  abb_probar_creacion(comparador);
  abb_probar_insercion(comparador); 
  abb_probar_quitar(comparador);
  abb_probar_buscar(comparador);
  abb_probar_vacio(comparador);
  abb_probar_tamanio(comparador);
  abb_probar_iterar(comparador);
  abb_probar_guardado_en_vector(comparador);
  abb_probar_destruir(comparador);
  abb_probar_destruir_todo(comparador);

  return pa2m_mostrar_reporte();
}