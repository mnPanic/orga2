%define NULL 0

; -> len => offset
;struct alumno {
;    short comision; -> 2 => 0  (a 2)
;    char * nombre;	 -> 8 => 8  (a 16)
;    int edad;		 -> 4 => 16 (a 20)
;};

%define offset_comision 0
%define offset_nombre 8
%define offset_edad 16

extern printf
global mostrarAlumno

section .rodata
	fmt: db "Nombre: %s, comision: %hd, edad: %d", 0x0a, 0x00

section .text
 
mostrarAlumno:
	; void mostrarAlumno(struct alumno * un_alumno);
	; un_alumno = rdi
	push rbp
	mov rbp, rsp
	; Pila alineada

	; printf(char* fmt, nombre, comision, edad)
	; rdi = fmt
	; rsi = nombre
	; dx  = comision
	; ecx = edad
	mov rsi, [rdi + offset_nombre]
	mov dx,  [rdi + offset_comision]
	mov ecx, [rdi + offset_edad]
	mov rdi, fmt

	call printf
	; Desencolo
	pop rbp
	ret
