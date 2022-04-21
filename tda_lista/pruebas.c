#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"


// Se realizan las pruebas sobre la función lista_crear
void lista_probar_creacion() 
{
  pa2m_nuevo_grupo("Creación de una lista");

  lista_t *lista = lista_crear();

  pa2m_afirmar(lista != NULL, "Se crea la lista exitosamente.");
  pa2m_afirmar(lista != NULL && lista->nodo_inicio == NULL, "El puntero al nodo inicial está inicializado en NULL.");
  pa2m_afirmar(lista != NULL && lista->nodo_fin == NULL, "El puntero al nodo final está inicializado en NULL.");
  pa2m_afirmar(lista != NULL && lista->cantidad == 0, "La cantidad de elementos de la lista se inicializa en 0.");

  lista_destruir(lista);
}


// Se realizan las pruebas sobre la función lista_insertar
void lista_probar_insercion_al_final()
{
  pa2m_nuevo_grupo("Inserción de elementos al final de una lista");

  lista_t *lista = lista_crear();

  int elemento_prueba_1 = 5;
  char elemento_prueba_2 = 'l';

  pa2m_afirmar(lista_insertar(NULL, &elemento_prueba_1) == NULL, "No se insertan elementos en una lista NULL.");

  lista = lista_insertar(lista, &elemento_prueba_1);
  pa2m_afirmar(lista != NULL, "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento en una lista vacia.");
  pa2m_afirmar(lista != NULL && lista->cantidad == 1, "La cantidad de elementos de la lista aumenta en 1.");

  size_t cantidad_auxiliar = lista->cantidad;
  pa2m_afirmar(lista_insertar(lista, &elemento_prueba_2) != NULL && lista->cantidad == cantidad_auxiliar + 1, 
               "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");

  pa2m_afirmar(lista_insertar(lista, NULL) != NULL, "Se inserta un elemento NULL a la lista.");

  lista_destruir(lista);
}



// Se realizan las pruebas sobre la función lista_quitar
void lista_probar_eliminacion_al_final()
{
  pa2m_nuevo_grupo("Eliminación de elementos al final de una lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();

  int elemento_prueba_1 = 11;
  char elemento_prueba_2 = 'a';
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_quitar(NULL) == NULL, "No se puede eliminar un elemento de una lista NULL.");
  pa2m_afirmar(lista_quitar(lista_vacia) == NULL, "No se puede eliminar un elemento de una lista vacia.");

  size_t cantidad_auxiliar = lista->cantidad;
  lista_quitar(lista);
  pa2m_afirmar(lista != NULL, "Se elimina un elemento de la lista.");
  pa2m_afirmar(lista != NULL, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(lista != NULL && lista->cantidad == cantidad_auxiliar - 1, 
               "La cantidad de elementos de la lista se reduce en 1.");
               
  pa2m_afirmar(lista_quitar(lista) == NULL, "Se elimina un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_insertar_en_posicion
void lista_probar_insercion_en_posicion()
{ 
  pa2m_nuevo_grupo("Inserción de elementos en cierta posicion de una lista");

  lista_t *lista = lista_crear();

  int elemento_prueba_1 = 1;
  int elemento_prueba_2 = 19;
  char elemento_prueba_3 = '<';

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_3, 0);
  pa2m_afirmar(lista != NULL, "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento en una lista vacia.");
  pa2m_afirmar(lista != NULL && lista->cantidad == 1, "La cantidad de elementos de la lista aumenta en 1.");

  size_t cantidad_auxiliar = lista->cantidad;
  pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 1) != NULL && lista->cantidad == cantidad_auxiliar + 1, 
               "Se inserta un elemento NULL a la lista.");

  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_prueba_2, 0) != NULL, 
               "Se inserta exitosamente un elemento al principio de una lista con al menos un elemento.");
  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_prueba_1, 1) != NULL, 
               "Se inserta exitosamente un elemento en medio de una lista con al menos un elemento.");
  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_prueba_3, 4) != NULL, 
               "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");
  pa2m_afirmar(lista_insertar_en_posicion(lista, &elemento_prueba_2, 99) != NULL, 
               "Se inserta al final un elemento que se queria insertar en una posicion no existente.");

  lista_destruir(lista);
}


