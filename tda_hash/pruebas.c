#include "src/hash.h"
#include "pa2m.h"
#include "src/lista.h"
#include <stdlib.h>
#include <string.h>

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
	hash_t *hash = hash_crear(4);

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


void dado_un_hash_null_no_se_puede_insertar_elementos()
{
	int elemento = 9;
	pa2m_afirmar(hash_insertar(NULL, "Hola", &elemento, NULL) == NULL,
	"En un hash NULL no es posible insertar un elemento");
}


void dada_una_clave_null_no_se_puede_insertar_elemento()
{
	int elemento = 2;
	hash_t *hash = hash_crear(4);

	pa2m_afirmar(hash_insertar(hash, NULL, &elemento, NULL) == NULL,
	"No se puede insertar en el hash si la clave enviada es NULL.");

	hash_destruir(hash);
}


void dado_un_hash_vacio_se_inserta_en_el()
{
	hash_t *hash = hash_crear(5);
	int elemento = 5;

	size_t cantidad_almacenados = hash_cantidad(hash);
	hash = hash_insertar(hash, "Playa", &elemento, NULL);

	pa2m_afirmar(hash != NULL && hash_contiene(hash, "Playa"), 
	"Se inserta un elemento en un hash vacio.");
	pa2m_afirmar(hash_cantidad(hash) == cantidad_almacenados + 1,
	"La cantidad de elementos almacenados en el hash aumenta en 1.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_se_inserta_un_elemento_null()
{
	hash_t *hash = hash_crear(7);
	
	hash = hash_insertar(hash, "Agua", NULL, NULL);
	pa2m_afirmar(hash != NULL && hash_obtener(hash, "Agua") == NULL,
	"Se inserta un elemento NULL en el hash.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_se_inserta_un_elemento_con_clave_no_existente()
{
	hash_t *hash = hash_crear(3);
	int elemento_1 = 19;
	int elemento_2 = 21;

	void *anterior = NULL;
	bool existe_elemento = hash_contiene(hash, "Cerati");
	hash = hash_insertar(hash, "Cerati", &elemento_1, &anterior);
	hash = hash_insertar(hash, "Calamaro", &elemento_2, &anterior);
	existe_elemento = hash_contiene(hash, "Cerati");

	pa2m_afirmar(hash != NULL && existe_elemento, 
	"Se inserta un elemento en el hash con clave que no existia.");
	pa2m_afirmar(anterior == NULL, 
	"El elemento anterior es NULL porque la clave no existia.");

	hash_destruir(hash);
}

/*
void dado_un_hash_no_null_se_actualiza_elemento_con_clave_existente()
{	
	hash_t *hash = hash_crear(7);
	int elemento_1 = 19;
	int elemento_2 = 21;
	int elemento_3 = 3;

	void *anterior = NULL;
	hash = hash_insertar(hash, "Chupetin", &elemento_1, NULL);

	hash = hash_insertar(hash, "Caramelo", &elemento_1, &anterior);
	int *elemento_anterior = hash_obtener(hash, "Caramelo");
	size_t cantidad_antes_de_actualizar = hash_cantidad(hash);

	hash = hash_insertar(hash, "Gomitas", &elemento_2, NULL);
	hash = hash_insertar(hash, "Caramelo", &elemento_3, &anterior);
	size_t cantidad_despues_de_actualizar = hash_cantidad(hash);

	hash = hash_insertar(hash, "Chocolate", &elemento_3, NULL);

	int *elemento_actualizado = hash_obtener(hash, "Caramelo");
	
	pa2m_afirmar(hash != NULL && *elemento_actualizado == elemento_3, 
	"Se actualiza un elemento del hash cuya clave ya existia.");
	pa2m_afirmar(cantidad_despues_de_actualizar == 
		     cantidad_antes_de_actualizar + 1, 
	"La cantidad de elementos del hash no aumenta al actualizar un \n\
	elemento.");

	pa2m_afirmar(*elemento_anterior == anterior, 
	"El elemento anterior es no NULL porque contiene el valor anterior \n\
	correspondiente a la clave cuyo valor fue actualizado.");

	hash_destruir(hash);
}
*/

/*
 * Se realizan las pruebas sobre la funcion hash_insertar
 */
void hash_probar_insercion()
{
	pa2m_nuevo_grupo("Pruebas de insercion de elementos en un hash");

	dado_un_hash_null_no_se_puede_insertar_elementos();
	dada_una_clave_null_no_se_puede_insertar_elemento();
	dado_un_hash_vacio_se_inserta_en_el();
	dado_un_hash_no_null_se_inserta_un_elemento_null();
	dado_un_hash_no_null_se_inserta_un_elemento_con_clave_no_existente();
//	dado_un_hash_no_null_se_actualiza_elemento_con_clave_existente();
}


void dado_un_hash_null_no_se_quita_elemento()
{
	pa2m_afirmar(hash_quitar(NULL, "Miedo") == NULL,
	"En un hash NULL no hay elemento para quitar.");
}


void dada_una_clave_null_no_se_puede_quitar_elemento()
{
	hash_t *hash = hash_crear(3);
	pa2m_afirmar(hash_quitar(hash, NULL) == NULL,
	"No se puede quitar un elemento si la clave enviada es NULL.");
	hash_destruir(hash);	
}


void dado_un_hash_no_null_se_quita_elemento_null()
{
	hash_t *hash = hash_crear(6);
	int elemento_1 = 2;
	int elemento_2 = 9;
	
	hash = hash_insertar(hash, "Buenos Aires", &elemento_2, NULL);
	hash = hash_insertar(hash, "Catamarca", NULL, NULL);
	hash = hash_insertar(hash, "Tucuman", &elemento_1, NULL);

	pa2m_afirmar(hash_quitar(hash, "Catamarca") == NULL,
	"Se quita un elemento NULL del hash.");

	hash_destruir(hash);	
}


void dado_un_hash_no_null_no_se_quita_un_elemento_inexistente()
{
	hash_t *hash = hash_crear(11);
	int elemento = 7;

	hash = hash_insertar(hash, "Hamburguesa", &elemento, NULL);

	pa2m_afirmar(hash_quitar(hash, "Empanada") == NULL,
	"No existe el elemento con la clave dada.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_se_quita_un_elemento_existente()
{
	hash_t *hash = hash_crear(6);
	int elemento_1 = 17;
	int elemento_2 = 8;

	hash = hash_insertar(hash, "Half Life 2", &elemento_2, NULL);
	hash = hash_insertar(hash, "Age of Empires 2", &elemento_1, NULL);
	hash = hash_insertar(hash, "world of warcraft", &elemento_2, NULL);

	size_t cantidad_aux = hash_cantidad(hash);
	int *elemento_a_quitar = hash_quitar(hash, "Half Life 2");
	pa2m_afirmar(*elemento_a_quitar == elemento_2,
	"Existe y se quita el elemento con la clave dada.");
	pa2m_afirmar(hash_cantidad(hash) == cantidad_aux - 1, 
	"Se reduce en 1 la cantidad de elementos almacenados en el hash.");

	hash_destruir(hash);
}


void dado_un_hash_con_valor_actualizado_se_quita_el_elemento_actual()
{
	hash_t *hash = hash_crear(5);
	int elemento_1 = 99;
	int elemento_2 = 63;

	void *anterior = NULL;
	hash = hash_insertar(hash, "Hielo", &elemento_2, &anterior);
	hash = hash_insertar(hash, "Fuego", &elemento_2, NULL);
	hash = hash_insertar(hash, "Tierra", &elemento_1, NULL);
	hash = hash_insertar(hash, "Hielo", &elemento_1, &anterior);
	int *elemento_anterior = anterior;

	int *elemento_quitado = hash_quitar(hash, "Hielo");
	pa2m_afirmar(*elemento_quitado != *elemento_anterior, 
	"Dada una clave en un hash no NULL cuyo valor asociado fue \n\
	actualizado, se quita el elemento actualizado.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_quitar
 */
void hash_probar_quitar()
{
	pa2m_nuevo_grupo("Pruebas de quitado de elementos en un hash");

	dado_un_hash_null_no_se_quita_elemento();
	dada_una_clave_null_no_se_puede_quitar_elemento();
	dado_un_hash_no_null_se_quita_elemento_null();
	dado_un_hash_no_null_no_se_quita_un_elemento_inexistente();
	dado_un_hash_no_null_se_quita_un_elemento_existente();
	dado_un_hash_con_valor_actualizado_se_quita_el_elemento_actual();
}


void dado_un_hash_null_se_devuelve_elemento_null()
{
	pa2m_afirmar(hash_obtener(NULL, "Aloha") == NULL, 
	"No hay elemento que obtener en un hash NULL.");
}


void dada_una_clave_null_no_se_puede_obtener_elemento()
{
	hash_t *hash = hash_crear(5);
	pa2m_afirmar(hash_obtener(hash, NULL) == NULL,
	"No se puede obtener el elemento si la clave enviada es NULL.");
	hash_destruir(hash);
}


void dado_un_hash_no_null_se_devuelve_elemento_null()
{
	hash_t *hash = hash_crear(15);
	int elemento = 6;
	
	hash = hash_insertar(hash, "Rojo", NULL, NULL);
	hash = hash_insertar(hash, "Amarillo", &elemento, NULL);

	pa2m_afirmar(hash_obtener(hash, "Rojo") == NULL,
	"La clave enviada devuelve como resultado un elemento NULL.");

	hash_destruir(hash);
}
	

void dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null()
{
	hash_t *hash = hash_crear(7);
	int elemento_1 = 17;
	int elemento_2 = 22;
	int elemento_3 = 9;

	hash = hash_insertar(hash, "Homero", &elemento_1 , NULL);
	hash = hash_insertar(hash, "Lisa", &elemento_1, NULL);
	hash = hash_insertar(hash, "Maggie", &elemento_3, NULL);
	hash = hash_insertar(hash, "Bart", &elemento_2, NULL);

	pa2m_afirmar(hash_obtener(hash, "Marge") == NULL, 
	"No se encuentra el elemento en un hash no NULL y se retorna NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve()
{
	hash_t *hash = hash_crear(5);
	int elemento_1 = 2;
	int elemento_2 = 1;

	hash = hash_insertar(hash, "Algo I", &elemento_1 , NULL);
	hash = hash_insertar(hash, "Algo II", &elemento_2, NULL);
	hash = hash_insertar(hash, "Algo III", &elemento_2, NULL);

	int *elemento_obtenido = hash_obtener(hash, "Algo II");
	pa2m_afirmar(*elemento_obtenido == elemento_2,
	"Se encuentra el elemento en un hash no NULL y se lo retorna.");

	hash_destruir(hash);
}


void dado_un_hash_con_valor_actualizado_se_devuelve_el_elemento_actual()
{
	hash_t *hash = hash_crear(9);
	int elemento_1 = 7;
	int elemento_2 = 16;
	int elemento_3 = 24;

	void *anterior = NULL;
	hash = hash_insertar(hash, "Iron Man", &elemento_1, &anterior);
	hash = hash_insertar(hash, "Thor", &elemento_2, NULL);
	hash = hash_insertar(hash, "Iron Man", &elemento_3, &anterior);
	hash = hash_insertar(hash, "Spiderman", &elemento_1, NULL);
	int *elemento_anterior = anterior;

	int *elemento_obtenido = hash_obtener(hash, "Iron Man");
	pa2m_afirmar(*elemento_obtenido != *elemento_anterior, 
	"Dada una clave en un hash no NULL cuyo valor asociado fue \n\
	actualizado, se devuelve el elemento actualizado.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_obtener
 */
void hash_probar_obtener()
{
	pa2m_nuevo_grupo("Pruebas de obtencion de elemento en un hash");

	dado_un_hash_null_se_devuelve_elemento_null();
	dada_una_clave_null_no_se_puede_obtener_elemento();
	dado_un_hash_no_null_se_devuelve_elemento_null();
	dado_un_hash_no_null_no_existe_el_elemento_y_se_devuelve_null();
	dado_un_hash_no_null_existe_el_elemento_y_se_lo_devuelve();
	dado_un_hash_con_valor_actualizado_se_devuelve_el_elemento_actual();
}


void dado_un_hash_null_no_se_encuentra_el_elemento()
{
	pa2m_afirmar(!hash_contiene(NULL, "Hola"), 
	"No existe el elemento con la clave dada en un hash NULL.");
}


void dada_una_clave_null_no_existe_el_elemento()
{
	hash_t *hash = hash_crear(2);
	pa2m_afirmar(!hash_contiene(hash, NULL), 
	"No existe el elemento si la clave enviada es NULL.");
	hash_destruir(hash);
}


void dado_un_hash_no_null_se_encuentra_el_elemento()
{
	hash_t *hash = hash_crear(5);
	int elemento_1 = 6;
	int elemento_2 = 10;

	hash = hash_insertar(hash, "Fisica", &elemento_1, NULL);
	hash = hash_insertar(hash, "Analisis II", &elemento_2, NULL);

	pa2m_afirmar(hash_contiene(hash, "Analisis II"),
	"Existe el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}


void dado_un_hash_no_null_no_se_encuentra_el_elemento()
{
	hash_t *hash = hash_crear(8);
	int elemento_1 = 77;
	int elemento_2 = 0;
	int elemento_3 = 8;

	hash = hash_insertar(hash, "Manzana", &elemento_1, NULL);
	hash = hash_insertar(hash, "Naranja", &elemento_3, NULL);
	hash = hash_insertar(hash, "Pera", &elemento_2, NULL);
	hash = hash_insertar(hash, "Mandarina", &elemento_1, NULL);
	
	pa2m_afirmar(!hash_contiene(hash, "mandarina"),
	"No existe el elemento con la clave dada en un hash no NULL.");

	hash_destruir(hash);
}


/*
 * Se realizan las pruebas sobre la funcion hash_contiene
 */	
void hash_probar_contiene()
{
	pa2m_nuevo_grupo("Pruebas de existencia de elemento en un hash");

	dado_un_hash_null_no_se_encuentra_el_elemento();
	dada_una_clave_null_no_existe_el_elemento();
	dado_un_hash_no_null_se_encuentra_el_elemento(); 
	dado_un_hash_no_null_no_se_encuentra_el_elemento();
}


void dado_un_hash_null_se_retorna_cantidad_0()
{
	pa2m_afirmar(hash_cantidad(NULL) == 0, 
	"Para hash NULL, se retorna cantidad 0.");
}


void dado_un_hash_no_null_se_retorna_su_cantidad_de_elementos_almacenados()
{
	hash_t *hash = hash_crear(7);
	int valor_1 = 11;
	int valor_2 = 1;

	hash = hash_insertar(hash, "Pila", &valor_1, NULL);
	hash = hash_insertar(hash, "Cola", &valor_2, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 2, 
	"Para hash no NULL, se retorna su cantidad de elementos almacenados.");

	hash_destruir(hash);
}


void en_un_hash_no_null_su_cantidad_no_cambia_al_insertar_valor_duplicado()
{
	hash_t *hash = hash_crear(6);
	int elemento_1 = 3;
	int elemento_2 = 1;

	void *anterior = NULL;
	hash = hash_insertar(hash, "Argentina", &elemento_2, &anterior);
	hash = hash_insertar(hash, "Argentina", &elemento_1, &anterior);
	hash = hash_insertar(hash, "Jamaica", &elemento_2, NULL);

	pa2m_afirmar(hash_cantidad(hash) == 2,
	"La cantidad de elementos almacenados del hash no cambia al\n\
	insertar un valor con clave duplicada.");

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
	en_un_hash_no_null_su_cantidad_no_cambia_al_insertar_valor_duplicado();
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
	hash_t *hash = hash_crear(7);

	bool hash_destruido = false;
	hash_destruir(hash);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, "Se libera un hash sin elementos.");
}


void dado_un_hash_con_al_menos_un_elemento_se_libera()
{
	hash_t *hash = hash_crear(5);
	int elemento_1 = 9;
	int elemento_2 = 7;
	int elemento_3 = 2;

	hash = hash_insertar(hash, "Anana", &elemento_1, NULL);
	hash = hash_insertar(hash, "Nota", &elemento_2, NULL);
	hash = hash_insertar(hash, "helado", &elemento_3, NULL);

	bool hash_destruido = false;
	hash_destruir(hash);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
		     "Se libera un hash con al menos un elemento.");
}


void dado_un_hash_con_valor_actualizado_se_libera()
{
	hash_t *hash = hash_crear(3);
	int elemento_1 = 55;
	int elemento_2 = 9;
	int elemento_3 = 7;

	void *anterior = NULL;
	hash = hash_insertar(hash, "Python", &elemento_1, &anterior);
	hash = hash_insertar(hash, "Python", &elemento_2, &anterior);
	hash = hash_insertar(hash, "Java", &elemento_3, NULL);

	bool hash_destruido = false;
	hash_destruir(hash);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido,
	"Se libera un hash en el que se insertó un valor con clave duplicada");
}


/*
 * Se realizan las pruebas sobre la funcion hash_destruir
 */
void hash_probar_destruir()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash.");

	dado_un_hash_null_se_libera();
	dado_un_hash_sin_elementos_se_libera();
	dado_un_hash_con_al_menos_un_elemento_se_libera();
	dado_un_hash_con_valor_actualizado_se_libera();
}


void dado_un_hash_null_se_libera_con_destruir_todo()
{
	bool hash_destruido = false;
	hash_destruir_todo(NULL, free);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
		     "Se libera un hash NULL con destruir todo.");
}


void con_destructor_null_se_libera_un_hash_no_null()
{
	hash_t *hash = hash_crear(5);
	int elemento_1 = 8;
	int elemento_2 = 5;

	hash = hash_insertar(hash, "Felipe", &elemento_1, NULL);
	hash = hash_insertar(hash, "Alfonso", &elemento_1, NULL);
	hash = hash_insertar(hash, "Rodrigo", &elemento_2, NULL);
	hash = hash_insertar(hash, "Martin", &elemento_1, NULL);

	bool hash_destruido = false;
	hash_destruir_todo(hash, NULL);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
	"Se libera solo el hash con destructor NULL.");
}


void con_destructor_no_null_se_libera_un_hash_no_null_y_sus_elementos()
{
	hash_t *hash = hash_crear(9);
	int *elemento_1 = malloc(sizeof(int));
	int *elemento_2 = malloc(sizeof(int));
	int *elemento_3 = malloc(sizeof(int));

	hash_insertar(hash, "Verano", elemento_1, NULL);
	hash_insertar(hash, "Invierno", elemento_2, NULL);
	hash_insertar(hash, "Primavera", elemento_3, NULL);

	bool hash_destruido = false;
	hash_destruir_todo(hash, free);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
	"Se libera el hash y sus elementos con destructor no NULL.");
}


void dado_un_hash_con_valor_actualizado_se_libera_con_destructor_no_null()
{
	hash_t *hash = hash_crear(4);
	int *elemento_1 = malloc(sizeof(int));
	int *elemento_2 = malloc(sizeof(int));
	int *elemento_3 = malloc(sizeof(int));

	void *anterior = NULL;
	hash_insertar(hash, "Karen", elemento_1, &anterior);
	hash_insertar(hash, "Jimena", elemento_3, NULL);
	hash_insertar(hash, "Karen", elemento_2, &anterior);
	hash_insertar(hash, "Maria", elemento_1, NULL);

	bool hash_destruido = false;
	hash_destruir_todo(hash, free);
	hash_destruido = true;

	pa2m_afirmar(hash_destruido, 
	"Se libera un hash en el que se insertó un valor con clave \n\
	duplicada y sus elementos con destructor no NULL.");	
}


/*
 * Se realizan las pruebas sobre la funcion hash_destruir_todo
 */
void hash_probar_destruir_todo()
{
	pa2m_nuevo_grupo("Pruebas de destruccion de hash y de sus elementos.");

	dado_un_hash_null_se_libera_con_destruir_todo();
	con_destructor_null_se_libera_un_hash_no_null();
	con_destructor_no_null_se_libera_un_hash_no_null_y_sus_elementos();
	dado_un_hash_con_valor_actualizado_se_libera_con_destructor_no_null();
}

/*
void dado_un_hash_no_null_se_insertan_n_elementos(size_t cantidad, 
						  char *mensaje)
{	
	hash_t *hash = hash_crear(15);

	char *caracteres = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuv\n\
	wxyz1234567890!@<>{}[]()'_*#!%$&/=+*-.:;|2U98HFUHFWE!rt#$#wefERFFHWI\n\
	SH4ffr2453#!!dehUH12hZ_{2{d}[dw2}!GHFD97Yg8yfd97hsdff0923h94344##dsh\n\
	dsj2183hHFDHGF!r#ufhuh4$!sdc{d{s}df{ds]]<Zwef>dsf2138FN3J32}2{<z!h5$\n\
	dsfhu32#jsduihHUD2FBVHhfbhdi!334#[}{sd{-<_:4wfdf;:3h43434fdufdfh__u8\n\
	fh3F{EW32}FOSDFHIgdfFFDS343t6tyFDSF:DFsDS:F;SDW;|2#$#wefERFFHWI48uU8\n\
	SH4fAUfhyidHIDFSIFSD#!23_#hUH12hZ_{2{d}DSQRFsf_[]()'_*#!%$&/=+*-.:;|\n\
	182U42RFDSf32123RF@fsfs";

	size_t longitud_string = 2;
	char string_hash[longitud_string];

	int elemento = 5;
	int i = 0, j = 0, k = 0;
	bool error_en_insercion = false;
	while (i < cantidad && !error_en_insercion) {
		if (j == strlen(caracteres)) {
			k++;
			j = k;
		}

		if (k == strlen(caracteres)) {
			longitud_string++;
			j = 0;
			k = 0;
			char string_hash[longitud_string];
		}
		
		strncpy(string_hash, &caracteres[j], longitud_string);
		string_hash[longitud_string] = '\0';

		hash = hash_insertar(hash, string_hash, &elemento, NULL);


		if (hash == NULL)
			error_en_insercion = true;
		i++;
		j += 2;
	}

	pa2m_afirmar(!error_en_insercion && hash_cantidad(hash) == cantidad, 
		     mensaje);

	hash_destruir(hash);
}


void pruebas_de_volumen()
{
	pa2m_nuevo_grupo("Pruebas de volumen");

	dado_un_hash_no_null_se_insertan_n_elementos(5, 
				"Se insertan 5 elementos en el hash");
	dado_un_hash_no_null_se_insertan_n_elementos(10, 
				"Se insertan 10 elementos en el hash");
	dado_un_hash_no_null_se_insertan_n_elementos(20, 
				"Se insertan 20 elementos en el hash");
	dado_un_hash_no_null_se_insertan_n_elementos(30, 
				"Se insertan 30 elementos en el hash");
	dado_un_hash_no_null_se_insertan_n_elementos(50, 
				"Se insertan 50 elementos en el hash");
	dado_un_hash_no_null_se_insertan_n_elementos(100, 
				"Se insertan 100 elementos en el hash");
}
*/

int main()
{	
	hash_probar_creacion();
	hash_probar_insercion();
	//hash_probar_rehash();
	hash_probar_quitar();
	hash_probar_obtener();
	hash_probar_contiene();
	hash_probar_cantidad();
	hash_probar_destruir();
	hash_probar_destruir_todo();

//	pruebas_de_volumen();

	return pa2m_mostrar_reporte();
}