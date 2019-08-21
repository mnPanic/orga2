#include <stdio.h>

extern double sumarDosD(double, double);

int main()
{
	double a = 4.5;
	double b = 19.0;
	printf("Hacemos %f + %f = %f\n", a, b, sumarDosD(a, b));
	return 0;
}
