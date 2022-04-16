#include "src/sala.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
		return -1;

	sala_t *sala = sala_crear_desde_archivos(argv[1], argv[2]);
	
	if (sala != NULL) {
		printf("Objetos...\n");

		int cant_nombres_objetos = 0;
		char **vector_nombres_objetos = sala_obtener_nombre_objetos(sala, &cant_nombres_objetos);

		if (vector_nombres_objetos == NULL)
			return -1;

		for (int i = 0; i < cant_nombres_objetos; i++) 
			printf("%i: %s\n", i, vector_nombres_objetos[i]);

		printf("\nInteracciones...\n");
		if (sala_es_interaccion_valida(sala, "examinar", "habitacion", ""))
			printf("Examinar la habitacion: Valido\n");
		
		if (sala_es_interaccion_valida(sala, "abrir", "pokebola", ""))
			printf("Abrir pokebola: Valido\n");

		if (sala_es_interaccion_valida(sala, "usar", "llave", "cajon"))
			printf("Usar llave en el cajon: Valido\n");

		if (sala_es_interaccion_valida(sala, "quemar", "mesa", ""))
			printf("Quemar la mesa: Valido\n");

		free(vector_nombres_objetos);
	}

	sala_destruir(sala);
	
	return 0;
}