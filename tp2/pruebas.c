#include "pa2mm.h"
#include "src/estructuras.h"
#include "src/sala.h"
#include "src/objeto.h"
#include "src/interaccion.h"
#include "src/auxiliar.h"

#include "string.h"
#include <stdbool.h>


void pruebasCrearObjeto()
{
	pa2m_afirmar(objeto_crear_desde_string(NULL) == NULL,
		     "No puedo crear un objeto a partir de un string NULL");
	pa2m_afirmar(objeto_crear_desde_string("") == NULL,
		     "No puedo crear un objeto a partir de un string vacío");
	pa2m_afirmar(objeto_crear_desde_string("a;b") == NULL,
		     "\"a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;b") == NULL,
		     "\"a;;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;b") == NULL,
		     "\";a;b\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;b;c") == NULL,
		     "\"a;b;c\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string("a;;true") == NULL,
		     "\"a;;true\" no es un string objeto válido");
	pa2m_afirmar(objeto_crear_desde_string(";a;false") == NULL,
		     "\";a;false\" no es un string objeto válido");

	struct objeto *objeto1 = objeto_crear_desde_string("nombre;desc;true");
	pa2m_afirmar(objeto1, "\"nombre;desc;true\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto1->nombre, "nombre") == 0, "El nombre del objeto es \"nombre\"");
	pa2m_afirmar(strcmp(objeto1->descripcion, "desc") == 0,
		     "La descripcion del objeto es \"desc\"");
	pa2m_afirmar(objeto1->es_asible == true, "El objeto es asible");

	struct objeto *objeto2 = objeto_crear_desde_string("A;Be;false\n");
	pa2m_afirmar(objeto2, "\"A;Be;false\\n\" es un string objeto válido");
	pa2m_afirmar(strcmp(objeto2->nombre, "A") == 0, "El nombre del objeto es \"A\"");
	pa2m_afirmar(strcmp(objeto2->descripcion, "Be") == 0,
		     "La descripcion del objeto es \"Be\"");
	pa2m_afirmar(objeto2->es_asible == false, "El objeto no es asible");

	free(objeto1);
	free(objeto2);
}


void pruebasCrearInteracciones()
{
	pa2m_afirmar(interaccion_crear_desde_string(NULL) == NULL,
		     "No puedo crear una interacción a partir de un string NULL");
	pa2m_afirmar(interaccion_crear_desde_string("") == NULL,
		     "No puedo crear una interacción a partir de un string vacío");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c:d:e") == NULL,
		     "\"a;b;c:d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d") == NULL,
		     "\"a;b;c;d\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;c;d:e") == NULL,
		     "\"a;b;c;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;d:e") == NULL,
		     "\"a;b;_;d:e\" no es un string interacción válido");
	pa2m_afirmar(interaccion_crear_desde_string("a;b;_;de:f:g") == NULL,
		     "\"a;b;_;de:f:g\" no es un string interacción válido");

	struct interaccion *inter1 = interaccion_crear_desde_string("a;b;c;d:e:f");
	pa2m_afirmar(inter1, "\"a;b;c;d:e:f\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter1->objeto, "a") == 0, "El nombre del objeto es \"a\"");
	pa2m_afirmar(strcmp(inter1->verbo, "b") == 0, "El verbo es \"b\"");
	pa2m_afirmar(strcmp(inter1->objeto_parametro, "c") == 0, "El segundo objeto es \"c\"");
	pa2m_afirmar(inter1->accion.tipo == DESCUBRIR_OBJETO,
		     "El tipo de acción es DESCUBRIR_OBJETO");
	pa2m_afirmar(strcmp(inter1->accion.objeto, "e") == 0, "El objeto de la acción es \"e\"");
	pa2m_afirmar(strcmp(inter1->accion.mensaje, "f") == 0, "El mensaje de la acción es \"f\"");

	struct interaccion *inter2 = interaccion_crear_desde_string("OB;VER;_;m:_:MSG");
	pa2m_afirmar(inter1, "\"OB;VER;_;m:_:MSG\" es un string interacción válido");
	pa2m_afirmar(strcmp(inter2->objeto, "OB") == 0, "El nombre del objeto es \"OB\"");
	pa2m_afirmar(strcmp(inter2->verbo, "VER") == 0, "El verbo es \"VER\"");
	pa2m_afirmar(strcmp(inter2->objeto_parametro, "") == 0, "El segundo objeto es vacío");
	pa2m_afirmar(inter2->accion.tipo == MOSTRAR_MENSAJE,
		     "El tipo de acción es MOSTRAR_MENSAJE");
	pa2m_afirmar(strcmp(inter2->accion.objeto, "") == 0, "El objeto de la acción es vacío");
	pa2m_afirmar(strcmp(inter2->accion.mensaje, "MSG") == 0,
		     "El mensaje de la acción es \"MSG\"");

	free(inter1);
	free(inter2);
}


