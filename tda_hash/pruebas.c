#include "src/hash.h"
#include "pa2m.h"


void hash_probar_cantidad()
{
	pa2m_nuevo_grupo("Pruebas de elementos almacenados en un hash");

	hash_t *hash = hash_crear();

	pa2m_afirmar(hash_cantidad(hash));
}


int main()
{
	hash_probar_cantidad();

	return pa2m_mostrar_reporte();
}
