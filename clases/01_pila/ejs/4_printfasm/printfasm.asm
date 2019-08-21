section .data
	format: DB '%i, %f, %s', 0

global imprime_parametros
extern printf

section .text
	imprime_parametros: ; imprime_parametros(int a, double f, char* s)
						;					  RDI ,   XMM0  ,   RSI
		; Queremos ejecutar printf(char *, int a, double f, char* s)

		sub RSP, 8
		mov RAX, 1
		mov RDX, RSI
		mov RSI, RDI
		mov RDI, format
		; Ya tenemos en XMM0 el float

		call printf
		add RSP, 8

		ret