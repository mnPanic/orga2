global borrarUltimo
global agregarPrimero
extern free
extern malloc

%define NULL 0
; -> size => offset
; struct nodo{
; 	int dato;			-> 4 => 0 (a 4)
;	struct nodo *prox;	-> 8 => 8 (a 16)
; }; -> 16
; struct lista{
;	struct nodo *primero;	-> 8 => 0 (a 8)
; }; -> 8

; Definir los offsets para nodo
%define nodo_offset_dato 0
%define nodo_offset_prox 8
; Definir los offsets para lista
%define lista_offset_primero 0
; Definir el tamaño de los nodos
%define tam_nodo 16

%define r8_next r8
%define r9_prev r9
%define rdi_l rdi

borrarUltimo:
	; void borrarUltimo(struct lista *l)
	; l = rdi
	; Armo stack frame para estar alineado
	push rbp
	mov rbp, rsp

	; Me guardo la direccion de la dir del siguiente
	lea r8_next, [rdi_l + lista_offset_primero]	; r8 = next
	mov r9_prev, r8								; r9 = prev
	
	; Recorro hasta que el puntero sea null
.ciclo:
	cmp	word [r8_next], NULL
	je .fin
	mov r9_prev, r8_next
	lea r8_next, [r8_next + nodo_offset_prox]
	jmp .ciclo

.fin:
	; Estoy en el fin, borro el último
	mov rdi, [r9_prev]
	push r9_prev ; alineado
	call free
	pop r9_prev
	mov word [r9_prev], NULL

	; Reestablezco stack
	pop rbp
	ret

agregarPrimero:
	; void agregarPrimero(struct lista* l, int unInt)
	; l 	= rdi
	; unInt = esi
	; Stack frame
	push rbp
	mov rbp, rsp
	; Preservo parámetros
	push r12
	push rbx

	mov r12, rdi 	; l = rdi = r12
	mov ebx, esi	; n = esi = ebx

	; Creo el nuevo nodo
	mov rdi, tam_nodo
	call malloc 							; rax = nuevo nodo
	mov [rax + nodo_offset_dato], ebx 		; Seteo el dato al nodo
	mov rdi, [r12 + lista_offset_primero]
	mov [rax + nodo_offset_prox], rdi 		; Seteo el siguiente
	mov [r12 + lista_offset_primero], rax 	; Seteo el nuevo primero de la lista

	; Reestablezco
	pop rbx
	pop r12
	pop rbp
	ret
