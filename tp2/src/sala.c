#include "estructuras.h"
#include "sala.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interaccion.h"
#include "objeto.h"
#include "TDAs/lista.h"
#include "TDAs/hash.h"

#define CAPACIDAD_INICIAL_OBJETOS 5
#define LARGO_MAX_LINEA 1024

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
	size_t cantidad_nombres;
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
 * Se recibe la ruta al archivo de objetos y un puntero a un puntero a hash que
 * almacena la información de los objetos de la sala
 * 
 * Se lee el archivo de objetos, se guarda su información en el hash de 
 * objetos, y se devuelve el status de leer el archivo y guardar su información
 * (-1 si hubo error, cualquier otra cosa si no lo hubo)
 */
int lectura_archivo_objetos(const char *objetos, hash_t *hash_objetos)
{
	FILE *archivo_objetos = fopen(objetos, "r");
	if(!archivo_objetos)
		return -1;

	char linea_objetos[LARGO_MAX_LINEA];
	char *leida_objetos = fgets(linea_objetos, LARGO_MAX_LINEA, 
				    archivo_objetos);

	while (leida_objetos) {
		struct objeto *objeto_sala = 
				objeto_crear_desde_string(linea_objetos);
		if (objeto_sala == NULL) {
			hash_destruir(hash_objetos);
			fclose(archivo_objetos);
			return -1;
		}

		struct info_objeto *info_objeto = 
					malloc(sizeof(struct info_objeto));
		if (info_objeto == NULL)
			return -1;

		strcpy(info_objeto->descripcion, objeto_sala->descripcion);
		info_objeto->es_asible = objeto_sala->es_asible;

		char *copia_nombre = duplicar_string(objeto_sala->nombre);
		hash_objetos = hash_insertar(hash_objetos, copia_nombre, 
					     info_objeto, NULL);
		free(info_objeto);
		free(copia_nombre);
		free(objeto_sala);

		leida_objetos = fgets(linea_objetos, LARGO_MAX_LINEA, 
				      archivo_objetos);
	}

	fclose(archivo_objetos);
	return 0;
}


/*
 * Se recibe la ruta al archivo de interacciones y un puntero a un puntero a 
 * lista que almacena la información de las interacciones posibles de los 
 * objetos de la sala
 * 
 * Se lee el archivo de interacciones, se guarda su información en la lista de 
 * interacciones, y se devuelve el status de leer el archivo y guardar su 
 * información (-1 si hubo error, cualquier otra cosa si no lo hubo)
 */
int lectura_archivo_interacciones(const char *interacciones, 
				  lista_t *lista_interacciones)
{
	FILE *archivo_interacciones = fopen(interacciones, "r");
	if(!archivo_interacciones)
		return -1;

	char linea_interacciones[LARGO_MAX_LINEA];
	char *leida_interacciones = fgets(linea_interacciones, LARGO_MAX_LINEA, 
					  archivo_interacciones);

	while (leida_interacciones) {
		struct interaccion *interaccion_sala = 
			interaccion_crear_desde_string(linea_interacciones);
		if (interaccion_sala == NULL) {
			lista_destruir(lista_interacciones);
			fclose(archivo_interacciones);
			return -1;
		}

		lista_interacciones = lista_insertar(lista_interacciones, 
						      interaccion_sala);

		leida_interacciones = fgets(linea_interacciones, 
				LARGO_MAX_LINEA, archivo_interacciones);
	}

	fclose(archivo_interacciones);
	return 0;
}


/*
 * Se reserva memoria para la sala y se inicializan sus campos (Creando las
 * estructuras correspondientes para almacenar objetos e interacciones)
 */
sala_t *inicializar_sala()
{
	sala_t *sala = malloc(sizeof(struct sala));
	if (sala == NULL)
		return NULL;

	sala->escapado = false;
	sala->objetos = hash_crear(CAPACIDAD_INICIAL_OBJETOS);
	sala->objetos_conocidos = hash_crear(CAPACIDAD_INICIAL_OBJETOS);
	sala->objetos_poseidos = hash_crear(CAPACIDAD_INICIAL_OBJETOS);
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

	int status_objetos = lectura_archivo_objetos(objetos, 
						     sala->objetos);
	int status_interacciones = lectura_archivo_interacciones(interacciones, 
						sala->interacciones);
	size_t cantidad_objetos = hash_cantidad(sala->objetos);
	size_t cantidad_interacciones = lista_tamanio(sala->interacciones);

	if (status_objetos == -1 || status_interacciones == -1 || 
	    cantidad_objetos == 0 || cantidad_interacciones == 0) {
		sala_destruir(sala);
		return NULL;
	}

	return sala;
}


