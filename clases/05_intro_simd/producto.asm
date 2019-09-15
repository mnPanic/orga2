global productoInternoFloats

section .text
productoInternoFloats:
    ; float productoInternoFloats(float* a, float* b, short n)
    ;  Realiza el producto interno de dos vectores de floats
    ;  Supone n multiplo de 4
    ;   rdi = a
    ;   rsi = b
    ;    dx = n (longitud de ambos vectores)
    
    ; Dados
    ;
    ;  A = [a1, a2, a3, a4, ..., an]
    ;  B = [b1, b2, b3, b4, ..., bn]
    ;
    ; El producto interno es
    ;
    ;  <A, B> = a1 * b2 + ... + an * bn

    ; xmm0 = resultado
    ; xmm0 = valores de A
    ; xmm2 = valores de B

    pxor xmm0, xmm0     ; xmm0 = 0

    .loop:
        ; Levanto de a 4 en xmm1 y xmm2
        movdqu xmm1, [rdi]  ; xmm1 = a1 | a2 | a3 | a4
        movdqu xmm2, [rsi]  ; xmm2 = b1 | b2 | b3 | b4

        ; Los multiplico
        mulps xmm1, xmm2    ; xmm1 = a1*b1 | a2*b2 | a3*b3 | a4*b4

        ; Acumulo el resultado parcial
        addps xmm0, xmm1    ; xmm0 = a1*b1 + a5*b5 + ... | a2*b2 + a6*b6 + ... | ...

        ; Decremento n
        sub dx, 4

        ; Comparo con 0
        cmp dx, 0
        jne .loop

    ; Tengo en xmm0 las sumas parciales
    ;   xmm0 = a1*b1 + ... | a2*b2 + ... | a3*b3 + ... | a4*b4 + ...
    ;        =      r1     |      r2     |      r3     |      r4
    ; Las quiero sumar entre sí

    haddps xmm0, xmm0       ; xmm0 = r1 + r2 | r3 + r4 | r1 + r2 | r3 + r4
    haddps xmm0, xmm0       ; xmm0 = ... | ... | ... | r1 + r2 + r3 + r4
    ; El resultado está en la parte baja de xmm0

    ret