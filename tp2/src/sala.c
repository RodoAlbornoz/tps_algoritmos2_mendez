#include "estructuras.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interaccion.h"
#include "objeto.h"
#include "TDAs/lista.h"
#include "TDAs/hash.h"

#define MAX_LINEA 1024

struct sala {
	hash_t *objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *interacciones;
	bool escapado;
};

struct info_objeto {
	char descripcion[MAX_TEXTO];
	bool es_asible;
};

struct nombres {
	char **vector_nombres;
	size_t cantidad;
};


struct elementos_interaccion {
	const char *verbo;
	const char *objeto1;
	const char *objeto2;
	bool es_valida;
};


/*
 * Se recibe un string
 *
 * Se retorna una copia del mismo
 */
char *duplicar_string(const char *s)
{
	if (!s)
		return NULL;

	char *p = malloc(strlen(s) + 1);
	if (!p)
		return NULL;

	strcpy(p, s);
	return p;
}


/*
 * Se recibe la linea actual leida del archivo, el archivo con los objetos
 * y un puntero a hash que almacena la información de los objetos de la sala
 *
 * Se guarda cada objeto leido del archivo dentro del hash
 */
void guardar_objeto(char linea[MAX_LINEA], FILE *archivo_objetos, 
		    hash_t *hash_objetos)
{
	struct objeto *objeto = objeto_crear_desde_string(linea);
	if (objeto == NULL) {
		hash_destruir(hash_objetos);
		fclose(archivo_objetos);
		return;
	}

	struct info_objeto *info_objeto = malloc(sizeof(struct info_objeto));
	if (info_objeto == NULL) {
		hash_destruir(hash_objetos);
		fclose(archivo_objetos);
		return;
	}

	strcpy(info_objeto->descripcion, objeto->descripcion);
	info_objeto->es_asible = objeto->es_asible;

	char *copia_nombre = duplicar_string(objeto->nombre);
	hash_objetos = hash_insertar(hash_objetos, copia_nombre, info_objeto, 
				     NULL);
	free(info_objeto);
	free(copia_nombre);
	free(objeto);
}


/*
 * Se recibe la ruta al archivo de objetos y un puntero a hash que almacena la
 * información de los objetos de la sala
 * 
 * Se lee el archivo de objetos, se guarda su información en el hash y se
 * retorna el hash con la información de los objetos de la sala
 */
hash_t *leer_objetos(const char *objetos, hash_t *hash_objetos)
{
	FILE *archivo_objetos = fopen(objetos, "r");
	if(!archivo_objetos) {
		hash_destruir(hash_objetos);
		return NULL;
	}

	char linea[MAX_LINEA];
	while (fgets(linea, MAX_LINEA, archivo_objetos))
		guardar_objeto(linea, archivo_objetos, hash_objetos);

	fclose(archivo_objetos);
	return hash_objetos;
}


/*
 * Se recibe la linea actual leida del archivo, el archivo con las 
 * interacciones y un puntero a listaque almacena la información de las 
 * interacciones de la sala
 *
 * Se guarda cada interaccion leida del archivo dentro de la lista
 */
void guardar_interaccion(char linea[MAX_LINEA], FILE *archivo_interacciones,
		    	 lista_t *lista_interacciones)
{
	struct interaccion *interaccion = 
					interaccion_crear_desde_string(linea);

	if (interaccion == NULL) {
		lista_destruir(lista_interacciones);
		fclose(archivo_interacciones);
		return;
	}

	lista_interacciones = lista_insertar(lista_interacciones, interaccion);
}


/*
 * Se recibe la ruta al archivo de interacciones y un puntero a lista que 
 * almacena la información de las interacciones de la sala
 * 
 * Se lee el archivo de interacciones, se guarda su información en la lista y
 * se retorna la lista con la información de las interacciones de la sala
 */
