global _start

section .rodata
	msg:  DB "Hola mundo!", 10, 0 	; 10: \n, 0: Fin de secuencia
	largo EQU $ - msg

section .text
	_start:
		mov rax, 4		; 4: sys_write
		mov rbx, 1		; 1: stdout
		mov rcx, msg
		mov rdx, largo
		int 0x80

		mov rax, 1		; 1: exit
		mov rbx, 0		; 0: ok
		int 0x80
