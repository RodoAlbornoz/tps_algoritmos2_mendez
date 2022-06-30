#include "estructuras.h"
#include "sala.h"
#include "interaccion.h"
#include "objeto.h"
#include "lista.h"
#include "hash.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINEA 1024

struct sala {
	hash_t *objetos;
	hash_t *objetos_conocidos;
	hash_t *objetos_poseidos;
	lista_t *interacciones;
	bool escapado;
};

struct nombres {
	char **vector_nombres;
	size_t cantidad;
};

struct elementos_interaccion {
	const char *verbo;
	const char *objeto1;
	const char *objeto2;
	bool existe;
};


/*
 * Se recibe la linea actual leida del archivo, el archivo con los objetos,
 * un puntero a hash que almacena la información de los objetos de la sala
 * y otro puntero a hash con la informacion de los objetos conocidos.
 *
 * Se guarda cada objeto leido del archivo dentro del hash y se retorna el
 * hash de los objetos. Tambien se hace que se conozca el primer objeto de la 
 * sala. También se hace conocido el primer objeto
 */
hash_t *guardar_objeto(char linea[MAX_LINEA], FILE *archivo_objetos, 
		       hash_t *hash_objetos, hash_t *hash_objetos_conocidos)
{
	struct objeto *objeto = objeto_crear_desde_string(linea);
	if (objeto == NULL) {
		hash_destruir_todo(hash_objetos, free);
		fclose(archivo_objetos);
		return NULL;
	}

	if (hash_cantidad(hash_objetos) == 0) {
		hash_objetos_conocidos = hash_insertar(hash_objetos_conocidos, 
						objeto->nombre, objeto, NULL);

		if (hash_objetos_conocidos == NULL) {
			hash_destruir_todo(hash_objetos_conocidos, free);
			hash_destruir_todo(hash_objetos, free);
			return NULL;
		}
	}

	hash_objetos = hash_insertar(hash_objetos, objeto->nombre, objeto,
				     NULL);
	if (hash_objetos == NULL) {
		hash_destruir_todo(hash_objetos, free);
		fclose(archivo_objetos);
		return NULL;
	}

	return hash_objetos;
}


/*
 * Se recibe la ruta al archivo de objetos, un puntero a hash que almacena la
 * información de los objetos de la sala y otro puntero a hash que almacena la
 * informacion de los objetos conocidos
 * 
 * Se lee el archivo de objetos, se guarda su información en el hash y se
 * retorna el hash con la información de los objetos de la sala.
 *
 */
hash_t *leer_objetos(const char *objetos, hash_t *hash_objetos, 
		     hash_t *hash_objetos_conocidos)
{
	FILE *archivo_objetos = fopen(objetos, "r");
	if(!archivo_objetos) {
		hash_destruir_todo(hash_objetos, free);
		return NULL;
	}

	char linea[MAX_LINEA];
	char *lectura = fgets(linea, MAX_LINEA, archivo_objetos);
	while (lectura) {
		hash_objetos = guardar_objeto(linea, archivo_objetos, 
					hash_objetos, hash_objetos_conocidos);
		if (hash_objetos == NULL || hash_objetos_conocidos == NULL)
			return NULL;

		lectura = fgets(linea, MAX_LINEA, archivo_objetos);
	}

	fclose(archivo_objetos);
	return hash_objetos;
}


/*
 * Se recibe la linea actual leida del archivo, el archivo con las 
 * interacciones y un puntero a lista que almacena la información de las
 * interacciones de la sala
 *
 * Se guarda cada interaccion leida del archivo dentro de la lista y se retorna
 * la lista con las interacciones
 */
lista_t *guardar_interaccion(char linea[MAX_LINEA], FILE *archivo_interacciones,
		    	 lista_t *lista_interacciones)
{
	struct interaccion *interaccion = interaccion_crear_desde_string(linea);
	if (interaccion == NULL) {
		lista_destruir_todo(lista_interacciones, free);
		fclose(archivo_interacciones);
		return NULL;
	}

	lista_interacciones = lista_insertar(lista_interacciones, interaccion);
	if (lista_interacciones == NULL) {
		lista_destruir_todo(lista_interacciones, free);
		fclose(archivo_interacciones);
		return NULL;
	}

	return lista_interacciones;
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
		lista_destruir_todo(lista_interacciones, free);
		return NULL;
	}

	char linea[MAX_LINEA];
	char *lectura = fgets(linea, MAX_LINEA, archivo_interacciones);
	while (lectura) {
		lista_interacciones = guardar_interaccion(linea, 
				archivo_interacciones, lista_interacciones);
		if (lista_interacciones == NULL)
			return NULL;

		lectura = fgets(linea, MAX_LINEA, archivo_interacciones);
	}

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
	sala->objetos = hash_crear(10);
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

	sala->objetos = leer_objetos(objetos, sala->objetos, 
				     sala->objetos_conocidos);
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
 * Se recibe el nombre del objeto, el objeto y la estructura que contiene el 
 * vector de nombres junto a su cantidad
 * 
 * Se guarda el nombre del objeto dentro del vector de nombres y se actualiza
 * la cantidad de nombres guardados
 */
