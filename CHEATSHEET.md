Registros
=========

```text
8 bits:     AL  BL  CL  DL  DIL SIL BPL SPL R8B ... R15B
16 bits:    AX  BX  CX  DX  DI  SI  BP  SP  R8W ... R15W
32 bits:    EAX EBX ECX EDX EDI ESI EBP ESP R8D ... R15D
64 bits:    RAX RBX RCX RDX RSI RDI RBP RSP R8  ... R15
128 bits:   XMM0,                               ... XMM15
```

Direccionamiento
================

```text
[Base + (Index * Scale) + Displacement]
 RAX      RAX      1      Cte. 32 bits
 ...      ...      2
 R15      R15      4
                   8
```

Secciones
=========

Dividen a un programa de assembler:

- `.data`: Donde declarar variables globales inicializadas.
(DB, DW, DD y DQ).

- `.rodata`: Donde declarar constantes globales inicializadas.
(DB, DW, DD y DQ).

- `.bss`: Donde declarar variables globales no inicializadas.
(RESB, RESW, RESD y RESQ).

- `.text`: Es donde se escribe el código.

Etiquetas y símbolos
--------------------

- `_start`: Punto de entrada del programa
- `global`: Define que un simbolo puede ser visto globalmente

Directivas de ensamblador
=========================

- Defines:
  - `DB`: _Define Byte_
  - `DW`: _Define Word_ (16b)
  - `DD`: _Define Double word_ (32b)
  - `DQ`: _Define Quadruple word_ (64b)
  - `RESB`, `RESW`, `RESD` y `RESQ`.
- `$`: se evalúa en la posición en memoria al principio de la línea que contiene
  la expresión.
- `EQU`: Definir constantes que no quedan en el archivo objeto
- `TIMES`: Prefijo para repetir una cantidad de veces la instrucción

Syscalls
========

Se usa la _int 0x80_

Interfaz
--------

1. El número de función que queremos en `rax`
2. Los parámetros en `rbx`, `rcx`, `rdx`, `rsi`, `rdi` y `rbp`; en ese orden
3. Llamamos a la interrupción del sistema operativo (`int 0x80`)
4. En general, la respuesta está en `rax`

Calls
-----

- Mostrar por pantalla (**sys_write**)
  Función 4
  Param 1: **¿donde?** (1 = stdout)
  Param 2: **Dirección de memoria del mensaje**
  Param 3: **Longitud del mensaje** (en bytes)
- Terminar el programa (**exit**)
  Función 1
  Parámetro 1: **Código de retorno** (0 = sin error)

Ejecutar
========

- Ensamblar

  ```bash
  nasm -f elf64 holamundo.asm
  ```

- Linkear

  ```bash
  ld -o holamundo holamundo.o
  ```
