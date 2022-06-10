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

	hash_probar_cantidad();
/*
	hash_probar_destruir();
	hash_probar_destruir_todo();
*/
	return pa2m_mostrar_reporte();
}
