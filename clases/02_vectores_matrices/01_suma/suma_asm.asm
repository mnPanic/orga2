global suma_asm
section .rodata:
    ls16b EQU 0x0000000000001111    ; least significant 16 bits
    short_size EQU 2                ; tamaño de un short en bytes


section .text:
    suma_asm: 
        ; int suma_asm(short* v, short n)
        ; res = rax
        ; v = di
        ; n = si

        ; limpio los primeros 48 bits mas significativos de rdi y rsi
        ; ya que puede ntener basura, pasándolos por una máscara.
        and rdi, ls16b
        and rsi, ls16b
        xor rax, rax    ; limpio rax

    .loop:
        test rsi,rsi         ; si `si` es 0, termine
        je .fin

        add rax, [rdi + short_size * rsi]

        dec rsi
        jmp .loop
    .fin:   
        ret