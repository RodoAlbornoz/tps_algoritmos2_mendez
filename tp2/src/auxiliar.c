#include "auxiliar.h"


size_t cantidad_objetos(sala_t *sala)
{
        return hash_cantidad(sala->objetos);
}


size_t cantidad_interacciones(sala_t *sala)
{
        return lista_tamanio(sala->interacciones);
}


bool sala_contiene_objeto(sala_t *sala, const char *nombre)
{
        return hash_contiene(sala->objetos, nombre);
}