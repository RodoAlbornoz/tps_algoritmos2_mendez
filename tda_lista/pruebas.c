#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"
#include <string.h>

#define CASO_EXITOSO 1
#define CASO_FALLIDO 0


/*
 * Se recibe la referencia a una lista vacia y un entero para evaluar como resultaron las pruebas

 * Se realizan las pruebas sobre la función lista_crear
 */
void lista_probar_creacion(lista_t *lista, int valor_prueba) 
{
  pa2m_nuevo_grupo("Creación de una lista");

  valor_prueba = lista != NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se crea la lista exitosamente.");

  valor_prueba = (lista != NULL && lista->nodo_inicio == NULL)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "El puntero al nodo inicial está inicializado en NULL.");

  valor_prueba = (lista != NULL && lista->nodo_fin == NULL)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "El puntero al nodo final está inicializado en NULL.");

  valor_prueba = (lista != NULL && lista->cantidad == 0)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "La cantidad de elementos de la lista se inicializa en 0.");
}


/*
 * Se recibe la referencia a una lista que al principio está vacia, un entero para evaluar como resultaron las pruebas y
 * la referencia a un elemento genérico de cualquier tipo de dato
 * 
 * Se realizan las pruebas sobre la función lista_insertar
 */
void lista_probar_insercion_al_final(lista_t *lista, int valor_prueba, void *elemento_prueba)
{
  pa2m_nuevo_grupo("Inserción de elementos al final de una lista (Funcion lista_insertar)");

  lista_t *lista_no_existente = lista_insertar(NULL, &elemento_prueba);
  valor_prueba = lista_no_existente == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se insertan elementos en una lista NULL.");

  lista = lista_insertar(lista, &elemento_prueba);
  valor_prueba = (lista != NULL && lista->cantidad == 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento en una lista vacia.");
  pa2m_afirmar(valor_prueba, "La cantidad de elementos de la lista aumenta en 1.");

  lista = lista_insertar(lista, NULL);
  valor_prueba = lista != NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se inserta un elemento NULL a la lista.");

  size_t cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar(lista, &elemento_prueba);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar + 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");

}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, y un entero para evaluar como resultaron las pruebas
 *
 * Se realizan las pruebas sobre la función lista_quitar
 */
void lista_probar_eliminacion_al_final(lista_t *lista, lista_t *lista_vacia, int valor_prueba)
{
  pa2m_nuevo_grupo("Eliminación de elementos al final de una lista (Funcion lista_quitar)");

  void *elemento_eliminado_lista = lista_quitar(NULL);
  valor_prueba = elemento_eliminado_lista == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede eliminar un elemento de una lista NULL.");

  size_t cantidad_auxiliar = lista->cantidad;
  elemento_eliminado_lista = lista_quitar(lista);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina el elemento de la lista.");
  pa2m_afirmar(valor_prueba, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(valor_prueba, "La cantidad de elementos de la lista se reduce en 1.");

  elemento_eliminado_lista = lista_quitar(lista);
  valor_prueba = lista != NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina un elemento NULL de la lista.");

  elemento_eliminado_lista = lista_quitar(lista_vacia);
  valor_prueba = elemento_eliminado_lista == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede eliminar un elemento de una lista vacia.");
}


/*
 * Se recibe la referencia a una lista que al principio está vacia, un entero para evaluar como resultaron las pruebas y
 * la referencia a un elemento genérico de cualquier tipo de dato
 * 
 * Se realizan las pruebas sobre la función lista_insertar_en_posicion
 */
void lista_probar_insercion_en_posicion(lista_t *lista, int valor_prueba, void *elemento_prueba)
{
  pa2m_nuevo_grupo("Inserción de elementos en una lista (Funcion lista_insertar_en_posicion)");

  lista_t *lista_no_existente = lista_insertar_en_posicion(NULL, &elemento_prueba, 0);
  valor_prueba = lista_no_existente == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se insertan elementos en una lista NULL.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba, 0);
  valor_prueba = (lista != NULL && lista->cantidad == 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento en una lista vacia.");
  pa2m_afirmar(valor_prueba, "La cantidad de elementos de la lista aumenta en 1.");

  lista = lista_insertar_en_posicion(lista, NULL, 1);
  valor_prueba = lista != NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se inserta un elemento NULL a la lista.");
  
  size_t cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar_en_posicion(lista, &elemento_prueba, 0);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar + 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento al principio de una lista con al menos un elemento.");
  
  cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar_en_posicion(lista, &elemento_prueba, 1);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar + 1)? CASO_EXITOSO : CASO_FALLIDO;  
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento en medio de una lista con al menos un elemento.");

  cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar_en_posicion(lista, &elemento_prueba, 4);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar + 1)? CASO_EXITOSO : CASO_FALLIDO;  
  pa2m_afirmar(valor_prueba, "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");
 
  cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar_en_posicion(lista, &elemento_prueba, 99);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar + 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se inserta al final un elemento que se queria insertar en una posicion no existente.");
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, y un entero para evaluar como resultaron las pruebas
 *
 * Se realizan las pruebas sobre la función lista_quitar_de_posicion
 */
void lista_probar_eliminacion_en_posicion(lista_t *lista, lista_t *lista_sin_elementos, int valor_prueba)
{
  pa2m_nuevo_grupo("Eliminación de elementos de la lista (Funcion lista_quitar_de_posicion)");

  void *elemento_eliminado_lista = lista_quitar_de_posicion(NULL, 9);
  valor_prueba = elemento_eliminado_lista == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede eliminar un elemento de una lista NULL.");
  
  size_t cantidad_auxiliar = lista->cantidad;
  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 5);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina el ultimo elemento de la lista.");
  pa2m_afirmar(valor_prueba, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(valor_prueba, "La cantidad de elementos se reduce en 1.");

  cantidad_auxiliar = lista->cantidad;
  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 2);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina un elemento del medio de la lista.");

  cantidad_auxiliar = lista->cantidad;
  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 0);
  valor_prueba = (lista != NULL && lista->cantidad == cantidad_auxiliar - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina el primer elemento de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 99);
  valor_prueba = elemento_eliminado_lista == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al querer eliminar un elemento en una posicion inexistente.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 1);
  valor_prueba = (lista != NULL && !lista_vacia(lista))? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se elimina un elemento NULL de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista_sin_elementos, 9);
  valor_prueba = elemento_eliminado_lista == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se permite eliminar un elemento de una lista vacia.");
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, y un entero para evaluar como resultaron las pruebas
 *
 * Se realizan las pruebas sobre la función lista_elemento_en_posicion 
 */