/*
 *
 *
 */
bool guardar_nombres(const char *nombre, void *info_objeto, 
		     void *nombres)
{
	struct nombres *nombres_objetos = nombres;
	char *nombre_objeto = (char *) nombre; // VER POR QUÉ ESTO FUNCIONÓ Y DECIR CÓMO LO ARREGLÉ

	nombres_objetos->vector_nombres[nombres_objetos->cantidad_nombres] = 
					nombre_objeto; // VER POR QUÉ ESTO FUNCIONÓ Y DECIR CÓMO LO ARREGLÉ
	(nombres_objetos->cantidad_nombres)++;

	return true;
}


char **sala_obtener_nombre_objetos(sala_t *sala, int *cantidad)
{
	if (sala == NULL) {
		if(cantidad != NULL)
			*cantidad = -1;
		return NULL;
	}

	int cantidad_objetos = (int) hash_cantidad(sala->objetos);

	char **vector_nombres = malloc((unsigned int) cantidad_objetos * 
					sizeof(char *));
	if (vector_nombres == NULL) {
		sala_destruir(sala);
		if (cantidad != NULL)
			*cantidad = -1; 
		return NULL;
	}

	struct nombres *nombres_objetos = malloc(sizeof(struct nombres));
	if (nombres_objetos == NULL) {
		sala_destruir(sala);
		return NULL;
	}
	nombres_objetos->cantidad_nombres = 0;
	nombres_objetos->vector_nombres = vector_nombres;

	hash_con_cada_clave(sala->objetos, guardar_nombres, nombres_objetos);

	if (cantidad != NULL)
		*cantidad = cantidad_objetos;

	free(nombres_objetos);
	return vector_nombres;
}


/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente conocidos por el jugador en la sala de escape.
 * No incluye los objetos poseidos por el jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_conocidos(sala_t *sala, int *cantidad)
{
	if (sala == NULL)
		return NULL;

	return NULL;
}


/*
 * Devuelve un vector dinámico reservado con malloc que contiene los nombres de
 * todos los objetos actualmente en posesión del jugador.
 *
 * En la variable cantidad (si no es nula) se guarda el tamanio del vector de
 * nombres.
 *
 * El vector devuelto debe ser liberado con free.
 *
 * En caso de error devuelve NULL y pone cantidad en -1.
 */
char **sala_obtener_nombre_objetos_poseidos(sala_t *sala, int *cantidad)
{
	if (sala == NULL)
		return NULL;

	return NULL;
}


/*
 * Hace que un objeto conocido y asible pase a estar en posesión del jugador.
 *
 * Devuelve true si pudo agarrar el objeto o false en caso de error (por ejemplo
 * el objeto no existe o existe pero no es asible o si dicho objeto ya está en
 * posesión del jugador).
 */
bool sala_agarrar_objeto(sala_t *sala, const char *nombre_objeto)
{
	if (sala == NULL)
		return false;

	return true;
}


/*
 * Obtiene la descripción de un objeto conocido o en posesión del usuario.
 *
 * Devuelve NULL en caso de error.
 */
char* sala_describir_objeto(sala_t* sala, const char *nombre_objeto)
{
	if (sala == NULL)	
		return NULL;

	return NULL;
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
bool verificar_interaccion_valida(void *interaccion_actual, 
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

	bool interacccion_valida = false;

	struct elementos_interaccion *elementos_interaccion = 
				malloc(sizeof(struct elementos_interaccion));
	if (elementos_interaccion == NULL)
		return false;
	elementos_interaccion->objeto1 = objeto1;
	elementos_interaccion->objeto2 = objeto2;
	elementos_interaccion->verbo = verbo;
	elementos_interaccion->es_valida = false;

	lista_con_cada_elemento(sala->interacciones, 
			verificar_interaccion_valida, elementos_interaccion);
	
	if (elementos_interaccion->es_valida)
		interacccion_valida = true;

	free(elementos_interaccion);

	return interacccion_valida;
}


/*
 * Devuelve true si se pudo escapar de la sala. False en caso contrario o si no existe la sala.
 */
bool sala_escape_exitoso(sala_t *sala)
{
	if (sala == NULL)
		return false;

	return sala->escapado;
}


/*
 *
 *
 */
/*
void destruir_objetos(void *info_objeto)
{
	struct info_objeto *objeto = info_objeto;
}
*/

/*
 *
 *
 */
void destruir_interacciones(void *interaccion_actual)
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
	lista_destruir_todo(sala->interacciones, destruir_interacciones);

	free(sala);
}