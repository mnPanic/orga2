#include <stdio.h>

extern void imprime_parametros(int, double, char*);

int main()
{
	imprime_parametros(10, 20.0, "Mi pequeño chambeln");
	return 0;
}