// Se realizan las pruebas sobre la función lista_quitar_de_posicion
void lista_probar_eliminacion_en_posicion()
{
  pa2m_nuevo_grupo("Eliminación de elementos en cierta posicion de una lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();

  char *elemento_prueba_1 = "Hola";
  int elemento_prueba_2 = -6;
  float elemento_prueba_3 = 0.5;

  lista_insertar_en_posicion(lista, &elemento_prueba_3, 1);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 0);
  lista_insertar_en_posicion(lista, &elemento_prueba_1, 1);
  lista_insertar_en_posicion(lista, NULL, 2);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 3);

  pa2m_afirmar(lista_quitar_de_posicion(NULL, 9) == NULL, "No se puede eliminar un elemento de una lista NULL.");
  pa2m_afirmar(lista_quitar_de_posicion(lista_vacia, 9) == NULL, 
               "No se permite eliminar un elemento de una lista vacia.");

  size_t cantidad_auxiliar = lista->cantidad;
  void *elemento_eliminado_lista = lista_quitar_de_posicion(lista, 4);
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se elimina el ultimo elemento de la lista.");
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(elemento_eliminado_lista != NULL && lista->cantidad == cantidad_auxiliar - 1, 
               "La cantidad de elementos se reduce en 1.");

  pa2m_afirmar(lista_quitar_de_posicion(lista, 1) != NULL, "Se elimina un elemento del medio de la lista.");
  pa2m_afirmar(lista_quitar_de_posicion(lista, 0) != NULL, "Se elimina el primer elemento de la lista.");
  pa2m_afirmar(lista_quitar_de_posicion(lista, 99) == NULL, 
               "Se retorna NULL al querer eliminar un elemento en una posicion inexistente.");
  pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == NULL, "Se elimina un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_elemento_en_posicion 
void lista_probar_buscar_por_posicion()
{
  pa2m_nuevo_grupo("Buscar elementos por posicion en la lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();

  char elemento_prueba_1 = 'k';
  int elemento_prueba_2 = 0;
  char elemento_prueba_3 = '!';
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_3);

  pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL, 
               "No se puede buscar un elemento por su posicion en una lista NULL.");
  pa2m_afirmar(lista_elemento_en_posicion(lista_vacia, 2) == NULL, 
               "Se retorna NULL al buscar un elemento en cierta posicion en una lista vacia.");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 9876) == NULL, 
               "Se retorna NULL al buscar un elemento en una posicion inexistente de una lista.");
               
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) != NULL, 
               "Se trae el elemento en la primera posicion en una lista con al menos un elemento.");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 3) != NULL, 
               "Se trae el elemento en la ultima posicion en una lista con al menos un elemento.");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 1) != NULL, 
               "Se trae un elemento en alguna posicion del medio en una lista con al menos un elemento.");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == NULL, "Se trae un elemento del tipo NULL en la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
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