bool guardar_nombre(const char *nombre, void *objeto, 
		    void *estructura_nombres)
{
	struct nombres *nombres = estructura_nombres;
	char *nombre_objeto = (char *) nombre;

	nombres->vector_nombres[nombres->cantidad] = nombre_objeto;
	(nombres->cantidad)++;

	return true;
}


/*
 * Se recibe un puntero a un hash de objetos (Ya sean totales, conocidos o
 * poseidos) y un puntero a la cantidad de objetos de ese tipo
 * 
 * Se devuelve un vector dinámico que contiene los nombres de los objetos
 * de la sala, según sean los objetos totales de la sala, los conocidos o
 * los poseidos
 */
char **obtener_nombres_objetos(hash_t *objetos, int *cantidad)
{
	if (objetos == NULL) {
		if (cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	size_t cantidad_nombres = hash_cantidad(objetos);
	char **vector_nombres = malloc((unsigned int) cantidad_nombres *
					sizeof(char *));
	if (vector_nombres == NULL) {
		if (cantidad != NULL)
			*cantidad = -1; 
		return NULL;
	}

	struct nombres nombres; 
	nombres.cantidad = 0;
	nombres.vector_nombres = vector_nombres;

	hash_con_cada_clave(objetos, guardar_nombre, &nombres);

	if (cantidad != NULL)
		*cantidad = (int) cantidad_nombres;

	return vector_nombres;
}


char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if (cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	return obtener_nombres_objetos(sala->objetos, cantidad);
}


char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if (cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	return obtener_nombres_objetos(sala->objetos_conocidos, cantidad);
}


char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if (cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	return obtener_nombres_objetos(sala->objetos_poseidos, cantidad);
}


bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (sala == NULL || nombre_objeto == NULL)
		return false;

	struct objeto *objeto = hash_obtener(sala->objetos_conocidos, 
					     nombre_objeto);

	if (objeto == NULL)
		return false;

	if (!objeto->es_asible)
		return false;

	sala->objetos_poseidos = hash_insertar(sala->objetos_poseidos, 
					nombre_objeto, objeto, NULL);

	return true;
}


char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (sala == NULL || nombre_objeto == NULL)	
		return NULL;

	struct objeto *objeto = hash_obtener(sala->objetos_conocidos, 
					     nombre_objeto);

	if (objeto == NULL) {
		objeto = hash_obtener(sala->objetos_poseidos, nombre_objeto);
		if (objeto == NULL)
			return NULL;
	}

	return objeto->descripcion;
}


/*
 * Se recibe un puntero a una interaccion, y strings de los objetos y el verbo
 * de otra interacción.
 *
 * Se retorna si la interacción corresponde con la de los objetos y verbo 
 * enviados
 */
bool interaccion_coincide(struct interaccion *interaccion, const char *verbo,
			  const char *objeto1, const char *objeto2)
{
	return ((strcmp(interaccion->objeto, objeto1) == 0) &&
	(strcmp(interaccion->objeto_parametro, objeto2) == 0) &&
	(strcmp(interaccion->verbo, verbo) == 0) );
}


/*
 *
 *
 */
bool objeto_es_conocido(hash_t *objetos_conocidos, char *nombre)
{
	if (strcpy(nombre, "_") == 0)
		return true;

	return hash_contiene(objetos_conocidos, nombre);
}


/*
 *
 *
 */
bool objeto_se_posee(hash_t *objetos_poseidos, const char *nombre)
{
	return hash_contiene(objetos_poseidos, nombre);
}


/*
 *
 *
 */
void descubrir_objeto(sala_t *sala, struct interaccion *interaccion)
{
	if (objeto_es_conocido(sala->objetos_conocidos, interaccion->objeto) &&
	    objeto_es_conocido(sala->objetos_conocidos, interaccion->objeto_parametro) &&
	    !objeto_es_conocido(sala->objetos_conocidos, interaccion->accion.objeto) && 
	    !objeto_se_posee(sala->objetos_poseidos, interaccion->accion.objeto)) {
		
		sala->objetos_conocidos = hash_insertar(sala->objetos_conocidos, 
		interaccion->accion.objeto, hash_obtener(sala->objetos, interaccion->accion.objeto), NULL);

		if (sala->objetos_conocidos == NULL) {
			sala_destruir(sala);
			return;
		}
	}
}


/*
 *
 *
 */
void eliminar_objeto(sala_t *sala, struct interaccion *interaccion)
{
	hash_quitar(sala->objetos, interaccion->objeto);
	hash_quitar(sala->objetos_conocidos, interaccion->objeto);
	hash_quitar(sala->objetos_poseidos, interaccion->objeto);
}


/*
 *
 *
 */