void pruebas_crear_sala()
{
	pa2m_afirmar(sala_crear_desde_archivos("/ASD/ASD/", "dasD/sa2asdd") == NULL,
		     "No puedo crear la sala a partír de archivos inexistentes");

	pa2m_afirmar(sala_crear_desde_archivos("", "chanu/int.csv") == NULL,
		     "No puedo crear la sala sin objetos");

	pa2m_afirmar(sala_crear_desde_archivos("chanu/obj.dat", "chanu/vacio.txt") == NULL,
		     "No puedo crear la sala sin interacciones");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala != NULL, "Puedo crear la sala a partir de archivos no vacíos");
	pa2m_afirmar(cantidad_objetos(sala) == 9, "Se leyeron 9 objetos");
	pa2m_afirmar(cantidad_interacciones(sala) == 9, "Se leyeron 9 interacciones");

	sala_destruir(sala);
}


void pruebas_nombre_objetos()
{
	int cantidad = 0;
	pa2m_afirmar(sala_obtener_nombre_objetos(NULL, &cantidad) == NULL,
		     "No puedo obtener los nombres de objetos de una sala NULL");
	pa2m_afirmar(cantidad == -1, 
		     "La cantidad es -1 luego de invocar a la función");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	char **objetos = sala_obtener_nombre_objetos(sala, NULL);
	pa2m_afirmar(objetos != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad NULL");

	char **objetos2 = sala_obtener_nombre_objetos(sala, &cantidad);
	pa2m_afirmar(objetos2 != NULL,
		     "Puedo pedir el vector de nombres a la sala pasando cantidad no NULL");
	pa2m_afirmar(cantidad == 9, "La cantidad de elementos del vector coincide con lo esperado");

	const char *esperados[] = { "habitacion",    "mesa",  "interruptor", "pokebola", "cajon",
				    "cajon-abierto", "llave", "anillo",	     "puerta" };

	int comparaciones_exitosas = 0;
	for (int i = 0; i < cantidad; i++)
		if (sala_contiene_objeto(sala, esperados[i]))
			comparaciones_exitosas++;

	pa2m_afirmar(comparaciones_exitosas == cantidad,
		     "Todos los nombres de objeto son los esperados");

	free(objetos);
	free(objetos2);
	sala_destruir(sala);
}


void pruebas_nombre_objetos_conocidos()
{
	int cantidad = 0;

	pa2m_afirmar(sala_obtener_nombre_objetos_conocidos(NULL, &cantidad) == NULL, 
	"No se pueden obtener los nombres de objetos conocidos en una sala NULL.");
	pa2m_afirmar(cantidad == -1, 
	"La cantidad es -1 después de invocada la función.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, NULL);
	pa2m_afirmar(conocidos != NULL, 
	"Se obtiene un vector de nombres de objetos conocidos de la sala con cantidad NULL.");

	cantidad = 0;
	char **conocidos2 = sala_obtener_nombre_objetos_conocidos(sala, &cantidad);
	pa2m_afirmar(conocidos2 != NULL, 
	"Se obtiene un vector de nombres de objetos conocidos de la sala con cantidad no NULL.");

	pa2m_afirmar(cantidad == 1, 
	"La cantidad de elementos conocidos es la correcta (Inicialmente conozco el primer objeto de la sala).");

	free(conocidos);
	free(conocidos2);
	sala_destruir(sala);
}


void pruebas_nombre_objetos_poseidos()
{
	int cantidad = 0;

	pa2m_afirmar(sala_obtener_nombre_objetos_poseidos(NULL, &cantidad) == NULL, 
	"No se pueden obtener los nombres de objetos poseidos en una sala NULL.");
	pa2m_afirmar(cantidad == -1, 
	"La cantidad es -1 después de invocada la función.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, NULL);
	pa2m_afirmar(poseidos != NULL, 
	"Se obtiene un vector de nombres de objetos poseidos de la sala con cantidad NULL.");

	char **poseidos2 = sala_obtener_nombre_objetos_poseidos(sala, &cantidad);
	pa2m_afirmar(poseidos2 != NULL, 
	"Se obtiene un vector de nombres de objetos poseidos de la sala con cantidad no NULL.");

	pa2m_afirmar(cantidad == 0, 
	"La cantidad de elementos poseidos es la correcta (Inicialmente no poseo ninguno).");

	free(poseidos);
	free(poseidos2);
	sala_destruir(sala);
}


void pruebas_agarrar_objeto()
{
	const char *nombre = "llave";

	pa2m_afirmar(!sala_agarrar_objeto(NULL, nombre), 
	"No se puede agarrar un objeto en una sala NULL.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	pa2m_afirmar(!sala_agarrar_objeto(sala, NULL), 
	"No se puede agarrar un objeto con nombre NULL.");

	sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL);

	pa2m_afirmar(sala_agarrar_objeto(sala, "pokebola"), 
	"Se agarra un objeto conocido y asible.");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "pokebola"),
	"No se puede volver a agarrar un objeto ya poseido.");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "llave"),
	"No se puede agarrar un objeto no conocido.");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "puerta"), 
	"No se puede agarrar un objeto no asible.");

	pa2m_afirmar(!sala_agarrar_objeto(sala, "bomba"), 
	"No se puede agarrar un objeto no existente.");

	sala_destruir(sala);
}


