#include "src/hash.h"
#include "pa2m.h"
#include "src/lista.h"

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
	
/*
void dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null()
{
	struct hash *hash = hash_crear(2);

	pa2m_afirmar(hash_obtener(hash, CLAVE NO EXISTENTE) == NULL, 
	"No se encuentra el elemento en un hash no NULL y se retorna NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve()
{
	struct hash *hash = hash_crear(2);

	pa2m_afirmar(hash_obtener(hash, CLAVE EXISTENTE) != NULL, 
	"Se encuentra el elemento en un hash no NULL y se lo retorna.");

	hash_destruir(hash);
}
*/

/*
 * Se realizan las pruebas sobre la funcion hash_obtener
 */
void hash_probar_obtener()
{
	pa2m_nuevo_grupo("Pruebas de obtencion de elemento en un hash");

	dado_un_hash_null_se_devuelve_elemento_null();
	// ARREGLAR INSERCION
	/*
	dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null();
	dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve();*/
}


void dado_un_hash_null_no_se_encuentra_el_elemento()
{
	pa2m_afirmar(!hash_contiene(NULL, "Hola"), 
	"No hay elemento para buscar en un hash NULL.");
}

/*
void dado_un_hash_no_null_se_encuentra_el_elemento()
{
	struct hash *hash = hash_crear(9);
	hash = hash_insertar();

	pa2m_afirmar(!hash_contiene(hash, CLAVE NO EXISTENTE),
	"No se encuentra el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_no_se_encuentra_el_elemento()
{
	struct hash *hash = hash_crear(5);
	hash = hash_insertar();
	
	pa2m_afirmar(hash_contiene(hash, CLAVE EXISTENTE),
	"Se encuentra el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}
*/

/*
 * Se realizan las pruebas sobre la funcion hash_contiene
 */	
void hash_probar_contiene()
{
	pa2m_nuevo_grupo("Pruebas de existencia de elemento en un hash");

	dado_un_hash_null_no_se_encuentra_el_elemento();
	// ARREGLAR INSERCION
	/*
	dado_un_hash_no_null_se_encuentra_el_elemento();
	dado_un_hash_no_null_no_se_encuentra_el_elemento();*/
}


void dado_un_hash_null_se_retorna_cantidad_0()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0, 
	"Para hash NULL, se retorna cantidad 0.");
}


void dado_un_hash_no_null_se_retorna_su_cantidad_de_elementos_almacenados()
{
	struct hash *hash = hash_crear(2);
	pa2m_afirmar(hash_cantidad(hash) == 0, 
	"Para hash no NULL, se retorna la cantidad de elementos almacenados.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_cantidad
 */
void hash_probar_cantidad()
{
	pa2m_nuevo_grupo("Pruebas de elementos almacenados en un hash");

	dado_un_hash_null_se_retorna_cantidad_0();
	// AGREGAR INSERCIONES EN ESTE
	dado_un_hash_no_null_se_retorna_su_cantidad_de_elementos_almacenados();
}

/*
void dado_un_hash_null_se_libera()
{
	pa2m_afirmar(true, "Se libera un hash NULL.");
}


void dado_un_hash_no_null_se_libera()
{
	pa2m_afirmar(true, "Se libera un hash no NULL.");
}


void hash_probar_destruir()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash.");

	dado_un_hash_null_se_libera();
	dado_un_hash_no_null_se_libera();
}


void hash_probar_destruir_todo()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash y de sus elementos.");
}
*/

int main()
{
	hash_probar_creacion();
//	hash_probar_insercion();
	hash_probar_quitar();
	hash_probar_obtener();
	hash_probar_contiene();
	hash_probar_cantidad(); /*
	hash_probar_destruir();
	hash_probar_destruir_todo();*/
	return pa2m_mostrar_reporte();
}