lista_t *leer_interacciones(const char *interacciones, 
			    lista_t *lista_interacciones)
{
	FILE *archivo_interacciones = fopen(interacciones, "r");
	if(!archivo_interacciones) {
		lista_destruir(lista_interacciones);
		return NULL;
	}

	char linea[MAX_LINEA];
	while (fgets(linea, MAX_LINEA, archivo_interacciones))
		guardar_interaccion(linea, archivo_interacciones, 
				    lista_interacciones);

	fclose(archivo_interacciones);
	return lista_interacciones;
}


/*
 * Se reserva memoria para la sala y se inicializan sus campos (Creando las
 * estructuras correspondientes para almacenar objetos e interacciones), 
 * retornando la sala
 */
sala_t *inicializar_sala()
{
	sala_t *sala = malloc(sizeof(struct sala));
	if (sala == NULL)
		return NULL;

	sala->escapado = false;
	sala->objetos = hash_crear(5);
	sala->objetos_conocidos = hash_crear(5);
	sala->objetos_poseidos = hash_crear(5);
	sala->interacciones = lista_crear();

	if (sala->objetos == NULL || sala->interacciones == NULL || 
	    sala->objetos_conocidos == NULL ||
	    sala->objetos_poseidos == NULL) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}


sala_t *sala_crear_desde_archivos(const char *objetos, 
				  const char *interacciones)
{
	if (objetos == NULL || interacciones == NULL)
		return NULL;

	sala_t *sala = inicializar_sala();
	if (sala == NULL)
		return NULL;

	sala->objetos = leer_objetos(objetos, sala->objetos);
	sala->interacciones = leer_interacciones(interacciones, 
						sala->interacciones);

	size_t cantidad_objetos = hash_cantidad(sala->objetos);
	size_t cantidad_interacciones = lista_tamanio(sala->interacciones);

	if (sala->objetos == NULL || sala->interacciones == NULL ||
	    cantidad_objetos == 0 || cantidad_interacciones == 0) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}


/*
 * Se recibe el nombre del objeto, su informacion (Descripción, asible)
 * y la estructura que contiene el vector de nombres junto a su cantidad
 * 
 * Se guarda el nombre del objeto dentro del vector de nombres
 */
bool guardar_nombre(const char *nombre, void *info_objeto, 
		    void *estructura_nombres)
{
	struct nombres *nombres = estructura_nombres;
	char *nombre_objeto = (char *) nombre;

	nombres->vector_nombres[nombres->cantidad] = nombre_objeto;
	(nombres->cantidad)++;

	return true;
}


/*
 * Se recibe un puntero a sala y el puntero al vector de los nombres de
 * los objetos dentro de la sala
 *
 * Se llena el vector con los nombres de todos los objetos de la sala
 */
void llenar_vector_nombres(sala_t *sala, char **vector_nombres)
{
	struct nombres *nombres = malloc(sizeof(struct nombres));
	if (nombres == NULL) {
		sala_destruir(sala);
		return;
	}
	nombres->cantidad = 0;
	nombres->vector_nombres = vector_nombres;

	hash_con_cada_clave(sala->objetos, guardar_nombre, nombres);
	free(nombres);
}


/*
 * Se recine un puntero a sala y un puntero a la cantidad de objetos de
 * cierto tipo (Totales, conocidos, poseidos)
 * 
 * Se devuelve un vector dinámico que contiene los nombres de los objetos
 * de la sala, según sean los objetos totales de la sala, los conocidos o
 * los poseidos
 */
char **obtener_nombres_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	int cantidad_nombres = (int) hash_cantidad(sala->objetos);
	char **vector_nombres = malloc((unsigned int) cantidad_nombres * 
					sizeof(char *));
	if (vector_nombres == NULL) {
		sala_destruir(sala);
		if (cantidad != NULL)
			*cantidad = -1; 
		return NULL;
	}

	llenar_vector_nombres(sala, vector_nombres);	

	if (cantidad != NULL)
		*cantidad = cantidad_nombres;

	return vector_nombres;
}


char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	return obtener_nombres_objetos(sala, cantidad);
}


