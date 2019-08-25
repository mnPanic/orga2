; Construir una función en ASM con la siguiente aridad:
; 	int suma_parametros( int a0, int a1, int a2, int a3,
; 						 int a4, int a5 ,int a6, int a7 );
; Ésta retorna el resultado de la operación:
; a0-a1+a2-a3+a4-a5+a6-a7
global suma_parametros
section .text
	suma_parametros: ; suma_parametros(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7)
		; RDI = a0
		; RSI = a1
		; RDX = a2
		; RCX = a3
		; R8  = a4
		; R9  = a5
		; Los restantes en la pila
		; RBP + 8  = rbp viejo
		; RBP + 16 = a7
		; RBP + 24 = a6
		
		; stack frame
		push rbp
		mov rbp, rsp
		; a0-a1+a2-a3+a4-a5+a6-a7
		mov rax, rdi
		sub rax, rsi
		add rax, rdx
		sub rax, rcx
		add rax, r8
		sub rax, r9
		add rax, [rbp + 24]
		sub rax, [rbp + 16]
		
		; stack frame
		pop rbp
		ret 