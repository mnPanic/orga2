global sumar

section .rodata
    THRSS: times 8 dw 0x03

section .text
sumar:
    ; sumar(short* p, int len)
    ;   Modifica el arreglo de shorts sumandole 3 a los valores negativos.
    ;   Asume len mult de 8

    ; rdi = p    (short*)
    ; esi = len  (int)
    
    ; Tengo una mascara con los ocho 3s
    ; Cargo la mascara en xmm0
    movdqu xmm0, [THRSS]  ; xmm0 = 3s mask

    ; esi = [p1, p2, p3, p4, ..., pn]
    ; Cada short es 16 bits = 2 bytes = 1 word
    .loop:
        ; Cargo los 8 shorts
        movdqu xmm1, [rdi + rsi]    ; xmm1 = p1 | p2 | ... | p8

        pxor xmm2, xmm2             ; xmm2 = 0

        pcmpgtw xmm2, xmm1          ; si xmm2[i] > xmm1[i] => xmm2[i] = 1
                                    ; 0 > xmm1[i]
        
        ; Tengo en 1 las words de xmm2 que tienen valores negativos 
        ; Lo paso por un and con la máscara para solo sumar a esos
        pand xmm2, xmm0             ; xmm2[i] &= xmm0[i]

        ; Sumo a xmm1 los 3s donde corresponda
        paddsw xmm1, xmm2           ; xmm1[i] += xmm2[i]
                                    ; xmm1[i] += 3 si xmm1[i] es negativo
        
        ; Escribo devuelta en memoria
        movdqu [rdi + rsi], xmm1

        ; Decremento el size en 8
        sub rsi, 8

        cmp rsi, 0
        jne .loop
    
    ; Ya esta modificado el vector
    ret
    

    