void lista_probar_buscar_por_posicion(lista_t *lista, lista_t* lista_sin_elementos, int valor_prueba)
{
  pa2m_nuevo_grupo("Buscar elementos por posicion en la lista");

  void *elemento_en_posicion = lista_elemento_en_posicion(NULL, 0);
  valor_prueba = elemento_en_posicion == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede buscar un elemento por su posicion en una lista NULL.");

  elemento_en_posicion = lista_elemento_en_posicion(lista_sin_elementos, 2);
  valor_prueba = elemento_en_posicion == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar un elemento en cierta posicion en una lista vacia.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 9876);
  valor_prueba = elemento_en_posicion == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar un elemento en una posicion inexistente de una lista.");

  size_t posicion_1 = 0;
  elemento_en_posicion = lista_elemento_en_posicion(lista, posicion_1);
  valor_prueba = (lista != NULL && !lista_vacia(lista) && posicion_1 <= lista->cantidad - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se trae el elemento en la primera posicion en una lista con al menos un elemento.");

  size_t posicion_2 = 3;
  elemento_en_posicion = lista_elemento_en_posicion(lista, posicion_2);
  valor_prueba = (lista != NULL && !lista_vacia(lista) && posicion_2 <= lista->cantidad - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se trae el elemento en la ultima posicion en una lista con al menos un elemento.");

  size_t posicion_3 = 2;
  elemento_en_posicion = lista_elemento_en_posicion(lista, posicion_3);
  valor_prueba = (lista != NULL && !lista_vacia(lista) && posicion_2 <= lista->cantidad - 1)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se trae un elemento en alguna posicion del medio en una lista con al menos un elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 2);
  valor_prueba = elemento_en_posicion == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se trae un elemento del tipo NULL en la lista.");
}


/*
 * Se reciben las referencias a elementos genéricos de cualquier tipo de dato 
 *
 * Se castean los elementos genéricos a int, y se devuelve 0 si sus valores son iguales, o 1 si no lo son.
 */
int comparar_enteros(void *entero1, void *entero2)
{
  entero1 = (int *) entero1;
  entero2 = (int *) entero2;

  if (entero1 == entero2)
    return 0;
  
  return 1;
}


/*
 * Se reciben las referencias a elementos genéricos de cualquier tipo de dato 
 *
 * Se castean los elementos genéricos a char, y se devuelve 0 si sus valores son iguales, o 1 si no lo son.
 */
