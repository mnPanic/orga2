extern malloc
extern printf
extern free
%define size_int 4

section .data:
formato_puntero_entero: DB 'f1_asm: %d',10,'f1_asm: debería imprimir 42',10,10,0

section .text:
global f1_asm
f1_asm:
	push rbp
	mov rbp, rsp
	mov rdi, size_int
	call malloc
	; El mov debería ser de a DWORD, no de a BYTE
	mov [rax], DWORD 42
	mov rdi, formato_puntero_entero
	; El mov a rsi debería ser de [rax], no de rax
	mov rsi, [rax]
	; Luego de printf, habría que llamar a free
	; Para ello, es necesario preservar el puntero que estaba en rax
	; Para eso se preservará rax
	; Además, hay que llamar a printf con la pila alineada
	push rax
	sub rsp, 8
	mov rax, 1
	call printf
	add rsp, 8
	pop rax
	mov rdi, rax
	call free
	pop rbp
	ret