%define NULL 0
; Completar!
%define offset_comision 0
; Completar!
%define offset_nombre 8
; Completar!
%define offset_edad 16

extern printf

global mostrarAlumno

section .data
	texto: db "Nombre: %s, comision: %hd, edad: %d", 0x0a, 0x00

section .text

; Me llega por RDI el PUNTERO a la estructura
mostrarAlumno:
	push rbp
	mov rbp, rsp
	; Pila alineada

	; Poner los elementos del struct en los registros necesarios
	; y llamar a printf

	mov rsi, [rdi + offset_nombre]
	mov dx, [rdi + offset_comision]
	mov ecx, [rdi + offset_edad]
	mov rdi, texto
	mov rax, 0

	call printf

	; Desencolo
	pop rbp
	ret