void pruebas_describir_objeto()
{
	pa2m_afirmar(sala_describir_objeto(NULL, "habitacion") == NULL, 
	"No se puede obtener descripción de un objeto en una sala NULL.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	pa2m_afirmar(sala_describir_objeto(sala, NULL) == NULL,
	"No se puede obtener descripción de un objeto con nombre NULL.");
	
	pa2m_afirmar(sala_describir_objeto(sala, "habitacion") != NULL, 
	"Se retorna la descripcion de un objeto conocido.");

	sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL);
	sala_agarrar_objeto(sala, "pokebola");

	pa2m_afirmar(sala_describir_objeto(sala, "pokebola") != NULL, 
	"Se retorna la descripcion de un objeto poseido.");

	pa2m_afirmar(sala_describir_objeto(sala, "Mechero") == NULL, 
	"No se retorna la descripcion de un objeto que no existe.");

	pa2m_afirmar(sala_describir_objeto(sala, "llave") == NULL, 
	"No se retorna la descripcion de un objeto no conocido ni poseido.");

	sala_destruir(sala);
}


void imprimir_mensaje(const char *mensaje, enum tipo_accion accion, void *aux)
{
	printf("%s\n", mensaje);
}


void pruebas_descubrir_objeto(sala_t *sala)
{
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL) == 0, // ERROR ELIMINANDO POKEBOLA
	"Quiero descubrir un objeto sin poseer el primer objeto (Pokebola)");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL) == 2,
	"Se ejecuta mas de una interaccion sobre un objeto.");

	int cantidad_conocidos = 0;
	bool es_conocido = false;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	for (int i = 0; i < cantidad_conocidos; i++)
		if (strcmp(conocidos[i], "puerta") == 0)
			es_conocido = true;
	pa2m_afirmar(es_conocido, "Se ejecuta una interacción con accion DESCUBRIR OBJETO. Ahora conozco la puerta.");

	for (int i = 0; i < cantidad_conocidos; i++)
		if (strcmp(conocidos[i], "pokebola") == 0)
			es_conocido = true;
	pa2m_afirmar(es_conocido, "Se ejecuta una interacción con accion DESCUBRIR OBJETO. Ahora conozco la pokebola.");
	free(conocidos);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL) == 0,
	"Quiero descubrir objetos que ya conozco (Pokebola y puerta)");
}


