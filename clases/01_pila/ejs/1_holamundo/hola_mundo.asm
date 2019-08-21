section .data
	msg: DB "Hola mundo bro", 10
	largo EQU $ - msg

	global _start

section .text
	_start:
	mov rax, 4
	mov rbx, 1
	mov rcx, msg
	mov rdx, largo
	int 0x80

	mov rax, 1
	mov rbx, 0
	int 0x80