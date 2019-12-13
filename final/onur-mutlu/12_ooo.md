# Lecture 12 - Out Of Order Execution

Posibilitar Out Of Order Execution (OOO)

1. Linkear el consumidor de un valor al productor
    - **Register Renaming** (con RAT; Register Alias Table) asociar un *tag* a
      cada valor.
2. Bufferear las instrucciones hasta que estén listas
    - Insertándolas en una **reservation station** después del renaming
3. Trackear el readiness de los valores fuente de una instrucción
    - Se hace **broadcast** del tag cuando el valor es producido
    - Las instrucciones comparan los **source tags** con los broadcasteados,
      - Si hay match, el source value se vuelve ready
4. Cuando estén ready todos los source values de una instrucción, dispatch a la
   function unit (FU)
    - **Wakeup y select/schedule** a la instrucción.