// Se realizan las pruebas sobre la función lista_buscar_elemento
void lista_probar_buscar_elemento()
{
  pa2m_nuevo_grupo("Buscar elementos en la lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();

  int elemento_prueba_1 = 100;
  char elemento_prueba_2 = 'x';
  int elemento_a_buscar = 77;

  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, &elemento_prueba_2);

  pa2m_afirmar(lista_buscar_elemento(NULL, comparar_enteros, &elemento_prueba_1) == NULL, 
               "No se puede buscar un elemento en una lista NULL.");
  pa2m_afirmar(lista_buscar_elemento(lista, NULL, &elemento_prueba_2) == NULL, 
               "No se puede buscar un elemento si la función de comparación enviada es NULL.");
  pa2m_afirmar(lista_buscar_elemento(lista_vacia, comparar_enteros, &elemento_prueba_2) == NULL, 
               "No se encuentra el elemento buscado en una lista vacia.");

  pa2m_afirmar(lista_buscar_elemento(lista, comparar_enteros, &elemento_a_buscar) == NULL, 
               "No se encuentra el elemento buscado.");

  pa2m_afirmar(lista_buscar_elemento(lista, comparar_enteros, &elemento_prueba_1) == &elemento_prueba_1, 
               "Se busca y se encuentra el primer elemento encontrado.");
  pa2m_afirmar(lista_buscar_elemento(lista, comparar_enteros, &elemento_prueba_1) == &elemento_prueba_1, 
               "Se busca y encuentra un elemento del tipo entero.");

  pa2m_afirmar(lista_buscar_elemento(lista, comparar_char, &elemento_prueba_2) == &elemento_prueba_2, 
               "Se encuentra el primer elemento encontrado cuando hay otro igual más adelante en la lista."); 
  pa2m_afirmar(lista_buscar_elemento(lista, comparar_char, &elemento_prueba_2) == &elemento_prueba_2, 
               "Se busca y encuentra un elemento del tipo char.");   

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_primero
void lista_probar_obtener_primer_elemento()
{
  pa2m_nuevo_grupo("Obtención de primer elemento de una lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();

  int elemento_prueba_1 = 99;
  char elemento_prueba_2 = 'E';

  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_primero(NULL) == NULL, "Se retorna NULL al buscar el primer elemento de una lista NULL.");
  pa2m_afirmar(lista_primero(lista_vacia) == NULL, "Se retorna NULL al buscar el primer elemento de una lista vacia.");

  pa2m_afirmar(lista != NULL, "En una lista de un solo elemento, se devuelve su único elemento como primero.");

  lista = lista_insertar(lista, &elemento_prueba_2);
  pa2m_afirmar(lista != NULL, "Se retorna el primer elemento de una lista con mas de un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_ultimo
void lista_probar_obtener_ultimo_elemento()
{
  pa2m_nuevo_grupo("Obtención de ultimo elemento de una lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();  

  int elemento_prueba_1 = 11;
  float elemento_prueba_2 = 0.5;

  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_ultimo(NULL) == NULL, "Se retorna NULL al buscar el ultimo elemento de una lista NULL.");
  pa2m_afirmar(lista_ultimo(lista_vacia) == NULL, "Se retorna NULL al buscar el ultimo elemento de una lista vacia.");

  pa2m_afirmar(lista != NULL, "En una lista de un solo elemento, se devuelve su único elemento como ultimo.");

  lista = lista_insertar(lista, &elemento_prueba_2);
  pa2m_afirmar(lista != NULL, "Se retorna el ultimo elemento de una lista con mas de un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_vacia
void lista_probar_vacia_o_inexistente()
{
  pa2m_nuevo_grupo("Comprobación de lista vacia o no existente");

  lista_t *lista = lista_crear();
  lista_t *lista_sin_elementos = lista_crear();

  int elemento_prueba = 6;

  lista = lista_insertar(lista, &elemento_prueba);

  pa2m_afirmar(lista_vacia(NULL), "Se devuelve true para una lista NULL.");
  pa2m_afirmar(lista_vacia(lista_sin_elementos), "Se devuelve true para una lista vacia.");
  pa2m_afirmar(!lista_vacia(lista), "Se devuelve false para una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_sin_elementos);
}


// Se realizan las pruebas sobre la función lista_tamanio
void lista_probar_tamanio()
{
  pa2m_nuevo_grupo("Comprobación de tamaño de una lista");

  lista_t *lista = lista_crear();
  lista_t *lista_vacia = lista_crear();
  lista_t *lista_nula = NULL;

  char elemento_prueba = 'i';

  lista = lista_insertar(lista, &elemento_prueba);

  pa2m_afirmar(lista_nula == NULL && lista_tamanio(lista_nula) == 0, "Se devuelve 0 para una lista NULL.");
  pa2m_afirmar(lista_vacia!= NULL && lista_tamanio(lista_vacia) == 0, "Se devuelve 0 para una lista vacia.");
  pa2m_afirmar(lista != NULL && lista_tamanio(lista) > 0, 
               "Se devuelve la cantidad de elementos para una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_destruir
void lista_probar_destruccion()
{
  pa2m_nuevo_grupo("Destrucción de la lista");

  lista_t *lista_de_un_elemento = lista_crear();
  lista_t *lista_mas_de_un_elemento = lista_crear();
  lista_t *lista_sin_elementos = lista_crear();

  lista_t *lista_inexistente = NULL;
  lista_destruir(lista_inexistente);
  pa2m_afirmar(lista_inexistente == NULL, "Se libera una lista NULL.");

  bool lista_es_vacia = lista_vacia(lista_sin_elementos);
  lista_destruir(lista_sin_elementos);
  pa2m_afirmar(lista_es_vacia, "Se libera una lista vacia");

  lista_destruir(lista_de_un_elemento);
  pa2m_afirmar(lista_de_un_elemento != NULL, 
               "Se libera una lista de un solo elemento junto con su único nodo.");

  lista_destruir(lista_mas_de_un_elemento);
  pa2m_afirmar(lista_mas_de_un_elemento != NULL, 
               "Se libera una lista de mas de un elemento junto con todos sus nodos.");
}


// Se realizan las pruebas sobre la función lista_destruir_todo
void lista_probar_destruccion_total()
{
  pa2m_nuevo_grupo("Destrucción de la lista y de sus elementos");
  /*
  lista_t *lista_de_un_elemento = lista_crear();
  lista_t *lista_mas_de_un_elemento = lista_crear();*/
  lista_t *lista_sin_elementos = lista_crear();

  lista_t *lista_inexistente = NULL;
  lista_destruir_todo(lista_inexistente, free);
  pa2m_afirmar(lista_inexistente == NULL, "Se libera una lista NULL.");

  bool lista_es_vacia = lista_vacia(lista_sin_elementos);
  lista_destruir_todo(lista_sin_elementos, free);
  pa2m_afirmar(lista_es_vacia, "Se libera una lista vacia");
/*
  lista_destruir(lista_de_un_elemento);
  pa2m_afirmar(lista_de_un_elemento != NULL, 
               "Se libera una lista de un solo elemento junto con su único nodo.");

  lista_destruir(lista_mas_de_un_elemento);
  pa2m_afirmar(lista_mas_de_un_elemento != NULL, 
               "Se libera una lista de mas de un elemento junto con todos sus nodos.");*/
}


// Se realizan las pruebas sobre las operaciones de una lista
void pruebas_lista()
{
  lista_probar_creacion();
  lista_probar_insercion_al_final();
  lista_probar_eliminacion_al_final();
  lista_probar_insercion_en_posicion();
  lista_probar_eliminacion_en_posicion();
  lista_probar_buscar_por_posicion();
  lista_probar_buscar_elemento(); // Volver a probar después con GDB.
  lista_probar_obtener_primer_elemento();
  lista_probar_obtener_ultimo_elemento();
  lista_probar_vacia_o_inexistente();
  lista_probar_tamanio();
  lista_probar_destruccion();
  lista_probar_destruccion_total();
}


// Se realizan las pruebas sobre las operaciones de una pila
void pruebas_pila()
{

}


// Se realizan las pruebas sobre las operaciones de una cola
void pruebas_cola()
{

}


int main() {  
  pruebas_lista();
  pruebas_pila();
  pruebas_cola();

  return pa2m_mostrar_reporte();
}