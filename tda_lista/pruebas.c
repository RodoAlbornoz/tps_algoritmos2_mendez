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
  lista = lista_insertar(lista, &elemento_prueba_2);
  pa2m_afirmar(lista != NULL && lista->cantidad == cantidad_auxiliar + 1, 
               "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");

  lista = lista_insertar(lista, NULL);
  pa2m_afirmar(lista != NULL, "Se inserta un elemento NULL a la lista.");

  lista_destruir(lista);
}


// Se realizan las pruebas sobre la función lista_quitar
void lista_probar_eliminacion_al_final()
{
  pa2m_nuevo_grupo("Eliminación de elementos al final de una lista");

  lista_t *lista = lista_crear();

  int elemento_prueba_1 = 11;
  char elemento_prueba_2 = 'a';

  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_quitar(NULL) == NULL, "No se puede eliminar un elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *elemento_eliminado = lista_quitar(lista_vacia);
  pa2m_afirmar(elemento_eliminado == NULL, "No se puede eliminar un elemento de una lista vacia.");

  size_t cantidad_auxiliar = lista->cantidad;
  elemento_eliminado = lista_quitar(lista);
  pa2m_afirmar(elemento_eliminado != NULL, "Se elimina un elemento no NULL de la lista.");
  pa2m_afirmar(elemento_eliminado != NULL, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(elemento_eliminado != NULL && lista->cantidad == cantidad_auxiliar - 1, 
               "La cantidad de elementos de la lista se reduce en 1.");
               
  elemento_eliminado = lista_quitar(lista);
  pa2m_afirmar(elemento_eliminado == NULL, "Se elimina un elemento NULL de la lista.");

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

  pa2m_afirmar(lista_insertar_en_posicion(NULL, &elemento_prueba_1, 5) == NULL, "No se insertan elementos en una lista NULL.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_3, 0);
  pa2m_afirmar(lista != NULL, "Se retorna la lista al insertar un elemento en la misma.");
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento en una lista vacia.");
  pa2m_afirmar(lista != NULL && lista->cantidad == 1, "La cantidad de elementos de la lista aumenta en 1.");

  size_t cantidad_auxiliar = lista->cantidad;
  lista = lista_insertar_en_posicion(lista, NULL, 1);
  pa2m_afirmar(lista != NULL && lista->cantidad == cantidad_auxiliar + 1, "Se inserta un elemento NULL a la lista.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_2, 0);
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento al principio de una lista con al menos un elemento.");
  
  lista = lista_insertar_en_posicion(lista, &elemento_prueba_1, 1);
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento en medio de una lista con al menos un elemento.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_3, 4);
  pa2m_afirmar(lista != NULL, "Se inserta exitosamente un elemento al final de una lista con al menos un elemento.");

  lista = lista_insertar_en_posicion(lista, &elemento_prueba_2, 99);
  pa2m_afirmar(lista != NULL, "Se inserta al final un elemento que se queria insertar en una posicion no existente.");

  lista_destruir(lista);
}


// Se realizan las pruebas sobre la función lista_quitar_de_posicion
void lista_probar_eliminacion_en_posicion()
{
  pa2m_nuevo_grupo("Eliminación de elementos en cierta posicion de una lista");

  lista_t *lista = lista_crear();

  char *elemento_prueba_1 = "Hola";
  int elemento_prueba_2 = -6;
  float elemento_prueba_3 = 0.5;

  lista_insertar_en_posicion(lista, &elemento_prueba_3, 1);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 0);
  lista_insertar_en_posicion(lista, &elemento_prueba_1, 1);
  lista_insertar_en_posicion(lista, NULL, 2);
  lista_insertar_en_posicion(lista, &elemento_prueba_2, 3);

  pa2m_afirmar(lista_quitar_de_posicion(NULL, 9) == NULL, "No se puede eliminar un elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *elemento_eliminado_lista = lista_quitar_de_posicion(lista_vacia, 9);
  pa2m_afirmar(elemento_eliminado_lista == NULL, "No se permite eliminar un elemento de una lista vacia.");

  size_t cantidad_auxiliar = lista->cantidad;
  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 1);
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se elimina un elemento no NULL del medio de la lista.");
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se devuelve el elemento eliminado.");
  pa2m_afirmar(elemento_eliminado_lista != NULL && lista->cantidad == cantidad_auxiliar - 1, 
               "La cantidad de elementos se reduce en 1.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 3);
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se elimina el ultimo elemento de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 0);
  pa2m_afirmar(elemento_eliminado_lista != NULL, "Se elimina el primer elemento de la lista.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 99);
  pa2m_afirmar(elemento_eliminado_lista == NULL, "Se retorna NULL al querer eliminar un elemento en una posicion inexistente.");

  elemento_eliminado_lista = lista_quitar_de_posicion(lista, 0);
  pa2m_afirmar(elemento_eliminado_lista == NULL, "Se elimina un elemento NULL de la lista.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_elemento_en_posicion 
void lista_probar_buscar_por_posicion()
{
  pa2m_nuevo_grupo("Buscar elementos por posicion en la lista");

  lista_t *lista = lista_crear();

  char elemento_prueba_1 = 'k';
  int elemento_prueba_2 = 0;
  char elemento_prueba_3 = '!';

  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista = lista_insertar(lista, NULL);
  lista = lista_insertar(lista, &elemento_prueba_3);

  void *elemento_en_posicion = lista_elemento_en_posicion(NULL, 0);
  pa2m_afirmar(elemento_en_posicion == NULL, "No se puede buscar un elemento por su posicion en una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  elemento_en_posicion = lista_elemento_en_posicion(lista_vacia, 2);
  pa2m_afirmar(elemento_en_posicion == NULL, "Se retorna NULL al buscar un elemento en cierta posicion en una lista vacia.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 9876);
  pa2m_afirmar(elemento_en_posicion == NULL, "Se retorna NULL al buscar un elemento en una posicion inexistente de una lista.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 0);
  pa2m_afirmar(elemento_en_posicion != NULL, "Se trae el elemento en la primera posicion en una lista con al menos un elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento_en_posicion != NULL, "Se trae el elemento en la ultima posicion en una lista con al menos un elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 1);
  pa2m_afirmar(elemento_en_posicion != NULL, 
               "Se trae un elemento en alguna posicion del medio en una lista con al menos un elemento.");

  elemento_en_posicion = lista_elemento_en_posicion(lista, 2);
  pa2m_afirmar(elemento_en_posicion == NULL, "Se trae un elemento NULL de la lista.");

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

  lista_t *lista_vacia = lista_crear();
  void *elemento_encontrado = lista_buscar_elemento(lista_vacia, comparar_enteros, &elemento_prueba_2);
  pa2m_afirmar(elemento_encontrado == NULL, "No se encuentra el elemento buscado en una lista vacia.");

  elemento_encontrado = lista_buscar_elemento(lista, comparar_enteros, &elemento_a_buscar);
  pa2m_afirmar(elemento_encontrado == NULL, "No se encuentra el elemento buscado.");

  elemento_encontrado = lista_buscar_elemento(lista, comparar_enteros, &elemento_prueba_1);
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_1, "Se busca y se encuentra el primer elemento encontrado.");
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_1, "Se busca y encuentra un elemento del tipo entero.");

  elemento_encontrado = lista_buscar_elemento(lista, comparar_char, &elemento_prueba_2);
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_2, 
               "Se encuentra el primer elemento encontrado cuando hay otro igual más adelante en la lista.");
  pa2m_afirmar(elemento_encontrado == &elemento_prueba_2, "Se busca y encuentra un elemento del tipo char.");   

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_primero
void lista_probar_obtener_primer_elemento()
{
  pa2m_nuevo_grupo("Obtención de primer elemento de una lista");

  lista_t *lista = lista_crear();

  int elemento_prueba_1 = 99;
  char elemento_prueba_2 = 'E';

  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_primero(NULL) == NULL, "Se retorna NULL al buscar el primer elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *primer_elemento = lista_primero(lista_vacia);
  pa2m_afirmar(primer_elemento == NULL, "Se retorna NULL al buscar el primer elemento de una lista vacia.");

  primer_elemento = lista_primero(lista);
  pa2m_afirmar(lista != NULL, "En una lista de un solo elemento, se devuelve su único elemento como primero.");

  lista = lista_insertar(lista, &elemento_prueba_2);
  primer_elemento = lista_primero(lista);
  pa2m_afirmar(lista != NULL, "Se retorna el primer elemento de una lista con mas de un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_ultimo
void lista_probar_obtener_ultimo_elemento()
{
  pa2m_nuevo_grupo("Obtención de ultimo elemento de una lista");

  lista_t *lista = lista_crear(); 

  int elemento_prueba_1 = 11;
  float elemento_prueba_2 = 0.5;

  lista = lista_insertar(lista, &elemento_prueba_1);

  pa2m_afirmar(lista_ultimo(NULL) == NULL, "Se retorna NULL al buscar el ultimo elemento de una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  void *ultimo_elemento = lista_ultimo(lista_vacia);
  pa2m_afirmar(ultimo_elemento == NULL, "Se retorna NULL al buscar el ultimo elemento de una lista vacia.");

  ultimo_elemento = lista_ultimo(lista_vacia);
  pa2m_afirmar(lista != NULL, "En una lista de un solo elemento, se devuelve su único elemento como ultimo.");


  lista = lista_insertar(lista, &elemento_prueba_2);
  ultimo_elemento = lista_ultimo(lista_vacia);
  pa2m_afirmar(lista != NULL, "Se retorna el ultimo elemento de una lista con mas de un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_vacia
void lista_probar_vacia_o_inexistente()
{
  pa2m_nuevo_grupo("Comprobación de lista vacia o no existente");

  lista_t *lista = lista_crear();

  int elemento_prueba = 6;

  lista = lista_insertar(lista, &elemento_prueba);

  pa2m_afirmar(lista_vacia(NULL), "Se devuelve true para una lista NULL.");

  lista_t *lista_sin_elementos = lista_crear();
  bool es_vacia = lista_vacia(lista_sin_elementos);
  pa2m_afirmar(es_vacia, "Se devuelve true para una lista vacia.");

  es_vacia = lista_vacia(lista);
  pa2m_afirmar(!es_vacia, "Se devuelve false para una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_sin_elementos);
}


// Se realizan las pruebas sobre la función lista_tamanio
void lista_probar_tamanio()
{
  pa2m_nuevo_grupo("Comprobación de tamaño de una lista");

  lista_t *lista = lista_crear();

  char elemento_prueba = 'i';

  lista = lista_insertar(lista, &elemento_prueba);

  lista_t *lista_nula = NULL;
  size_t tamanio_lista = lista_tamanio(lista_nula);
  pa2m_afirmar(lista_nula == NULL && tamanio_lista == 0, "Se devuelve 0 para una lista NULL.");

  lista_t *lista_vacia = lista_crear();
  tamanio_lista = lista_tamanio(lista_vacia);
  pa2m_afirmar(lista_vacia != NULL && tamanio_lista == 0, "Se devuelve 0 para una lista vacia.");

  tamanio_lista = lista_tamanio(lista);
  pa2m_afirmar(lista != NULL && tamanio_lista > 0, 
               "Se devuelve la cantidad de elementos para una lista con al menos un elemento.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
}


// Se realizan las pruebas sobre la función lista_destruir
void lista_probar_destruccion()
{
  pa2m_nuevo_grupo("Destrucción de la lista");

  int elemento_prueba_1 = 9;
  char elemento_prueba_2 = 'z';

  lista_t *lista_inexistente = NULL;
  lista_destruir(lista_inexistente);
  pa2m_afirmar(lista_inexistente == NULL, "Se libera una lista NULL.");

  lista_t *lista_sin_elementos = lista_crear();
  bool lista_es_vacia = lista_vacia(lista_sin_elementos);
  lista_destruir(lista_sin_elementos);
  pa2m_afirmar(lista_es_vacia, "Se libera una lista vacia");

  lista_t *lista_de_un_elemento = lista_crear();
  lista_de_un_elemento = lista_insertar(lista_de_un_elemento, &elemento_prueba_1);
  lista_destruir(lista_de_un_elemento);
  pa2m_afirmar(lista_de_un_elemento != NULL, "Se libera una lista de un solo elemento junto con su único nodo.");

  lista_t *lista_mas_de_un_elemento = lista_crear();
  lista_mas_de_un_elemento = lista_insertar(lista_mas_de_un_elemento, &elemento_prueba_2);
  lista_mas_de_un_elemento = lista_insertar(lista_mas_de_un_elemento, &elemento_prueba_1);
  lista_destruir(lista_mas_de_un_elemento);
  pa2m_afirmar(lista_mas_de_un_elemento != NULL, "Se libera una lista de mas de un elemento junto con todos sus nodos.");
}


// Se recibe un archivo como un void*, lo castea a FILE* y lo cierra (Funciona como fclose)
void cerrar_archivo(void *archivo)
{
  archivo = (FILE *) archivo;
  fclose(archivo);
}


// Se realizan las pruebas sobre la función lista_destruir_todo
void lista_probar_destruccion_total()
{
  pa2m_nuevo_grupo("Destrucción de la lista y de sus elementos");
  
  int elemento_prueba_1 = 9;
  int *elemento_prueba_2 = malloc(sizeof(int));
  int *elemento_prueba_3 = malloc(sizeof(int));
  FILE *archivo_prueba_1 = fopen("prueba1.txt", "r");
  FILE *archivo_prueba_2 = fopen("prueba2.txt", "r");

  lista_t *lista_sin_elementos = lista_crear();

  lista_t *lista_inexistente = NULL;
  lista_destruir_todo(lista_inexistente, free);
  pa2m_afirmar(lista_inexistente == NULL, "Se libera una lista NULL.");

  bool lista_es_vacia = lista_vacia(lista_sin_elementos);
  lista_destruir_todo(lista_sin_elementos, free);
  pa2m_afirmar(lista_es_vacia, "Se libera una lista vacia");

  lista_t *lista_de_un_elemento = lista_crear();
  lista_de_un_elemento = lista_insertar(lista_de_un_elemento, &elemento_prueba_1);
  lista_destruir_todo(lista_de_un_elemento, NULL);

  pa2m_afirmar(lista_de_un_elemento != NULL, 
               "Se libera una lista de un solo elemento junto con su único nodo y se destruye su elemento.");
  pa2m_afirmar(lista_de_un_elemento != NULL, 
               "La función destructora enviada es NULL, asi que solo se libera memoria de la lista.");

  lista_t *lista_mas_de_un_elemento = lista_crear();
  lista_mas_de_un_elemento = lista_insertar(lista_mas_de_un_elemento, elemento_prueba_2);
  lista_mas_de_un_elemento = lista_insertar(lista_mas_de_un_elemento, elemento_prueba_3);
  lista_destruir_todo(lista_mas_de_un_elemento, free);

  pa2m_afirmar(lista_mas_de_un_elemento != NULL, 
               "Se libera una lista de mas de un elemento junto con todos sus nodos y se destruyen sus elementos.");
  pa2m_afirmar(lista_mas_de_un_elemento != NULL && elemento_prueba_2 != NULL && elemento_prueba_3 != NULL, 
               "Se libera la memoria de los elementos de la lista al enviar free como funcion destructora.");

  lista_t *lista_de_archivos = lista_crear();
  lista_de_archivos = lista_insertar(lista_de_archivos, archivo_prueba_1);
  lista_de_archivos = lista_insertar(lista_de_archivos, archivo_prueba_2);
  lista_destruir_todo(lista_de_archivos, cerrar_archivo);

  pa2m_afirmar(lista_de_archivos != NULL && archivo_prueba_1 != NULL && archivo_prueba_2 != NULL, 
               "Se cierran los archivos que son elementos de la lista al enviar cerrar_archivo (fclose) como funcion destructora.");
}


// Se realizan las pruebas sobre la función lista_iterador_crear
void lista_probar_creacion_iterador()
{
  pa2m_nuevo_grupo("Creación de un iterador para la lista");

  int elemento_prueba_1 = 7;
  char elemento_prueba_2 = 'J';

  lista_iterador_t *iterador_nulo = lista_iterador_crear(NULL);
  pa2m_afirmar(iterador_nulo == NULL, "No se crea el iterador si la lista enviada es NULL.");

  lista_t *lista_vacia = lista_crear();
  lista_iterador_t *iterador1 = lista_iterador_crear(lista_vacia);
  pa2m_afirmar(iterador1 != NULL, "Se crea el iterador exitosamente a partir de una lista no NULL.");
  pa2m_afirmar(iterador1 != NULL && iterador1->lista == lista_vacia, 
               "La lista a la que apunta el iterador es igual a la lista enviada a la función.");
  pa2m_afirmar(iterador1 != NULL && iterador1->corriente == NULL, 
               "El iterador apunta inicialmente al primer nodo de una lista vacia (O sea a NULL).");

  lista_t *lista = lista_crear();
  lista = lista_insertar(lista, &elemento_prueba_1);
  lista = lista_insertar(lista, &elemento_prueba_2);
  lista_iterador_t *iterador2 = lista_iterador_crear(lista);
  pa2m_afirmar(iterador2 != NULL && iterador2->corriente == lista->nodo_inicio, 
               "El iterador apunta inicialmente al primer nodo de una lista no vacia.");

  lista_destruir(lista);
  lista_destruir(lista_vacia);
  lista_iterador_destruir(iterador1);
  lista_iterador_destruir(iterador2);
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
  lista_probar_creacion_iterador();
}










// Se realizan las pruebas sobre la funcion pila_crear 
/* void pila_probar_creacion()
{
  pa2m_nuevo_grupo("Creación de una pila");

  lista_t *pila = pila_crear();
  pa2m_afirmar(pila != NULL, "Se crea la pila exitosamente.");
  pa2m_afirmar(pila != NULL && pila->nodo_inicio == NULL, "El tope de la pila está inicializado en NULL.");
  pa2m_afirmar(pila != NULL && pila->cantidad == 0, "La cantidad de elementos de la pila se inicializa en 0.");

  pila_destruir(pila);
}


// Se realizan las pruebas sobre la funcion pila_apilar
void pila_probar_apilar()
{
  pa2m_nuevo_grupo("Apilar un elemento en una pila");

  lista_t *pila = pila_crear();

  int elemento_prueba_1 = 5;
  char elemento_prueba_2 = 'l';

  pa2m_afirmar(pila_apilar(NULL, &elemento_prueba_1) == NULL, "No se apila sobre una pila NULL.");

  pila = pila_apilar(pila, &elemento_prueba_1);
  pa2m_afirmar(pila != NULL, "Se retorna la pila al apilar un elemento sobre ella.");
  pa2m_afirmar(pila != NULL, "Se apila exitosamente sobre una pila vacia.");
  pa2m_afirmar(pila!= NULL && pila->cantidad == 1, "La cantidad de elementos de la pila aumenta en 1.");

  size_t cantidad_auxiliar = pila->cantidad;
  pila  = pila_apilar(pila, &elemento_prueba_2);
  pa2m_afirmar(pila!= NULL && pila->cantidad == cantidad_auxiliar + 1, 
               "Se apila exitosamente sobre una pila con al menos un elemento.");

  pila = pila_apilar(pila, NULL);
  pa2m_afirmar(pila != NULL, "Se apila un elemento NULL sobre la pila.");

  pila_destruir(pila);
}


// Se realizan las pruebas sobre la funcion pila_desapilar
void pila_probar_desapilar()
{

}


// Se realizan las pruebas sobre la funcion pila_tope
void pila_probar_tope()
{

}


// Se realizan las pruebas sobre la funcion pila_tamanio
void pila_probar_tamanio()
{

}



// Se realizan las pruebas sobre la funcion pila_vacia
void pila_probar_vacia()
{

}


// Se realizan las pruebas sobre la funcion pila_destruir
void pila_probar_destruir()
{

}
*/

// Se realizan las pruebas sobre las operaciones de una pila 
/*void pruebas_pila()
{
  pila_probar_creacion();
  pila_probar_apilar();
  pila_probar_desapilar();
  pila_probar_tope();
  pila_probar_tamanio();
  pila_probar_vacia();
  pila_probar_destruir();
}*/


// Se realizan las pruebas sobre las operaciones de una cola
/*void pruebas_cola()
{
  cola_probar_creacion();
  cola_probar_encolar();
  cola_probar_desencolar();
  cola_probar_frente();
  cola_probar_tamanio();
  cola_probar_vacia();
  cola_probar_destruir();
}*/


int main() {  
  pruebas_lista();
//  pruebas_pila();
//  pruebas_cola();

  return pa2m_mostrar_reporte();
}