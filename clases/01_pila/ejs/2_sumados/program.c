#include <stdio.h>

extern int sumarDos(int, int);

int main()
{
	int a = 4;
	int b = 19;
	printf("Hacemos %i + %i = %i\n", a, b, sumarDos(a, b));
	return 0;
}
