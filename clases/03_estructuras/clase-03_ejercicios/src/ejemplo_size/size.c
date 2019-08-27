#include <stdio.h>      /* printf, scanf, NULL */
#include <stdlib.h>     /* malloc, free, rand */
#include "size.h"

int main(){
	struct alumno alu;
	struct alumno2 alu2;
	struct alumno3 alu3;

	printf("Tamaño de los tipos básicos:\n");
	printf("\tint\t%d bytes \n", (int) sizeof(int));
	printf("\tshort\t%d bytes \n", (int) sizeof(short));
	printf("\tchar\t%d bytes \n", (int) sizeof(char));
	printf("\tfloat\t%d bytes \n", (int) sizeof(float));
	printf("\tdouble\t%d bytes \n", (int) sizeof(double));
	printf("\n");
	
	printf("Tamaño de punteros a tipos básicos:\n");
	printf("\tint*\t%d bytes \n", (int) sizeof(int*));
	printf("\tshort*\t%d bytes \n", (int) sizeof(short*));
	printf("\tchar*\t%d bytes \n", (int) sizeof(char*));
	printf("\tfloat*\t%d bytes \n", (int) sizeof(float*));
	printf("\tdouble*\t%d bytes \n", (int) sizeof(double*));
	printf("\n");
	
	printf("Tamaño de enum {tipo_auto, tipo_camion} y su puntero:\n");
	printf("\tenum tipos\t%d bytes \n", (int) sizeof(enum tipos));
	printf("\tenum tipos*\t%d bytes \n", (int) sizeof(enum tipos*));
	printf("\n");
	
	printf("Tamaño de los structs de alumno:\n");
	printf("\tstruct alumno\t%d bytes \n", (int) sizeof(struct alumno));
	printf("\tstruct alumno2\t%d bytes \n", (int) sizeof(struct alumno2));
	printf("\tstruct alumno3\t%d bytes \n", (int) sizeof(struct alumno3));
	printf("\tstruct alumno4\t%d bytes \n", (int) sizeof(struct alumno4));
	printf("\tstruct alumno5\t%d bytes \n", (int) sizeof(struct alumno5));
	printf("\n");
	
	printf("Tamaño de punteros a los structs de alumno:\n");
	printf("\tstruct alumno*\t%d bytes \n", (int) sizeof(struct alumno*));
	printf("\tstruct alumno2*\t%d bytes \n", (int) sizeof(struct alumno2*));
	printf("\tstruct alumno3*\t%d bytes \n", (int) sizeof(struct alumno3*));
	printf("\tstruct alumno4*\t%d bytes \n", (int) sizeof(struct alumno4*));
	printf("\tstruct alumno5*\t%d bytes \n", (int) sizeof(struct alumno5*));
	printf("\n");

	printf("Tamaño y offsets del struct alumno:\n");
	printf("\tOFFSET alumno.nombre\t%d bytes \n", (int)((long long int)(&(alu.nombre)) - (long long int)(&(alu))) );
	printf("\tOFFSET alumno.comision\t%d bytes \n", (int)((long long int)(&(alu.comision)) - (long long int)(&(alu))) );
	printf("\tOFFSET alumno.dni\t%d bytes \n", (int)((long long int)(&(alu.dni)) - (long long int)(&(alu))) );
	printf("\tSIZE struct alumno\t%d bytes \n", (int) sizeof(struct alumno));
	printf("\n");
	
	printf("Tamaño y offsets del struct alumno2:\n");
	printf("\tOFFSET alumno2.comision\t%d bytes \n", (int)((long long int)(&(alu2.comision)) - (long long int)(&(alu2))) );
	printf("\tOFFSET alumno2.nombre\t%d bytes \n", (int)((long long int)(&(alu2.nombre)) - (long long int)(&(alu2))) );
	printf("\tOFFSET alumno2.dni\t%d bytes \n", (int)((long long int)(&(alu2.dni)) - (long long int)(&(alu2))) );
	printf("\tSIZE struct alumno2\t%d bytes \n", (int) sizeof(struct alumno2));
	printf("\n");
	
	printf("Tamaño y offsets del struct alumno3:\n");
	printf("\tOFFSET alumno3.nombre\t%d bytes \n", (int)((long long int)(&(alu3.nombre)) - (long long int)(&(alu3))) );
	printf("\tOFFSET alumno3.dni\t%d bytes \n", (int)((long long int)(&(alu3.dni)) - (long long int)(&(alu3))) );
	printf("\tOFFSET alumno3.comision\t%d bytes \n", (int)((long long int)(&(alu3.comision)) - (long long int)(&(alu3))) );
	printf("\tSIZE struct alumno3\t%d bytes \n", (int) sizeof(struct alumno3));
	
	return 0;
}