void pruebas_mostrar_mensaje(sala_t *sala)
{
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta", "", imprimir_mensaje, NULL) == 1,
	"Se ejecuta una interacción con accion MOSTRAR MENSAJE con funcion de imprimir mensaje no NULL.");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta", "", NULL, NULL) == 1,
	"Se ejecuta una interacción con accion MOSTRAR MENSAJE con funcion de imprimir mensaje NULL.");
}


void pruebas_eliminar_objeto(sala_t *sala)
{
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL) == 2,
	"Puedo abrir la pokebola sin poseerla");

	int cantidad_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	bool ya_no_se_posee = true;

	for (int i = 0; i < cantidad_poseidos; i++)
		if (strcmp(poseidos[i], "pokebola") == 0)
			ya_no_se_posee = false;

	pa2m_afirmar(ya_no_se_posee,
	"Se ejecuta una interacción con accion ELIMINAR OBJETO. Ya no poseo la pokebola");

	free(poseidos);
}


void pruebas_reemplazar_objeto(sala_t *sala)
{
	int cantidad_poseidos = 0;
	char **poseidos = sala_obtener_nombre_objetos_poseidos(sala, &cantidad_poseidos);
	bool se_posee = false;

	for (int i = 0; i < cantidad_poseidos; i++)
		if (strcmp(poseidos[i], "llave") == 0)
			se_posee = true;

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL) == 0 && !se_posee, 
	"Quiero abrir la puerta con la llave, pero no poseo la llave.");

	sala_agarrar_objeto(sala, "llave");

	sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL);

	int cantidad_conocidos = 0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);

	bool ya_no_la_conozco = true;
	for (int i = 0; i < cantidad_conocidos; i++)
		if (strcmp(conocidos[i], "puerta") == 0)
			ya_no_la_conozco = false;
	pa2m_afirmar(ya_no_la_conozco, 
	"Se ejecuta una interaccion con accion REEMPLAZAR OBJETO. Ya no conozco la puerta.");

	bool es_conocido = false;
	for (int i = 0; i < cantidad_conocidos; i++)
		if (strcmp(conocidos[i], "puerta-abierta") == 0)
			es_conocido = true;
	pa2m_afirmar(es_conocido, 
	"Se ejecuta una interaccion con accion REEMPLAZAR OBJETO. Ahora conozco la puerta abierta.");	

	free(conocidos);
	free(poseidos);
}


void pruebas_ejecutar_interaccion()
{
	pa2m_afirmar(sala_ejecutar_interaccion(NULL, "abrir", "llave", "puerta", 
	imprimir_mensaje, NULL) == 0, 
	"No se puede ejecutar una interacción en una sala NULL.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, NULL, "llave", "puerta", 
	imprimir_mensaje, NULL) == 0, 
	"No se puede ejecutar una interacción con verbo NULL.");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", NULL, "puerta", 
	imprimir_mensaje, NULL) == 0, 
	"No se puede ejecutar una interacción con primer objeto NULL.");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave", NULL, 
	imprimir_mensaje, NULL) == 0, 
	"No se puede ejecutar una interacción con segundo objeto NULL.");

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "quemar", "habitacion", "", 
	imprimir_mensaje, NULL) == 0, 
	"No se ejecuta una interaccion inexistente.");	

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "puerta", "", imprimir_mensaje, NULL) == 0,
	"Intento ejecutar una interacción que imprime un mensaje cuando NO conozco el primer objeto (puerta).");

	int cantidad_conocidos = 0;
	char **conocidos = sala_obtener_nombre_objetos_conocidos(sala, &cantidad_conocidos);
	bool es_conocido = false;
	for (int i = 0; i < cantidad_conocidos; i++)
		if (strcmp(conocidos[i], "puerta") == 0)
			es_conocido = true;
	pa2m_afirmar(sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL) == 0 && !es_conocido, 
	"Quiero abrir la puerta con la llave, pero no conozco la puerta.");
	free(conocidos);

	pa2m_nuevo_grupo("Pruebas de descubrimiento de objetos");
	pruebas_descubrir_objeto(sala);

	pa2m_nuevo_grupo("Pruebas de mostrar mensaje");
	pruebas_mostrar_mensaje(sala);

	pa2m_nuevo_grupo("Pruebas de eliminacion de objetos");
	pruebas_eliminar_objeto(sala);

	pa2m_nuevo_grupo("Pruebas de reemplazo de objetos");
	pruebas_reemplazar_objeto(sala);	

	sala_destruir(sala);
}


