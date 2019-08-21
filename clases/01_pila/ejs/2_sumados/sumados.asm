global sumarDos

section .text
	
	sumarDos: ; (int a, int b)
		MOV RAX, RDI
		ADD RAX, RSI

		RET