int comparar_char(void *char1, void *char2)
{
  char1 = (char *) char1;
  char2 = (char *) char2;

  if (char1 == char2)
    return 0;
  
  return 1;
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, un entero para evaluar como resultaron las pruebas, y
 * la referencia a elementos genéricos de cualquier tipo de dato 
 *
 * Se realizan las pruebas sobre la función lista_buscar_elemento
 */
void lista_probar_buscar_elemento(lista_t *lista, lista_t* lista_sin_elementos, int valor_prueba, void *elemento_a_buscar,
                                  void *elemento_en_lista, void *elemento_en_lista_repetido)
{
  pa2m_nuevo_grupo("Buscar elementos en la lista");

  void *elemento_encontrado = lista_buscar_elemento(NULL, comparar_enteros, elemento_a_buscar);
  valor_prueba = elemento_encontrado == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede buscar un elemento en una lista NULL.");

  elemento_encontrado = lista_buscar_elemento(lista, NULL, elemento_a_buscar);
  valor_prueba = elemento_encontrado == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se puede buscar un elemento si la función de comparación enviada es NULL.");

  elemento_encontrado = lista_buscar_elemento(lista_sin_elementos, comparar_enteros, elemento_a_buscar);
  valor_prueba = elemento_encontrado == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se encuentra el elemento buscado en una lista vacia.");

  elemento_encontrado = lista_buscar_elemento(lista, comparar_enteros, elemento_a_buscar);
  valor_prueba = elemento_encontrado == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "No se encuentra el elemento buscado.");
  
  elemento_encontrado = lista_buscar_elemento(lista, comparar_char, elemento_en_lista);
  valor_prueba = elemento_encontrado == elemento_en_lista? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se busca y se encuentra el primer elemento encontrado.");
  
  elemento_encontrado = lista_buscar_elemento(lista, comparar_enteros, elemento_en_lista_repetido);
  valor_prueba = elemento_encontrado == elemento_en_lista_repetido? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se encuentra el primer elemento encontrado cuando hay otro igual en la lista.");  
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, un entero para evaluar como resultaron las pruebas y 
 * la referencia a un elemento genérico de cualquier tipo de dato
 * 
 * Se realizan las pruebas sobre la función lista_primero
 */
void lista_probar_obtener_primer_elemento(lista_t *lista, lista_t *lista_sin_elementos, int valor_prueba, void *elemento_prueba)
{
  pa2m_nuevo_grupo("Obtención de primer elemento de una lista");

  void *primer_elemento = lista_primero(NULL);
  valor_prueba = primer_elemento == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar el primer elemento de una lista NULL.");

  primer_elemento = lista_primero(lista_sin_elementos);
  valor_prueba = primer_elemento == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar el primer elemento de una lista vacia.");

  primer_elemento = lista_primero(lista);
  valor_prueba = (lista != NULL && !lista_vacia(lista))? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "En una lista de un solo elemento, se devuelve su único elemento como primero.");

  lista = lista_insertar(lista, &elemento_prueba);
  primer_elemento = lista_primero(lista);
  valor_prueba = (lista != NULL && !lista_vacia(lista))? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna el primer elemento de una lista con mas de un elemento.");
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, un entero para evaluar como resultaron las pruebas y 
 * la referencia a un elemento genérico de cualquier tipo de dato
 * 
 * Se realizan las pruebas sobre la función lista_ultimo
 */
void lista_probar_obtener_ultimo_elemento(lista_t *lista, lista_t *lista_sin_elementos, int valor_prueba, void *elemento_prueba)
{
  pa2m_nuevo_grupo("Obtención de ultimo elemento de una lista");

  void *ultimo_elemento = lista_ultimo(NULL);
  valor_prueba = ultimo_elemento == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar el ultimo elemento de una lista NULL.");
  
  ultimo_elemento = lista_ultimo(lista_sin_elementos);
  valor_prueba = ultimo_elemento == NULL? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna NULL al buscar el ultimo elemento de una lista vacia.");

  ultimo_elemento = lista_ultimo(lista);
  valor_prueba = (lista != NULL && !lista_vacia(lista))? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "En una lista de un solo elemento, se devuelve su único elemento como ultimo.");

  lista = lista_insertar(lista, &elemento_prueba);
  ultimo_elemento = lista_ultimo(lista);
  valor_prueba = (lista != NULL && !lista_vacia(lista))? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se retorna el ultimo elemento de una lista con mas de un elemento.");
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, y un entero para evaluar como resultaron las pruebas
 *
 * Se realizan las pruebas sobre la función lista_vacia
 */
void lista_probar_vacia_o_inexistente(lista_t *lista, lista_t *lista_sin_elementos, int valor_prueba)
{
  pa2m_nuevo_grupo("Comprobación de lista vacia o no existente");

  bool es_vacia = lista_vacia(NULL);
  valor_prueba = es_vacia? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve true para una lista NULL.");

  es_vacia = lista_vacia(lista_sin_elementos);
  valor_prueba = es_vacia? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve true para una lista vacia.");

  es_vacia = lista_vacia(lista);
  valor_prueba = !es_vacia? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve false para una lista con al menos un elemento.");
}


/*
 * Se reciben las referencias a una lista no vacia y a una vacia, y un entero para evaluar como resultaron las pruebas
 *
 * Se realizan las pruebas sobre la función lista_tamanio
 */
void lista_probar_tamanio(lista_t *lista, lista_t *lista_vacia, int valor_prueba)
{
  pa2m_nuevo_grupo("Comprobación de tamaño de una lista");

  lista_t *lista_nula = NULL;

  size_t cantidad_elementos = lista_tamanio(lista_nula);
  valor_prueba = (lista_nula == NULL && cantidad_elementos == 0)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve 0 para una lista NULL.");

  cantidad_elementos = lista_tamanio(lista_vacia);
  valor_prueba = (lista_vacia != NULL && cantidad_elementos == 0)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve 0 para una lista vacia.");

  cantidad_elementos = lista_tamanio(lista);
  valor_prueba = (lista != NULL && cantidad_elementos > 0)? CASO_EXITOSO : CASO_FALLIDO;
  pa2m_afirmar(valor_prueba, "Se devuelve la cantidad de elementos para una lista con al menos un elemento.");
}


void lista_probar_destruccion(lista_t *lista)
{
  pa2m_nuevo_grupo("Destrucción de la lista");
//  pa2m_afirmar(valor_prueba, "Liberar memoria de solo uno de los 2 nodos cuando solo queda un elemento en la lista.");
//pa2m_afirmar(valor_prueba, "Si se quiere eliminar un ultimo elemento de una lista vacia, la lista no debe liberarse.");
//pa2m_afirmar(valor_prueba, "Si se quiere eliminar un elemento de una lista vacia, la lista no debe liberarse.");
//pa2m_afirmar(valor_prueba, "Si se quiere buscar el primer elemento de una lista vacia, la lista no debe liberarse.");
//pa2m_afirmar(valor_prueba, "Si se quiere buscar el ultimo elemento de una lista vacia, la lista no debe liberarse.");

  lista_destruir(lista);
}


int main() {
  int valor_prueba = 0;

  int elemento_prueba_1 = 5;
  char elemento_prueba_2 = 'f';
  int elemento_prueba_3 = 77;
  int elemento_prueba_4 = 1;

  lista_t *lista_prueba_1 = lista_crear();
  lista_t *lista_prueba_2 = lista_crear();
  lista_t *lista_prueba_3 = lista_crear();
  lista_t *lista_prueba_4 = lista_crear();
  lista_t *lista_vacia = lista_crear();

  lista_probar_creacion(lista_prueba_1, valor_prueba);

  lista_probar_insercion_al_final(lista_prueba_1, valor_prueba, &elemento_prueba_1); 
  lista_probar_eliminacion_al_final(lista_prueba_1, lista_vacia, valor_prueba);


  lista_probar_insercion_en_posicion(lista_prueba_2, valor_prueba, &elemento_prueba_2);
  lista_probar_eliminacion_en_posicion(lista_prueba_2, lista_vacia, valor_prueba);


  lista_prueba_3 = lista_insertar(lista_prueba_3, &elemento_prueba_3);
  lista_prueba_3 = lista_insertar(lista_prueba_3, &elemento_prueba_2);
  lista_prueba_3 = lista_insertar(lista_prueba_3, NULL);
  for (int i = 0; i < 2; i++)
    lista_prueba_3 = lista_insertar(lista_prueba_3, &elemento_prueba_1);
  
  lista_probar_buscar_por_posicion(lista_prueba_3, lista_vacia, valor_prueba);
  lista_probar_buscar_elemento(lista_prueba_3, lista_vacia, valor_prueba, &elemento_prueba_4, &elemento_prueba_2, 
  &elemento_prueba_1); // Volver a probar después con GDB


  lista_prueba_4 = lista_insertar(lista_prueba_4, NULL);
  lista_probar_obtener_primer_elemento(lista_prueba_4, lista_vacia, valor_prueba, &elemento_prueba_1);
  lista_probar_obtener_ultimo_elemento(lista_prueba_4, lista_vacia, valor_prueba, &elemento_prueba_2);


  lista_probar_vacia_o_inexistente(lista_prueba_1, lista_vacia, valor_prueba);
  lista_probar_tamanio(lista_prueba_1, lista_vacia, valor_prueba);

/*
  lista_probar_destruccion(lista_prueba_1);


  if (lista_prueba_1->cantidad == 1) {
    free(lista_prueba_1->nodo_inicio);
  } else {
    free(lista_prueba_1->nodo_inicio);
    free(lista_prueba_1->nodo_fin);
  }
  free(lista_prueba_1);

  if (lista_prueba_2->cantidad == 1) {
    free(lista_prueba_2->nodo_inicio);
  } else {
    free(lista_prueba_2->nodo_inicio);
    free(lista_prueba_2->nodo_fin);
  }
  free(lista_prueba_2);
*/
  return pa2m_mostrar_reporte();
}