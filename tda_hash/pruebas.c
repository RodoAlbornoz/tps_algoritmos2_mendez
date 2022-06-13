#include "src/hash.h"
#include "pa2m.h"
#include "src/lista.h"
#include <stdlib.h>

typedef struct par {
	char *clave;
	void *valor;
} par_t;

struct hash {
	lista_t **tabla;
	size_t capacidad;
	size_t almacenados;
};


void con_capacidad_menor_a_3_se_crea_el_hash_con_capacidad_3()
{
	struct hash *hash = hash_crear(1);

	pa2m_afirmar(hash->capacidad == 3, 
	"Se crea un hash con capacidad 3 al crearlo con capacidad menor a 3.");

	hash_destruir(hash);
}


void con_capacidad_mayor_o_igual_a_3_se_crea_el_hash_con_esa_capacidad()
{
	size_t capacidad = 7;
	struct hash *hash = hash_crear(capacidad);

	pa2m_afirmar(hash->capacidad == capacidad, 
	"Se crea un hash con la capacidad indicada al ser esta 3 o mayor.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_su_cantidad_empieza_en_0()
{
	struct hash *hash = hash_crear(4);

	pa2m_afirmar(hash_cantidad(hash) == 0, 
	"La cantidad de elementos almacenados del hash empieza en 0.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_crear
 */
void hash_probar_creacion()
{
	pa2m_nuevo_grupo("Pruebas de creacion de un hash");

	con_capacidad_menor_a_3_se_crea_el_hash_con_capacidad_3();
	con_capacidad_mayor_o_igual_a_3_se_crea_el_hash_con_esa_capacidad();
	dado_un_hash_no_null_su_cantidad_empieza_en_0();
}


void hash_probar_insercion()
{
	int elemento_1 = 9;
	int elemento_2 = 7;
	int elemento_3 = 2;
	int elemento_4 = 6;

	struct hash *hash = hash_crear(4);
	hash = hash_insertar(hash, "H", &elemento_1, NULL);
	hash = hash_insertar(hash, "M", &elemento_2, NULL);
	hash = hash_insertar(hash, "Z", &elemento_3, NULL);
	hash = hash_insertar(hash, "A", &elemento_4, NULL);

	hash_destruir(hash);
}


void dado_un_hash_null_no_se_quita_elementos()
{
	pa2m_afirmar(hash_quitar(NULL, "Miedo") == NULL,
	"En un hash NULL no hay elemento para quitar.");
}

/*
void dado_un_hash_no_null_no_se_quita_un_elemento_inexistente()
{
	struct hash *hash = hash_crear(11);

	pa2m_afirmar(hash_quitar(hash, "Miedo") == NULL,
	"En un hash no NULL no existe el elemento a quitar.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_se_quita_un_elemento_existente()
{
	struct hash *hash = hash_crear(6);

	pa2m_afirmar(hash_quitar(hash, "Miedo") != NULL,
	"En un hash no NULL se quita el elemento indicado.");

	hash_destruir(hash);
}
*/

void hash_probar_quitar()
{
	pa2m_nuevo_grupo("Pruebas de quitado de elementos en un hash");

	dado_un_hash_null_no_se_quita_elementos();
	// ARREGLAR INSERCION
	/*
	dado_un_hash_no_null_no_se_quita_un_elemento_inexistente();
	dado_un_hash_no_null_se_quita_un_elemento_existente();*/
}


void dado_un_hash_null_se_devuelve_elemento_null()
{
	pa2m_afirmar(hash_obtener(NULL, "Aloha") == NULL, 
	"No hay elemento que obtener en un hash NULL.");
}
	

void dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null()
{
	struct hash *hash = hash_crear(2);

	// pa2m_afirmar(hash_obtener(hash, CLAVE NO EXISTENTE) == NULL, 
	// "No se encuentra el elemento en un hash no NULL y se retorna NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve()
{
	struct hash *hash = hash_crear(2);

	// pa2m_afirmar(hash_obtener(hash, CLAVE EXISTENTE) != NULL, 
	// "Se encuentra el elemento en un hash no NULL y se lo retorna.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_obtener
 */
void hash_probar_obtener()
{
	pa2m_nuevo_grupo("Pruebas de obtencion de elemento en un hash");

	dado_un_hash_null_se_devuelve_elemento_null();
	dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null(); // ARREGLAR INSERCION
	dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve(); // ARREGLAR INSERCION
}


void dado_un_hash_null_no_se_encuentra_el_elemento()
{
	pa2m_afirmar(!hash_contiene(NULL, "Hola"), 
	"No existe el elemento con la clave dada en un hash NULL.");
}


void dado_un_hash_no_null_se_encuentra_el_elemento()
{
	struct hash *hash = hash_crear(9);
	// hash = hash_insertar();

	// pa2m_afirmar(hash_contiene(hash, CLAVE NO EXISTENTE),
	// "Existe el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_no_se_encuentra_el_elemento()
{
	struct hash *hash = hash_crear(5);
	// hash = hash_insertar();
	
	// pa2m_afirmar(!hash_contiene(hash, CLAVE EXISTENTE),
	// "No existe el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_contiene
 */	
void hash_probar_contiene()
{
	pa2m_nuevo_grupo("Pruebas de existencia de elemento en un hash");

	dado_un_hash_null_no_se_encuentra_el_elemento();
	dado_un_hash_no_null_se_encuentra_el_elemento(); // ARREGLAR INSERCION
	dado_un_hash_no_null_no_se_encuentra_el_elemento(); // ARREGLAR INSERCION
}


void dado_un_hash_null_se_retorna_cantidad_0()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0, 
	"Para hash NULL, se retorna cantidad 0.");
}


void dado_un_hash_no_null_se_retorna_su_cantidad_de_elementos_almacenados()
{
	struct hash *hash = hash_crear(2);
	//hash_insertar(elemento)
	//hash_insertar(elemento)

	pa2m_afirmar(hash_cantidad(hash) == 2, 
	"Para hash no NULL, se retorna su cantidad de elementos almacenados.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_cantidad
 */
void hash_probar_cantidad()
{
	pa2m_nuevo_grupo("Pruebas de elementos almacenados en un hash");

	dado_un_hash_null_se_retorna_cantidad_0();
	dado_un_hash_no_null_se_retorna_su_cantidad_de_elementos_almacenados(); // AGREGAR INSERCIONES EN ESTE
}


void dado_un_hash_null_se_libera()
{
	bool hash_destruido = false;
	hash_destruir(NULL);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, "Se libera un hash NULL.");
}


void dado_un_hash_sin_elementos_se_libera()
{
	struct hash *hash = hash_crear(7);

	bool hash_destruido = false;
	hash_destruir(hash);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, "Se libera un hash sin elementos.");
}


void dado_un_hash_con_al_menos_un_elemento_se_libera()
{
	struct hash *hash = hash_crear(4);
	int elemento_1 = 9;
	int elemento_2 = 7;
	int elemento_3 = 2;

	hash = hash_insertar(hash, "A", &elemento_1, NULL);
	hash = hash_insertar(hash, "N", &elemento_2, NULL);
	hash = hash_insertar(hash, "d", &elemento_3, NULL);

	bool hash_destruido = false;
	hash_destruir(hash);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
		     "Se libera un hash con al menos un elemento.");
}


void hash_probar_destruir()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash.");

	dado_un_hash_null_se_libera();
	dado_un_hash_sin_elementos_se_libera();
	dado_un_hash_con_al_menos_un_elemento_se_libera(); // AGREGAR INSERCIONES EN ESTE
}


void dado_un_hash_null_se_libera_con_destruir_todo()
{
	bool hash_destruido = false;
	hash_destruir_todo(NULL, NULL);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
		     "Se libera un hash NULL con destruir todo.");
}


void con_destructor_null_se_libera_un_hash()
{
	struct hash *hash = hash_crear(5);

	bool hash_destruido = false;
	hash_destruir_todo(hash, NULL);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
	"Se libera solo el hash con destructor NULL.");
}


void con_destructor_no_null_se_libera_un_hash_y_sus_elementos()
{
	struct hash *hash = hash_crear(9);/*
	int elemento_1 = 9;
	int elemento_2 = 7;
	int elemento_3 = 88;
	// hash_insertar(ELEMENTOS EN MEMORIA);
	// hash_insertar(ELEMENTOS EN MEMORIA);
	// hash_insertar(ELEMENTOS EN MEMORIA);*/

	bool hash_destruido = false;
	hash_destruir_todo(hash, free);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
	"Se libera el hash y sus elementos con destructor no NULL.");
}


void hash_probar_destruir_todo()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash y de sus elementos.");

	dado_un_hash_null_se_libera_con_destruir_todo();
	con_destructor_null_se_libera_un_hash();
	con_destructor_no_null_se_libera_un_hash_y_sus_elementos(); // AGREGAR INSERCIONES EN ESTE
}


int main()
{	
	hash_probar_creacion();/*
	hash_probar_insercion();
	hash_probar_quitar();*/
	/*hash_probar_obtener();
	hash_probar_contiene();	
	hash_probar_cantidad();*/	     // PENDIENTE INSERTAR ELEMENTOS EN HASH
	hash_probar_destruir();      // PENDIENTE INSERTAR ELEMENTOS EN HASH
//	hash_probar_destruir_todo(); // PENDIENTE INSERTAR ELEMENTOS EN HASH

	return pa2m_mostrar_reporte();
}