void reemplazar_objeto(sala_t *sala, struct interaccion *interaccion)
{
	if (objeto_se_posee(sala->objetos_poseidos, interaccion->objeto) &&
	    objeto_es_conocido(sala->objetos_conocidos, interaccion->objeto_parametro) &&
	    !objeto_es_conocido(sala->objetos_conocidos, interaccion->accion.objeto)) {
		
		sala->objetos_conocidos = hash_insertar(sala->objetos_conocidos, 
		interaccion->accion.objeto, hash_obtener(sala->objetos, interaccion->accion.objeto), NULL);

		if (sala->objetos_conocidos == NULL) {
			sala_destruir(sala);
			return;
		}

		hash_quitar(sala->objetos_conocidos, interaccion->objeto_parametro);
	}
}


/*
 *
 *
 */
int ejecutar_interaccion(sala_t *sala, struct interaccion *interaccion, 
			 void (*mostrar_mensaje)(const char *mensaje,
						 enum tipo_accion accion,
						 void *aux),
			 void *aux)
{
	switch (interaccion->accion.tipo) {
	case MOSTRAR_MENSAJE:
		mostrar_mensaje(interaccion->accion.mensaje, MOSTRAR_MENSAJE, 
				aux);		
		break;

	case DESCUBRIR_OBJETO:
		descubrir_objeto(sala, interaccion);
		mostrar_mensaje(interaccion->accion.mensaje, DESCUBRIR_OBJETO, 
				aux);
		break;

	case REEMPLAZAR_OBJETO:
		reemplazar_objeto(sala, interaccion);
		mostrar_mensaje(interaccion->accion.mensaje, REEMPLAZAR_OBJETO, 
				aux);
		break;

	case ELIMINAR_OBJETO:
		eliminar_objeto(sala, interaccion);
		mostrar_mensaje(interaccion->accion.mensaje, ELIMINAR_OBJETO, 
				aux);
		break;
	
	case ESCAPAR:
		sala->escapado = true;
		mostrar_mensaje(interaccion->accion.mensaje, ESCAPAR, aux);
		break; 

	default:
		mostrar_mensaje(interaccion->accion.mensaje, ACCION_INVALIDA, aux);
		return 0;
	}

	return 1;
}


int sala_ejecutar_interaccion(sala_t *sala, const char *verbo,
			      const char *objeto1, const char *objeto2,
			      void (*mostrar_mensaje)(const char *mensaje,
						      enum tipo_accion accion,
						      void *aux),
			      void *aux)
{
	if (sala == NULL || mostrar_mensaje == NULL || verbo == NULL || 
	    objeto1 == NULL || objeto2 == NULL)
		return 0;

	int ejecuciones = 0;
	lista_iterador_t *iterador = lista_iterador_crear(sala->interacciones);
	if (iterador == NULL)
		return 0;

	struct interaccion *interaccion;
	for (; lista_iterador_tiene_siguiente(iterador);
	     lista_iterador_avanzar(iterador)) {
		interaccion = lista_iterador_elemento_actual(iterador);

		if (interaccion_coincide(interaccion, verbo, objeto1, objeto2))
			ejecuciones += ejecutar_interaccion(sala, interaccion, 
							mostrar_mensaje, aux);
	}

	lista_iterador_destruir(iterador);

	return ejecuciones;
}


/*
 * Se recibe un puntero a una interaccion leida de la lista de interacciones,
 * y un puntero a una estructura con los objetos y verbo de la interaccion a
 * verificar si existe o es válida
 *
 * Se retorna un booleano que dice si la interacción existe en la lista (false) 
 * o si aun no se encontró (true)
 */
bool verificar_interaccion(void *interaccion1, 
			   void *interaccion2)
{
	struct interaccion *interaccion_actual = interaccion1;
	struct elementos_interaccion *interaccion = interaccion2;

	if (interaccion_coincide(interaccion_actual, interaccion->verbo, 
	    interaccion->objeto1, interaccion->objeto2)) {
		interaccion->existe = true;
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

	struct elementos_interaccion *interaccion = 
				malloc(sizeof(struct elementos_interaccion));
	if (interaccion == NULL)
		return false;

	interaccion->objeto1 = objeto1;
	interaccion->objeto2 = objeto2;
	interaccion->verbo = verbo;
	interaccion->existe = false;

	lista_con_cada_elemento(sala->interacciones, verificar_interaccion, 
				interaccion);

	if (interaccion->existe)
		interaccion_valida = true;

	free(interaccion);

	return interaccion_valida;
}


bool sala_escape_exitoso(sala_t *sala)
{
	if (sala == NULL)
		return false;

	return sala->escapado;
}


void sala_destruir(sala_t *sala)
{
	if (sala == NULL)
		return;

	hash_destruir_todo(sala->objetos, free);
	hash_destruir(sala->objetos_conocidos);
	hash_destruir(sala->objetos_poseidos);
	lista_destruir_todo(sala->interacciones, free);

	free(sala);
}