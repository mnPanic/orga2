extern malloc
extern printf
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
	mov [rax], BYTE 42
	mov rdi, formato_puntero_entero
	mov rsi, rax
	mov rax, 1
	call printf
	pop rbp
	ret