void pruebas_interacciones()
{
	pa2m_afirmar(sala_es_interaccion_valida(NULL, "hacer", NULL, NULL) == false,
		     "No es válido pedir interacciones de una sala NULL");

	sala_t *sala = sala_crear_desde_archivos("chanu/obj.dat", "chanu/int.csv");

	pa2m_afirmar(sala_es_interaccion_valida(sala, NULL, "", "") == false, "No es válida una intearcción con verbo NULL");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "hacer", NULL, "") == false, "No es válida una intearcción con objeto NULL");

	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "habitacion", "") == true, "Puedo examinar la habitación");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "usar", "llave", "cajon") == true, "Puedo usar la llave en el cajón");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "pokebola", "") == true, "Puedo abrir la pokebola");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "cajon-abierto", "") == true, "Puedo examinar el cajón abierto");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "romper", "todo", "") == false, "No puedo romper todo");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "abrir", "mesa", "") == false, "No puedo abrir la mesa");
	pa2m_afirmar(sala_es_interaccion_valida(sala, "examinar", "techo", "") == false, "No puedo examinar el techo");

	sala_destruir(sala);
}


void pruebas_escape_sala()
{
	pa2m_afirmar(!sala_escape_exitoso(NULL), 
		     "No se puede escapar de una sala NULL.");

	sala_t *sala = sala_crear_desde_archivos("ejemplo/objetos.txt", "ejemplo/interacciones.txt");

	pa2m_afirmar(!sala_escape_exitoso(sala), 
		     "Aun no se pudo escapar de la sala.");

	sala_ejecutar_interaccion(sala, "examinar", "habitacion", "", NULL, NULL);
	sala_agarrar_objeto(sala, "pokebola");
	sala_ejecutar_interaccion(sala, "abrir", "pokebola", "", NULL, NULL);
	sala_agarrar_objeto(sala, "llave");
	sala_ejecutar_interaccion(sala, "abrir", "llave", "puerta", NULL, NULL);

	pa2m_afirmar(sala_ejecutar_interaccion(sala, "salir", "puerta-abierta", "", NULL, NULL) == 1, 
	"Se ejecuta una interacción con accion ESCAPAR");

	pa2m_afirmar(sala_escape_exitoso(sala), "Se escapó exitosamente de la sala.");

	sala_destruir(sala);
}


int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de objetos");
	pruebasCrearObjeto();

	pa2m_nuevo_grupo("Pruebas de creación de interacciones");
	pruebasCrearInteracciones();

	pa2m_nuevo_grupo("Pruebas de creación de sala");
	pruebas_crear_sala();

	pa2m_nuevo_grupo("Pruebas del vector de nombres");
	pruebas_nombre_objetos();

	pa2m_nuevo_grupo("Pruebas del vector de nombres conocidos");
	pruebas_nombre_objetos_conocidos();

	pa2m_nuevo_grupo("Pruebas del vector de nombres poseidos");
	pruebas_nombre_objetos_poseidos();

	pa2m_nuevo_grupo("Pruebas de agarrado de objetos");
	pruebas_agarrar_objeto();

	pa2m_nuevo_grupo("Pruebas de descripción de objetos");
	pruebas_describir_objeto();

	pa2m_nuevo_grupo("Pruebas de ejecución de interacciones");
	pruebas_ejecutar_interaccion();

	pa2m_nuevo_grupo("Pruebas de interacciones");
	pruebas_interacciones();

	pa2m_nuevo_grupo("Pruebas de escape de sala");
	pruebas_escape_sala();

	return pa2m_mostrar_reporte();
}
