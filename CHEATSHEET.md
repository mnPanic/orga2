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

Convención C
============

_(en 64 bits)_

- Preservar los registros RBX, R12, R13, R14, R15 y RBP.
- Retornar el resultado a través de RAX si un valor entero (y RDX si ocupa 
  128bits) o XMM0, si es un número de punto flotante.
- Preservar la consistencia de la pila.
- La pila opera alineada a 8 bytes. Pero antes de llamar a funciones de C debe
  estarlo a 16 bytes.

Pasaje de parámetros
--------------------

_En 32 bits_
- Los parámetros se pasan a través de la pila desde la dirección más baja a la 
  más alta.
- Son apilados de derecha a izquierda según aparecen en la firma de la función.
- Para valores de 64bits se apilan en little-endian.

_En 64 bits_
Los parámetros se pasan por registro, de izquierda a derecha según la firma de 
la función, clasificados por tipo:

- Enteros y direcciónes de memoria: RDI, RSI, RDX, RCX, R8 y R9
- Punto flotante: XMM0 a XMM7
- Resto de los parámetros que superen la cantidad de registros se ubican en la 
  pila como en 32 bits.


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

SIMD
====

Empaquetamiento
---------------

Un registro xmm tiene 128 bits, 16 bytes, y entran

    n   Byes        bits        size    type
    16  1 byte      8 bits      byte    char
    8   2 bytes     16 bits     word    short
    4   4 bytes     32 bits     dword   int / float
    2   8 bytes     64 bits     qword   double
    1   16 bytes    128 bits    dqword