char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	return obtener_nombres_objetos(sala, cantidad);
}


char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	return obtener_nombres_objetos(sala, cantidad);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (sala == NULL || nombre_objeto == NULL)
		return false;

	struct info_objeto *info_objeto = hash_obtener(sala->objetos_conocidos, 
						       nombre_objeto);

	if (info_objeto == NULL)
		return false;

	if (!info_objeto->es_asible)
		return false;

	char *nombre_duplicado = duplicar_string(nombre_objeto);
	sala->objetos_poseidos = hash_insertar(sala->objetos_poseidos, 
				 nombre_duplicado, info_objeto, NULL);

	return true;
}


char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (sala == NULL || nombre_objeto == NULL)	
		return NULL;

	struct info_objeto *info_objeto = hash_obtener(sala->objetos_conocidos, 
						       nombre_objeto);

	if (info_objeto == NULL) {
		info_objeto = hash_obtener(sala->objetos_poseidos, 
					   nombre_objeto);
		if (info_objeto == NULL)
			return NULL;
	}

	return info_objeto->descripcion;
}


/*
 * Ejecuta una o mas interacciones en la sala de escape. Cuando una interacción
 * tenga un mensaje para mostrar por pantalla, se invocará la función
 * mostrar_mensaje (si no es NULL) con el mensaje a mostrar, el tipo de acción que representa el
 * mensaje y un puntero auxiliar del usuario.
 *
 * Devuelve la cantidad de interacciones que pudo ejecutar o 0 en caso de error.
 *
 */
int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (sala == NULL || mostrar_mensaje == NULL)
		return 0;

	return 0;
}


/*
 *
 *
 */
bool verificar_interaccion(void *interaccion_actual, 
			   void *elementos_interaccion)
{
	struct interaccion *interaccion = interaccion_actual;
	struct elementos_interaccion *interaccion_a_verificar = 
						elementos_interaccion;

	if (strcmp(interaccion->objeto, interaccion_a_verificar->objeto1) == 0 &&
	    (strcmp(interaccion->objeto_parametro, interaccion_a_verificar->objeto2) == 0) &&
	    (strcmp(interaccion->verbo, interaccion_a_verificar->verbo) == 0)) {
		interaccion_a_verificar->es_valida = true;
		return false;
	    }

	return true;
}


bool sala_es_interaccion_valida(sala_t *sala, const char *verbo, 
				const char *objeto1, const char *objeto2)
{
	if (sala == NULL || verbo == NULL || objeto1 == NULL || 
	    objeto2 == NULL)
		return false;

	bool interaccion_valida = false;

	struct elementos_interaccion *elementos_interaccion = 
				malloc(sizeof(struct elementos_interaccion));
	if (elementos_interaccion == NULL)
		return false;
	elementos_interaccion->objeto1 = objeto1;
	elementos_interaccion->objeto2 = objeto2;
	elementos_interaccion->verbo = verbo;
	elementos_interaccion->es_valida = false;

	lista_con_cada_elemento(sala->interacciones, verificar_interaccion, 
				elementos_interaccion);
	
	if (elementos_interaccion->es_valida)
		interaccion_valida = true;

	free(elementos_interaccion);

	return interaccion_valida;
}


bool sala_escape_exitoso(sala_t *sala)
{
	if (sala == NULL)
		return false;

	return sala->escapado;
}


/*
 * Se recibe un puntero al elemento que contiene la información de una
 * interaccion en memoria
 * 
 * Se libera la memoria del puntero a la información de la interacción
 */
void destruir_interaccion(void *interaccion_actual)
{
	struct interaccion *interaccion = interaccion_actual;
	free(interaccion);
}


void sala_destruir(sala_t *sala)
{
	if (sala == NULL)
		return;

	hash_destruir(sala->objetos);
	hash_destruir(sala->objetos_conocidos);
	hash_destruir(sala->objetos_poseidos);
	lista_destruir_todo(sala->interacciones, destruir_interaccion);

	free(sala);
}