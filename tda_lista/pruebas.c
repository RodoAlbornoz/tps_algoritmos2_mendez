#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

/*
 * Se realizan las pruebas sobre la función lista_crear
 */ 
void lista_probar_creacion() 
{
  pa2m_nuevo_grupo("Creación de una lista");

  lista_t *lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Se crea una lista exitosamente.");
  pa2m_afirmar(lista != NULL && lista->nodo_inicio == NULL, 
  "El puntero al nodo inicial de la lista está inicializado en NULL.");

  pa2m_afirmar(lista != NULL && lista->nodo_fin == NULL, 
  "El puntero al nodo final de la lista está inicializado en NULL.");

  pa2m_afirmar(lista != NULL && lista_vacia(lista), 
               "La cantidad de elementos de la lista se inicializa en 0.");

  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_insertar
 */
void lista_probar_insercion_al_final()
{
  pa2m_nuevo_grupo("Inserción de elementos al final de una lista");

  int elemento_prueba_1 = 5;
  char *elemento_prueba_2 = "Hola mundo";

  pa2m_afirmar(lista_insertar(NULL, &elemento_prueba_1) == NULL, 
               "No se insertan elementos en una lista NULL.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  pa2m_afirmar(lista != NULL, 
  "Se retorna la lista al insertar un elemento al final de la misma.");
  pa2m_afirmar(lista != NULL, 
               "Se inserta un elemento en una lista vacia.");
  pa2m_afirmar(lista != NULL && lista_tamanio(lista) == 1, 
               "La cantidad de elementos de la lista aumenta en 1.");

  size_t cantidad_auxiliar = lista_tamanio(lista);
  lista = lista_insertar(lista, &elemento_prueba_2);
  pa2m_afirmar(lista_tamanio(lista) == cantidad_auxiliar + 1, 
  "Se inserta un elemento al final de una lista con al menos un elemento.");

  lista = lista_insertar(lista, NULL);
  pa2m_afirmar(lista != NULL, "Se inserta un elemento NULL a la lista.");

  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_quitar
*/ 
void lista_probar_eliminacion_al_final()
{
  pa2m_nuevo_grupo("Eliminación de elementos al final de una lista");

  int elemento_prueba_1 = 11;
  char elemento_prueba_2 = 'a';

  pa2m_afirmar(lista_quitar(NULL) == NULL, 
               "No se puede eliminar un elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *elemento_eliminado = lista_quitar(lista_vacia);
  pa2m_afirmar(elemento_eliminado == NULL,
               "No se puede eliminar un elemento de una lista vacia.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_1);

  size_t cantidad_auxiliar = lista_tamanio(lista);
  elemento_eliminado = lista_quitar(lista);
  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se elimina un elemento de la lista.");
  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se devuelve el elemento eliminado.");
  pa2m_afirmar(lista_tamanio(lista) == cantidad_auxiliar - 1, 
               "La cantidad de elementos de la lista se reduce en 1.");
               
  elemento_eliminado = lista_quitar(lista);
  pa2m_afirmar(elemento_eliminado == NULL, 
               "Se elimina un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_insertar_en_posicion
 */
void lista_probar_insercion_en_posicion()
{ 
  pa2m_nuevo_grupo("Inserción de elementos en cierta posicion de una lista");

  int elemento_prueba_1 = 1;
  char *elemento_prueba_2 = "Texto de prueba";
  char elemento_prueba_3 = '<';

  pa2m_afirmar(lista_insertar_en_posicion(NULL, &elemento_prueba_1, 5) == NULL, 
               "No se insertan elementos en una lista NULL.");

  lista_t *lista = lista_crear();
  lista = lista_insertar_en_posicion(lista, &elemento_prueba_3, 0);
  pa2m_afirmar(lista != NULL, 
               "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(lista != NULL, 
               "Se inserta un elemento en una lista vacia.");
  pa2m_afirmar(lista != NULL && lista_tamanio(lista) == 1, 
               "La cantidad de elementos de la lista aumenta en 1.");

  size_t cantidad_auxiliar = lista_tamanio(lista);
  lista = lista_insertar_en_posicion(lista, NULL, 1);
  pa2m_afirmar(lista_tamanio(lista) == cantidad_auxiliar + 1, 
               "Se inserta un elemento NULL a la lista.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_2, 0);
  pa2m_afirmar(lista != NULL, 
  "Se inserta un elemento al principio de una lista.");
  
  lista = lista_insertar_en_posicion(lista, &elemento_prueba_1, 1);
  pa2m_afirmar(lista != NULL, 
  "Se inserta un elemento en medio de una lista.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_3, 4);
  pa2m_afirmar(lista != NULL, 
  "Se inserta un elemento al final de una lista.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_2, 99);
  pa2m_afirmar(lista != NULL, 
  "Al insertar un elemento en una posicion inexistente, se inserta al final.");

  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_quitar_de_posicion
 */ 
void lista_probar_eliminacion_en_posicion()
{
  pa2m_nuevo_grupo("Eliminación de elementos en cierta posicion de una lista");

  char *elemento_prueba_1 = "Hola";
  int elemento_prueba_2 = -6;
  float elemento_prueba_3 = 0.5;

  pa2m_afirmar(lista_quitar_de_posicion(NULL, 9) == NULL, 
               "No se puede eliminar un elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *elemento_eliminado_lista = lista_quitar_de_posicion(lista_vacia, 9);
  pa2m_afirmar(elemento_eliminado_lista == NULL, 
               "No se puede eliminar un elemento de una lista vacia.");

  lista_t *lista = lista_crear();
  lista_insertar_en_posicion(lista, &elemento_prueba_3, 1);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 0);
  lista_insertar_en_posicion(lista, &elemento_prueba_1, 1);
  lista_insertar_en_posicion(lista, NULL, 2);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 3);

  size_t cantidad_auxiliar = lista_tamanio(lista);
  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 1);
  pa2m_afirmar(elemento_eliminado_lista != NULL, 
               "Se elimina un elemento del medio de la lista.");
  pa2m_afirmar(elemento_eliminado_lista != NULL, 
               "Se devuelve el elemento eliminado.");
  pa2m_afirmar(lista_tamanio(lista) == cantidad_auxiliar - 1, 
               "La cantidad de elementos se reduce en 1.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 3);
  pa2m_afirmar(elemento_eliminado_lista != NULL, 
               "Se elimina el ultimo elemento de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 0);
  pa2m_afirmar(elemento_eliminado_lista != NULL, 
               "Se elimina el primer elemento de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 99);
  pa2m_afirmar(elemento_eliminado_lista != NULL, 
  "Al eliminar un elemento en una posicion inexistente, se elimina al final.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 0);
  pa2m_afirmar(elemento_eliminado_lista == NULL, 
               "Se elimina un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_elemento_en_posicion 
 */ 
void lista_probar_buscar_por_posicion()
{
  pa2m_nuevo_grupo("Buscar elementos por su posicion en una lista");

  char elemento_prueba_1 = 'k';
  int elemento_prueba_2 = 0;
  char *elemento_prueba_3 = "Algoritmos 2";

  void *elemento_en_posicion = lista_elemento_en_posicion(NULL, 0);
  pa2m_afirmar(elemento_en_posicion == NULL, 
  "No se puede buscar un elemento por su posicion en una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  elemento_en_posicion = lista_elemento_en_posicion(lista_vacia, 2);
  pa2m_afirmar(elemento_en_posicion == NULL, 
  "Al buscar un elemento en una lista vacia, se devuelve NULL.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_3);

  elemento_en_posicion = lista_elemento_en_posicion(lista, 9876);
  pa2m_afirmar(elemento_en_posicion == NULL, 
  "Al buscar un elemento en una posición inexistente, se devuelve NULL.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 0);
  pa2m_afirmar(elemento_en_posicion != NULL, 
  "En una lista de al menos un elemento, se retorna el primer elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento_en_posicion != NULL, 
  "En una lista de al menos un elemento, se retorna el ultimo elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 1);
  pa2m_afirmar(elemento_en_posicion != NULL, 
  "Se retorna algun elemento del medio de una lista de al menos un elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 2);
  pa2m_afirmar(elemento_en_posicion == NULL, 
               "Se trae un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se reciben las referencias a elementos genéricos de cualquier tipo de dato 
 *
 * Se castean los elementos genéricos a int, y se devuelve 0 si sus valores 
 * son iguales, o 1 si no lo son.
 */
int comparacion_enteros(void *elemento1, void *elemento2)
{
  int *entero1 = (int *) elemento1;
  int *entero2 = (int *) elemento2;

  if ((*entero1) == (*entero2))
    return 0;
  
  return 1;
}


/*
 * Se reciben las referencias a elementos genéricos de cualquier tipo de dato 
 *
 * Se castean los elementos genéricos a char, y se devuelve 0 si sus valores 
 * son iguales, o 1 si no lo son.
 */
int comparacion_char(void *elemento1, void *elemento2)
{
  char *caracter1 = (char *) elemento1;
  char *caracter2 = (char *) elemento2;

  if ((*caracter1) == (*caracter2))
    return 0;
  
  return 1;
}


/*
 * Se realizan las pruebas sobre la función lista_buscar_elemento
 */ 
void lista_probar_buscar_elemento()
{
  pa2m_nuevo_grupo("Buscar elementos en una lista");

  lista_t *lista = lista_crear();

  int elemento_prueba_1 = 100;
  char elemento_prueba_2 = 'x';
  int elemento_a_buscar = 77;

  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, &elemento_prueba_2);

  pa2m_afirmar(lista_buscar_elemento(NULL, comparacion_enteros, 
               &elemento_prueba_1) == NULL, 
               "No se puede buscar un elemento en una lista NULL.");
  pa2m_afirmar(lista_buscar_elemento(lista, NULL, 
               &elemento_prueba_2) == NULL, 
  "Si el comparador es NULL, no se puede buscar un elemento.");

  void *elemento_encontrado = lista_buscar_elemento(lista, comparacion_enteros, 
                                              &elemento_a_buscar);
  pa2m_afirmar(elemento_encontrado == NULL, 
               "No se encuentra el elemento buscado.");

  elemento_encontrado = lista_buscar_elemento(lista, comparacion_enteros, 
                                              &elemento_prueba_1);
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_1, 
               "Se busca y se encuentra el primer elemento encontrado.");

  elemento_encontrado = lista_buscar_elemento(lista, comparacion_char, 
                                              &elemento_prueba_2);
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_2, 
  "Se busca un elemento repetido en la lista, y se devuelve el elemento en\n\
  en su primera aparecición.");

  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_primero
 */ 
void lista_probar_obtener_primer_elemento()
{
  pa2m_nuevo_grupo("Primer elemento de una lista");

  int elemento_prueba_1 = 99;
  char elemento_prueba_2 = 'E';

  pa2m_afirmar(lista_primero(NULL) == NULL, 
  "Se retorna NULL al buscar el primer elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *primer_elemento = lista_primero(lista_vacia);
  pa2m_afirmar(primer_elemento == NULL, 
  "Se retorna NULL al buscar el primer elemento de una lista vacia.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  primer_elemento = lista_primero(lista);
  pa2m_afirmar(lista != NULL, 
  "Se retorna el primer elemento de una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_ultimo
 */ 
void lista_probar_obtener_ultimo_elemento()
{
  pa2m_nuevo_grupo("Ultimo elemento de una lista");

  int elemento_prueba_1 = 11;
  float elemento_prueba_2 = 0.5;

  pa2m_afirmar(lista_ultimo(NULL) == NULL, 
  "Se retorna NULL al buscar el ultimo elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *ultimo_elemento = lista_ultimo(lista_vacia);
  pa2m_afirmar(ultimo_elemento == NULL, 
  "Se retorna NULL al buscar el ultimo elemento de una lista vacia.");

  lista_t *lista = lista_crear(); 
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  ultimo_elemento = lista_ultimo(lista);
  pa2m_afirmar(lista != NULL, 
  "Se retorna el ultimo elemento de una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_vacia
 */ 
void lista_probar_vacia_o_inexistente()
{
  pa2m_nuevo_grupo("Lista vacia/inexistente");

  int elemento_prueba = 6;

  pa2m_afirmar(lista_vacia(NULL), "Se devuelve true para una lista NULL.");

  lista_t *lista_sin_elementos = lista_crear();
  pa2m_afirmar(lista_vacia(lista_sin_elementos), 
               "Se devuelve true para una lista vacia.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba);
  pa2m_afirmar(!lista_vacia(lista), 
               "Se devuelve false para una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_sin_elementos);
}


/*
 * Se realizan las pruebas sobre la función lista_tamanio
 */ 
void lista_probar_tamanio()
{
  pa2m_nuevo_grupo("Tamaño de una lista");

  char elemento_prueba = 'i';

  pa2m_afirmar(lista_tamanio(NULL) == 0, 
               "Se devuelve 0 elementos para una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  pa2m_afirmar(lista_vacia != NULL && lista_tamanio(lista_vacia) == 0, 
               "Se devuelve 0 elementos para una lista vacia.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba);
  pa2m_afirmar(lista_tamanio(lista) > 0, 
  "Se devuelve la cantidad de elementos para una lista con al menos un\n\
  elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_destruir
 */ 
void lista_probar_destruccion()
{
  pa2m_nuevo_grupo("Destrucción de una lista");

  int elemento_prueba_1 = 9;
  char elemento_prueba_2 = 'z';

  lista_t *lista_inexistente = NULL;
  lista_destruir(lista_inexistente);
  pa2m_afirmar(lista_inexistente == NULL, "Se libera una lista NULL.");

  lista_t *lista_sin_elementos = lista_crear();
  bool lista_es_vacia = lista_vacia(lista_sin_elementos);
  lista_destruir(lista_sin_elementos);
  pa2m_afirmar(lista_es_vacia, "Se libera una lista vacia");

  lista_t *lista = lista_crear();
  bool lista_eliminada = false;
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista_destruir(lista);
  lista_eliminada = true;
  pa2m_afirmar(lista_eliminada, "Se libera una lista de al menos un\n\
  elemento.");
}


/*
 * Se realizan las pruebas sobre la función lista_destruir_todo
 */
void lista_probar_destruccion_total()
{
  pa2m_nuevo_grupo("Destrucción de una lista y de sus elementos");
  
  int elemento_prueba_1 = 9;
  int elemento_prueba_2 = 10;
  int *elemento_prueba_3 = malloc(sizeof(int));
  int *elemento_prueba_4 = malloc(sizeof(int));

  lista_t *lista_sin_elementos = lista_crear();

  lista_t *lista_inexistente = NULL;
  bool lista_destruida = false;
  lista_destruir_todo(lista_inexistente, free);
  lista_destruida = true;
  pa2m_afirmar(lista_destruida, "Se libera una lista NULL.");

  lista_destruida = false;
  lista_destruir_todo(lista_sin_elementos, free);
  lista_destruida = true;
  pa2m_afirmar(lista_destruida, "Se libera una lista vacia");

  lista_t *lista1 = lista_crear();
  lista1 = lista_insertar(lista1, &elemento_prueba_1);
  lista1 = lista_insertar(lista1, &elemento_prueba_2);
  lista_destruida = false;
  lista_destruir_todo(lista1, NULL);
  lista_destruida = true;

  pa2m_afirmar(lista_destruida, 
  "Se libera una lista de mas de un elemento junto con todos sus nodos.");
  pa2m_afirmar(lista_destruida, 
  "Solo se libera memoria de la lista y no se destruyen sus elementos con\n\
  una funcion destructora NULL");

  lista_t *lista2 = lista_crear();
  lista2 = lista_insertar(lista2, elemento_prueba_3);
  lista2 = lista_insertar(lista2, elemento_prueba_4);
  lista_destruida = false;
  lista_destruir_todo(lista2, NULL);
  lista_destruida = true;

  pa2m_afirmar(lista_destruida && elemento_prueba_3 != NULL && 
               elemento_prueba_4 != NULL, "Se libera la memoria de los\n\
  elementos de la lista al enviar free como funcion destructora.");

  free(elemento_prueba_3);
  free(elemento_prueba_4);
}


/*
 * Se realizan las pruebas sobre la función lista_iterador_crear
 */
void lista_probar_creacion_iterador()
{
  pa2m_nuevo_grupo("Creación de un iterador externo");

  int elemento_prueba_1 = 7;
  char elemento_prueba_2 = 'J';

  pa2m_afirmar(lista_iterador_crear(NULL) == NULL, 
               "No se crea el iterador si la lista enviada es NULL.");

  lista_t *lista_vacia = lista_crear();
  lista_iterador_t *iterador1 = lista_iterador_crear(lista_vacia);

  pa2m_afirmar(iterador1 != NULL, 
               "Se crea el iterador a partir de una lista.");
  pa2m_afirmar(iterador1 != NULL && iterador1->corriente == NULL, 
  "El elemento actual del iterador apunta inicialmente a NULL para una lista\n\
  vacia.");
  lista_iterador_destruir(iterador1);

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista_iterador_t *iterador2 = lista_iterador_crear(lista);

  pa2m_afirmar(iterador2 != NULL && iterador2->corriente == lista->nodo_inicio, 
  "El elemento actual del iterador apunta inicialmente al primer elemento\n\
  para una lista con al menos un elemento.");
  lista_iterador_destruir(iterador2);

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre la función lista_iterador_tiene_siguiente
 */ 
void lista_probar_iterador_siguiente()
{
  pa2m_nuevo_grupo("Seguir iterando sobre el iterador externo");

  char elemento_prueba_1 = 'T';
  char elemento_prueba_2 = '9';

  pa2m_afirmar(!lista_iterador_tiene_siguiente(NULL), 
               "No hay elementos para iterar con un iterador NULL.");

  lista_t *lista_vacia = lista_crear();
  lista_iterador_t *iterador_lista_vacia = lista_iterador_crear(lista_vacia);

  pa2m_afirmar(!lista_iterador_tiene_siguiente(iterador_lista_vacia), 
               "No hay elementos para iterar en una lista vacia.");
  lista_iterador_destruir(iterador_lista_vacia);

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista_iterador_t *iterador = lista_iterador_crear(lista);

  pa2m_afirmar(lista_iterador_tiene_siguiente(iterador), "Se puede seguir\n\
  iterando sobre una lista con al menos un elemento si el elemento actual\n\
  del iterador no apunta a NULL.");
  lista_iterador_destruir(iterador);

  lista_destruir(lista_vacia);
  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_iterador_avanzar
 */
void lista_probar_iterador_avanzar()
{
  pa2m_nuevo_grupo("Avanzar un iterador externo");

  int elemento_prueba_1 = 66;
  char elemento_prueba_2 = 'r';

  pa2m_afirmar(!lista_iterador_avanzar(NULL), 
               "No se puede avanzar con un iterador NULL.");

  lista_t *lista_vacia = lista_crear();
  lista_iterador_t *iterador_lista_vacia = lista_iterador_crear(lista_vacia);

  pa2m_afirmar(!lista_iterador_avanzar(iterador_lista_vacia), 
               "No se puede avanzar en una lista vacia.");
  lista_iterador_destruir(iterador_lista_vacia);

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista_iterador_t *iterador1 = lista_iterador_crear(lista);

  pa2m_afirmar(!lista_iterador_avanzar(iterador1), 
  "Al avanzar el iterador en una lista con un elemento, el elemento actual\n\
  del iterador termina apuntando a NULL");
  lista_iterador_destruir(iterador1);

  lista = lista_insertar(lista, &elemento_prueba_1);
  lista_iterador_t *iterador2 = lista_iterador_crear(lista);
  pa2m_afirmar(lista_iterador_avanzar(iterador2), 
  "Si en una lista de mas de un elemento, el elemento actual del iterador\n\
  no apunta al último elemento de la lista, se puede avanzar el iterador");
  
  lista_iterador_avanzar(iterador2);
  pa2m_afirmar(!lista_iterador_avanzar(iterador2), 
  "Al avanzar el iterador en una lista con mas de un elemento cuando el\n\
  elemento actual del iterador apunta al último elemento de la lista, el\n\
  elemento actual del iterador termina apuntando a NULL");
  lista_iterador_destruir(iterador2);

  lista_destruir(lista_vacia);
  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_iterador_elemento_actual
 */ 
void lista_probar_iterador_elemento_actual()
{
  pa2m_nuevo_grupo("Elemento actual de un iterador externo");

  int elemento_prueba_1 = 10;
  int elemento_prueba_2 = 11;

  pa2m_afirmar(lista_iterador_elemento_actual(NULL) == NULL, 
               "No hay un elemento actual para un iterador NULL.");

  lista_t *lista_vacia = lista_crear();
  lista_iterador_t *iterador_lista_vacia = lista_iterador_crear(lista_vacia);

  void *elemento_actual = lista_iterador_elemento_actual(iterador_lista_vacia);
  pa2m_afirmar(elemento_actual == NULL, 
               "No se puede obtener el elemento actual de una lista vacia.");
  lista_iterador_destruir(iterador_lista_vacia);

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista_iterador_t *iterador = lista_iterador_crear(lista);

  elemento_actual = lista_iterador_elemento_actual(iterador);
  pa2m_afirmar(elemento_actual != NULL,
  "El nodo actual del iterador no es NULL y se devuelve su elemento.");

  lista_iterador_avanzar(iterador);
  lista_iterador_avanzar(iterador);
  elemento_actual = lista_iterador_elemento_actual(iterador);
  pa2m_afirmar(elemento_actual == NULL,
  "El nodo actual del iterador es NULL y se devuelve NULL.");
  lista_iterador_destruir(iterador);

  lista_destruir(lista_vacia);
  lista_destruir(lista);
}


/*
 * Se realizan las pruebas sobre la función lista_iterador_destruir
 */
void lista_probar_destruccion_iterador()
{
  pa2m_nuevo_grupo("Destruccion del iterador externo");

  lista_iterador_t *iterador_inexistente = NULL;
  bool iterador_destruido = false;
  lista_iterador_destruir(iterador_inexistente);
  iterador_destruido = true;
  pa2m_afirmar(iterador_destruido, "Se libera un iterador NULL.");

  lista_t *lista = lista_crear();
  lista_iterador_t *iterador = lista_iterador_crear(lista);
  iterador_destruido = false;
  lista_iterador_destruir(iterador);
  iterador_destruido = true;
  pa2m_afirmar(iterador != NULL, "Se libera un iterador no NULL.");

  lista_destruir(lista);
}


/*
 * Se reciben 2 punteros a enteros como punteros genéricos de cualquier tipo 
 * de dato.
 *
 * Se devuelve un booleano que dice si entero2 divide a entero1 
 * (entero2 | entero1)
 */
bool segundo_divide_al_primero(void *elemento1, void *elemento2)
{
  int *entero1 = (int *) elemento1;
  int *entero2 = (int *) elemento2;

  if (((*entero1) % (*entero2)) == 0)
    return true;

  return false;
}


/*
 * Se realizan las pruebas sobre la función lista_con_cada_elemento
 */ 
void lista_probar_iterador_interno()
{
  pa2m_nuevo_grupo("Iterador interno de una lista");

  int elemento_prueba_1 = 36;
  int elemento_prueba_2 = 27;
  int elemento_prueba_3 = 6;
  int elemento_prueba_4 = 2;
  int elemento_prueba_5 = 3;
  int elemento_prueba_6 = 7;

  size_t elementos_iterados = lista_con_cada_elemento(NULL, 
                              segundo_divide_al_primero, &elemento_prueba_1);
  pa2m_afirmar(elementos_iterados == 0, 
               "No se pueden iterar elementos en una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  elementos_iterados = lista_con_cada_elemento(lista_vacia, NULL, 
                                               &elemento_prueba_3);
  pa2m_afirmar(elementos_iterados == 0, 
               "No se pueden iterar elementos utilizando una función NULL.");

  elementos_iterados = lista_con_cada_elemento(lista_vacia, 
                       segundo_divide_al_primero, &elemento_prueba_2);
  pa2m_afirmar(elementos_iterados == 0, 
               "No hay elementos para iterar en una lista vacia.");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_3);
  lista = lista_insertar(lista, &elemento_prueba_2);

  elementos_iterados = lista_con_cada_elemento(lista, 
                       segundo_divide_al_primero, &elemento_prueba_6);
  pa2m_afirmar(elementos_iterados == 1, "En una lista de al menos un \n\
  elemento, se itera sobre un solo elemento y se deja de iterar cuando la\n\
  función del puntero a función ya no se cumple.");

  elementos_iterados = lista_con_cada_elemento(lista, 
                       segundo_divide_al_primero, &elemento_prueba_4);
  pa2m_afirmar(elementos_iterados == 3, "En una lista de al menos un \n\
  elemento, se itera sobre algunos elementos y se deja de iterar cuando la\n\
  función del puntero a función ya no se cumple.");

  elementos_iterados = lista_con_cada_elemento(lista, 
                       segundo_divide_al_primero, &elemento_prueba_5);
  pa2m_afirmar(elementos_iterados == lista_tamanio(lista), 
  "En una lista de al menos un elemento, se itera sobre todos los elementos\n\
  de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


/*
 * Se realizan las pruebas sobre las operaciones de una lista
 */ 
void pruebas_lista()
{
  lista_probar_creacion();
  lista_probar_insercion_al_final();
  lista_probar_eliminacion_al_final();
  lista_probar_insercion_en_posicion();
  lista_probar_eliminacion_en_posicion();
  lista_probar_buscar_por_posicion();
  lista_probar_buscar_elemento();
  lista_probar_obtener_primer_elemento();
  lista_probar_obtener_ultimo_elemento();
  lista_probar_vacia_o_inexistente();
  lista_probar_tamanio();
  lista_probar_destruccion();
  lista_probar_destruccion_total();

  lista_probar_creacion_iterador();
  lista_probar_iterador_siguiente();
  lista_probar_iterador_avanzar();
  lista_probar_iterador_elemento_actual();
  lista_probar_destruccion_iterador();
  lista_probar_iterador_interno();
}


/*
 * Se realizan las pruebas sobre la funcion pila_crear 
 */ 
void pila_probar_creacion()
{
  pa2m_nuevo_grupo("Creación de una pila");

  pila_t *pila = pila_crear();
  pa2m_afirmar(pila != NULL, "Se crea la pila exitosamente.");
  pa2m_afirmar(pila != NULL && pila_tope(pila) == NULL, 
               "El tope de la pila está inicializado en NULL.");
  pa2m_afirmar(pila != NULL && pila_vacia(pila), 
               "La cantidad de elementos de la pila se inicializa en 0.");

  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_apilar
 */ 
void pila_probar_apilar()
{
  pa2m_nuevo_grupo("Apilar sobre una pila");

  pila_t *pila = pila_crear();

  int elemento_prueba_1 = 5;
  char elemento_prueba_2 = 'l';

  pa2m_afirmar(pila_apilar(NULL, &elemento_prueba_1) == NULL, 
               "No se apila sobre una pila NULL.");

  pila = pila_apilar(pila, &elemento_prueba_1);
  pa2m_afirmar(pila != NULL, 
               "Se retorna la pila al apilar un elemento sobre ella.");
  pa2m_afirmar(pila != NULL, "Se apila exitosamente sobre una pila vacia.");
  pa2m_afirmar(pila!= NULL && pila_tamanio(pila) == 1, 
               "La cantidad de elementos de la pila aumenta en 1.");

  size_t cantidad_auxiliar = pila_tamanio(pila);
  pila = pila_apilar(pila, &elemento_prueba_2);
  pa2m_afirmar(pila != NULL && pila_tamanio(pila) == cantidad_auxiliar + 1, 
               "Se apila sobre una pila con al menos un elemento.");

  pila = pila_apilar(pila, NULL);
  pa2m_afirmar(pila != NULL, "Se apila un elemento NULL sobre la pila.");

  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_desapilar
 */ 
void pila_probar_desapilar()
{
  pa2m_nuevo_grupo("Desapilar sobre una pila");

  pila_t *pila = pila_crear();

  int elemento_prueba_1 = 1;
  int elemento_prueba_2 = 88;

  pila = pila_apilar(pila, &elemento_prueba_2);
  pila = pila_apilar(pila, NULL);
  pila = pila_apilar(pila, &elemento_prueba_1);

  pa2m_afirmar(pila_desapilar(NULL) == NULL, 
               "No se apila sobre una pila NULL.");

  pila_t *pila_vacia = pila_crear();
  void *elemento_eliminado = pila_desapilar(pila_vacia);
  pa2m_afirmar(elemento_eliminado == NULL, 
               "No se puede desapilar sobre una pila vacia.");

  size_t cantidad_auxiliar = pila_tamanio(pila);
  elemento_eliminado = pila_desapilar(pila);

  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se desapila un elemento de la pila.");
  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se devuelve el elemento desapilado.");
  pa2m_afirmar(pila_tamanio(pila) == cantidad_auxiliar - 1, 
               "La cantidad de elementos de la pila se reduce en 1");

  elemento_eliminado = pila_desapilar(pila);
  pa2m_afirmar(elemento_eliminado == NULL, 
               "Se desapila un elemento NULL de la pila.");

  pila_destruir(pila_vacia);
  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_tope
 */ 
void pila_probar_tope()
{
  pa2m_nuevo_grupo("Tope de una pila");

  pila_t *pila = pila_crear();

  char elemento_prueba_1 = '|';
  char elemento_prueba_2 = '_';

  pa2m_afirmar(pila_tope(NULL) == NULL, 
               "Se retorna NULL al buscar el tope de una pila NULL.");
  
  void *elemento_tope = pila_tope(pila);
  pa2m_afirmar(elemento_tope == NULL, 
               "Se retorna NULL al buscar el tope de una pila vacia.");
  
  pila = pila_apilar(pila, &elemento_prueba_1);
  pila = pila_apilar(pila, &elemento_prueba_2);
  elemento_tope = pila_tope(pila);
  pa2m_afirmar(pila != NULL && elemento_tope != NULL, 
  "Se retorna el elemento dentro del tope en una pila con al menos un\n\
  elemento.");

  pila = pila_apilar(pila, NULL);
  elemento_tope = pila_tope(pila);
  pa2m_afirmar(elemento_tope == NULL, 
               "Se retorna un elemento NULL del tope de la pila.");

  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_tamanio
 */ 
void pila_probar_tamanio()
{
  pa2m_nuevo_grupo("Tamaño de una pila");

  int elemento_prueba = 11;

  pila_t *pila = pila_crear();

  size_t tamanio_pila = pila_tamanio(NULL);
  pa2m_afirmar(tamanio_pila == 0, "Se devuelven 0 elementos para una pila\n\
  NULL.");
 
  pila_t *pila_vacia = pila_crear();
  tamanio_pila = pila_tamanio(pila_vacia); 
  pa2m_afirmar(pila_vacia != NULL && tamanio_pila == 0, 
               "Se devuelven 0 elementos para una pila vacia.");

  pila = pila_apilar(pila, &elemento_prueba);
  tamanio_pila = pila_tamanio(pila); 
  pa2m_afirmar(pila != NULL && pila_tamanio(pila) > 0, 
  "Se devuelve la cantidad de elementos para una pila con al menos un\n\
  elemento.");

  pila_destruir(pila_vacia);
  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_vacia
 */
void pila_probar_vacia()
{
  pa2m_nuevo_grupo("Pila vacia/inexistente");

  int elemento_prueba = 9;

  pila_t *pila = pila_crear();

  pa2m_afirmar(pila_vacia(NULL), "Se devuelve true para una pila NULL.");

  pila_t *pila_sin_elementos = pila_crear();
  bool es_vacia = pila_vacia(pila_sin_elementos);
  pa2m_afirmar(es_vacia, "Se devuelve true para una pila vacia.");

  pila = pila_apilar(pila, &elemento_prueba);
  es_vacia = pila_vacia(pila);
  pa2m_afirmar(!es_vacia, 
               "Se devuelve false para una pila con al menos un elemento.");

  pila_destruir(pila_sin_elementos);
  pila_destruir(pila);
}


/*
 * Se realizan las pruebas sobre la funcion pila_destruir
 */ 
void pila_probar_destruir()
{
  pa2m_nuevo_grupo("Destrucción de una pila");

  int elemento_prueba_1 = 111;
  char elemento_prueba_2 = 'K';

  pila_t *pila_inexistente = NULL;
  bool pila_eliminada = false;
  pila_destruir(pila_inexistente);
  pila_eliminada = true;
  pa2m_afirmar(pila_eliminada, "Se libera una pila NULL.");

  pila_t *pila_sin_elementos = pila_crear();
  pila_eliminada = false;
  pila_destruir(pila_sin_elementos);
  pila_eliminada = true;
  pa2m_afirmar(pila_eliminada, "Se libera una pila vacia");

  pila_t *pila = pila_crear();
  pila = pila_apilar(pila, &elemento_prueba_1);
  pila = pila_apilar(pila, &elemento_prueba_2);
  pila_destruir(pila);
  pa2m_afirmar(pila != NULL, 
  "Se libera una pila de al menos un elemento junto con todos sus nodos.");
}


/*
 * Se realizan las pruebas sobre las operaciones de una pila 
 */
void pruebas_pila()
{
  pila_probar_creacion();
  pila_probar_apilar();
  pila_probar_desapilar();
  pila_probar_tope();
  pila_probar_tamanio();
  pila_probar_vacia();
  pila_probar_destruir();
}


/*
 * Se realizan las pruebas sobre la funcion cola_crear
 */ 
void cola_probar_creacion()
{
  pa2m_nuevo_grupo("Creación de una cola");

  cola_t *cola = cola_crear();
  pa2m_afirmar(cola != NULL, "Se crea la cola exitosamente.");
  pa2m_afirmar(cola != NULL && cola_frente(cola) == NULL, 
               "El frente de la cola está inicializado en NULL.");
  pa2m_afirmar(cola != NULL && cola_vacia(cola), 
               "La cantidad de elementos de la cola se inicializa en 0.");

  cola_destruir(cola);
}


/*
 * Se realizan las pruebas sobre la funcion cola_encolar
 */ 
void cola_probar_encolar()
{
  pa2m_nuevo_grupo("Encolar sobre una cola");

  cola_t *cola = cola_crear();

  int elemento_prueba_1 = 7;
  char elemento_prueba_2 = '*';

  pa2m_afirmar(cola_encolar(NULL, &elemento_prueba_1) == NULL, 
               "No se encola sobre una cola NULL.");

  cola = cola_encolar(cola, &elemento_prueba_1);
  pa2m_afirmar(cola != NULL, "Se retorna la cola al encolar sobre ella.");
  pa2m_afirmar(cola != NULL, "Se encola sobre una cola vacia.");
  pa2m_afirmar(cola_tamanio(cola) == 1, "La cantidad de elementos de la cola\n\
  aumenta en 1.");

  size_t cantidad_auxiliar = cola_tamanio(cola);
  cola = cola_encolar(cola, &elemento_prueba_2);
  pa2m_afirmar(cola_tamanio(cola) == cantidad_auxiliar + 1, 
               "Se encola sobre una cola con al menos un elemento.");

  cola = cola_encolar(cola, NULL);
  pa2m_afirmar(cola != NULL, "Se encola un elemento NULL a la cola.");
  
  cola_destruir(cola);  
}


/*
 * Se realizan las pruebas sobre la funcion cola_desencolar
 */ 
void cola_probar_desencolar()
{
  pa2m_nuevo_grupo("Desencolar sobre una cola");

  cola_t *cola = cola_crear();

  char elemento_prueba_1 = 'j';
  char elemento_prueba_2 = 'k';

  pa2m_afirmar(cola_desencolar(NULL) == NULL, 
               "No se desencola sobre una cola NULL.");

  cola = cola_encolar(cola, &elemento_prueba_1);
  cola = cola_encolar(cola, NULL);
  cola = cola_encolar(cola, &elemento_prueba_2);

  cola_t *cola_vacia = cola_crear();
  void *elemento_eliminado = cola_desencolar(cola_vacia);
  pa2m_afirmar(elemento_eliminado == NULL, 
               "No se puede desencolar sobre una cola vacia.");

  size_t cantidad_auxiliar = cola_tamanio(cola);
  elemento_eliminado = cola_desencolar(cola);
  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se desencola un elemento de la cola.");
  pa2m_afirmar(elemento_eliminado != NULL, 
               "Se devuelve el elemento desencolado.");
  pa2m_afirmar(cola_tamanio(cola) == cantidad_auxiliar - 1, 
               "La cantidad de elementos de la cola se reduce en 1");

  elemento_eliminado = cola_desencolar(cola);
  pa2m_afirmar(elemento_eliminado == NULL, 
               "Se desencola un elemento NULL de la cola.");

  cola_destruir(cola_vacia);
  cola_destruir(cola);
}


/*
 * Se realizan las pruebas sobre la funcion cola_frente
 */ 
void cola_probar_frente()
{
  pa2m_nuevo_grupo("Frente de una cola");

  cola_t *cola = cola_crear();

  char elemento_prueba = '{';

  pa2m_afirmar(cola_frente(NULL) == NULL, 
  "Se retorna NULL al buscar el elemento del frente de una cola NULL.");
  
  void *elemento_frente_1 = cola_frente(cola);
  pa2m_afirmar(elemento_frente_1 == NULL, 
  "Se retorna NULL al buscar el elemento del frente de una cola vacia.");
  
  cola = cola_encolar(cola, NULL);
  elemento_frente_1 = cola_frente(cola);
  pa2m_afirmar(cola != NULL, 
  "Se retorna el elemento dentro del frente de una cola con al menos un\n\
  elemento.");

  cola = cola_encolar(cola, &elemento_prueba);
  void *elemento_frente_2 = cola_frente(cola);
  pa2m_afirmar(cola != NULL && elemento_frente_2 == elemento_frente_1, 
  "El elemento del frente de la cola no cambia al encolar un elemento");

  cola_destruir(cola);
}


/*
 * Se realizan las pruebas sobre la funcion cola_tamanio
 */ 
void cola_probar_tamanio()
{
  pa2m_nuevo_grupo("Tamaño de una cola");

  int elemento_prueba = 99;

  cola_t *cola = cola_crear();

  size_t tamanio_cola = cola_tamanio(NULL);
  pa2m_afirmar(tamanio_cola == 0, 
  "Se devuelve 0 elementos para una cola NULL.");
 
  cola_t *cola_vacia = cola_crear();
  tamanio_cola = cola_tamanio(cola_vacia); 
  pa2m_afirmar(cola_vacia != NULL && cola_tamanio(cola) == 0, 
  "Se devuelve 0 elementos para una cola vacia.");

  cola = cola_encolar(cola, &elemento_prueba);
  tamanio_cola = cola_tamanio(cola);
  pa2m_afirmar(cola != NULL && cola_tamanio(cola) > 0, 
  "Se devuelve la cantidad de elementos para una cola con al menos un\n\
  elemento.");

  cola_destruir(cola_vacia);
  cola_destruir(cola);
}


/*
 * Se realizan las pruebas sobre la funcion cola_vacia
 */ 
void cola_probar_vacia()
{
  pa2m_nuevo_grupo("Cola vacia/inexistente");

  int elemento_prueba = 9;

  cola_t *cola = cola_crear();

  pa2m_afirmar(cola_vacia(NULL), "Se devuelve true para una cola NULL.");

  cola_t *cola_sin_elementos = cola_crear();
  bool es_vacia = cola_vacia(cola_sin_elementos);
  pa2m_afirmar(es_vacia, "Se devuelve true para una cola vacia.");

  cola = cola_encolar(cola, &elemento_prueba);
  es_vacia = cola_vacia(cola);
  pa2m_afirmar(!es_vacia, 
               "Se devuelve false para una cola con al menos un elemento.");

  cola_destruir(cola_sin_elementos);
  cola_destruir(cola);
}


/*
 * Se realizan las pruebas sobre la funcion cola_destruir
 */ 
void cola_probar_destruir()
{
  pa2m_nuevo_grupo("Destrucción de una cola");

  int elemento_prueba_1 = 1;
  char elemento_prueba_2 = 'Z';

  cola_t *cola_inexistente = NULL;
  bool cola_destruida = false;
  cola_destruir(cola_inexistente);
  cola_destruida = true;
  pa2m_afirmar(cola_destruida, "Se libera una cola NULL.");

  cola_t *cola_sin_elementos = cola_crear();
  cola_destruida = false;
  cola_destruir(cola_sin_elementos);
  cola_destruida = true;
  pa2m_afirmar(cola_destruida, "Se libera una cola vacia");

  cola_t *cola = cola_crear();
  cola = cola_encolar(cola, &elemento_prueba_2);
  cola = cola_encolar(cola, &elemento_prueba_1);
  cola = cola_encolar(cola, &elemento_prueba_1);
  cola_destruida = false;
  cola_destruir(cola);
  cola_destruida = true;
  pa2m_afirmar(cola_destruida, 
  "Se libera una cola de al menos un elemento junto con todos sus nodos.");
}


/*
 * Se realizan las pruebas sobre las operaciones de una cola
 */
void pruebas_cola()
{
  cola_probar_creacion();
  cola_probar_encolar();
  cola_probar_desencolar();
  cola_probar_frente();
  cola_probar_tamanio();
  cola_probar_vacia();
  cola_probar_destruir();
}


int main() {  
  pruebas_lista();
  pruebas_pila();
  pruebas_cola();

  return pa2m_mostrar_reporte();
}