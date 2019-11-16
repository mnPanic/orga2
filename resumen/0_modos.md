# Modos

Para cambiar de modo **real** a **protegido**,

1. Setear el bit `PE` de CR0

    ```x86asm
    mov eax, cr0    ; Copia del valor de CR0 para setear el bit
    or eax, 1       ; Prender el primer bit
    mov cr0, eax    ; Persistir el valor en CR0
    ```

1. Jump far a la siguiente instrucción

    ```x86asm
    jmp <selector>:<offset>
    ```
