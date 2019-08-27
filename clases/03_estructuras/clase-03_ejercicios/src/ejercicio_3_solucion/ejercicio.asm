global borrarUltimo
global agregarPrimero
extern free
extern malloc

%define NULL 0
; Definir los offsets para nodo
%define nodo_offset_dato 0
%define nodo_offset_prox 8
; Definir los offsets para lista
%define lista_offset_primero 0
; Definir el tamaño de los nodos
%define tam_nodo 16

; void borrar(struct nodo **unDoblePunteroANodo)
;	rdi = nodo** unDoblePunteroANodo
borrar:
	push rdi
	mov rdi, [rdi]
	call free
	pop rdi
	mov QWORD [rdi], NULL
	ret

; void borrarUltimo(struct lista *unaLista) 
; 	rdi = lista* unaLista
borrarUltimo:
	push rbp
	mov rbp, rsp

	lea rsi, [rdi+lista_offset_primero]
	mov rdi, rsi

	.loop:
	cmp QWORD [rsi], NULL
	je .finLoop
	mov rdi, rsi
	mov rsi, [rsi]
	lea rsi, [rsi+nodo_offset_prox]
	jmp .loop

	.finLoop:
	call borrar

	pop rbp
	ret


; void agregarPrimero(struct lista* unaLista, int unInt)
; 	rdi = lista* unaLista
; 	esi = int unInt
agregarPrimero:
	push rbp
	mov rbp, rsp
	; preservo registros r12 y r13, ya que los voy a usar
	push r12
	push r13
	; tengo que guardar los valores de rdi y rsi ya que voy a llamar a malloc
	mov r12, rdi; r12 <- rdi
	mov r13, rsi; r13 <- rsi (solo uso esi)
	
	; pido memoria para un nuevo nodo
	mov rdi, tam_nodo
	call malloc

	; guardo los datos correspondientes al nuevo nodo
	mov [rax + nodo_offset_dato], r13d; guardo el dato (4 bytes)
	mov rdi, [r12+lista_offset_primero]
	mov [rax + nodo_offset_prox], rdi

	; apunto la lista al nuevo nodo
	mov [r12+lista_offset_primero], rax

	pop r13
	pop r12
	pop rbp
	ret