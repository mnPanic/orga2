section .data
	format: DB '%i, %f, %s', 0

global suma_parametros
extern printf

section .text
	suma_parametros: ; suma_parametros(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
		; Queremos ejecutar printf(char *, int a, double f, char* s)

		PUSH RBP
		sub 
		mov RAX, 1
		mov RDX, RSI
		mov RSI, RDI
		mov RDI, format
		; Ya tenemos en XMM0 el float

		call printf
		add RSP, 8

		ret