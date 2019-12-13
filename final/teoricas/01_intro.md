# Arquitectura de Computadores

## Arquitectura

Es el conjunto de recursos accesibles para el programador.
Por lo general se mantiene a través de los modelos de procesadores de esa
arquitectura (y de esta forma, se mantiene compatibilidad hacia los modelos
anteriores)

- Registros
- Set de instrucciones
- Estructuras de memoria (descriptores de segmento y página, etc.)

## Microarquitectura

Implementación en el silicio de la arquitectura. Puede cambiar de un modelo a
otro de la misma familia.

## ISA

El *Instruction Set Architecture* (ISA) es el set de instrucciones visibles por
el programador. Es la interfaz entre el software y el hardware.

Se diferencian entre sí según varios criterios:

- **Clases**: Con GPR vs registros dedicados, con registro-memoria vs load-store
- **Direccionamiento de memoria**: Alineación obligatoria de datos vs
  administración de a bytes.
- **Modos de direccionamiento**: Como son especificados los operandos
- **Tipos y tamaños de operandos**
- **Operaciones**: RISC (Reduced) vs CISC (Compex)
- **Control flow**: jmps condicionales, calls.
- **Longitud de código**: Instrucciones de tamaño fijo vs variable.

## Organización

Es los detalles de la implementación de la ISA.

- Organización e interconexión de la memoria.
- Diseño de los diferentes bloques de la CPU y para implementar el set
  de instrucciones.
- Implementación de paralelismo a nivel de instrucciones y/o de datos.

Puede haber procesadores con la misma ISA pero organiación diferente.