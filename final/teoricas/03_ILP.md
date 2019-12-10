# ILP (Instruction Level Paralelism)

Von Neumann define un modelo básico de CPU basado en una máquina de ejecución
con ciclos

![Ciclos de ejecución](img/ILP/cycle.png)

En los primeros procesadores cada etapa se ejecutaba en un ciclo de clock, y la
CPU entera estaba dedicada a esa tarea. Por esto ejecutar una sola instrucción
insumía varios ciclos de clock.

## Pipeline

La primera solución a este problema fue el **pipeline**, que permite superponer
en el tiempo, así posibilitando ejecutar varias instrucciones a la vez.
Así nace el concepto de *Instruction Level Paralelism (ILP)*.

- Requiere que los bloques del procesador que resuelvan la máquina de estados
  para la ejecución de una instrucción (fetch, decode, execute, etc.) puedan
  operar en forma simultánea.

- Es logrado si cada bloque funcional trabaja en paralelo pero cada uno con una
  instrucción diferente.

Parecido al concepto de *linea de montaje*. A cada parte se la denomina etapa o
*stage*.

![Pipeline ideal](img/ILP/pipeline/ideal.png)

- El pipeline tarda en llegar a esa condición final tantos ciclos de clock
  como etapas tenga.

- En un pipeline de 5 etapas, y si cada etapa insume solo un ciclo de clock,
  un resultado de instrucción es provisto por cada ciclo de clock, a partir del
  ciclo en el cual se llega a resolver la primera.

- Este escenario es teórico y en la práctica no se cumple todo el tiempo.

### Eficiencia

Hacer que haya mayor cantidad de etapas más simples entonces mejoraría la
performance, idealmente que lleven un solo clock.

Para un tiempo de ejecución por instrucción para una arquitectura sin pipeline,
en principio mientras mas etapas se definan para ejecutar esa operación, al
paralelizarlas con un pipeline el tiempo de ejecución de la instrucción se
reducirá proporcionalmente con la cantidad de etapas

    TPI = (Tiempo x instrucción en la CPU sin pipeline) / (# etapas)

Donde TPI es *Time Per Instruction*

Esta es una situación teórica ideal, en la práctica suele haber *overheads*
introducidos por el pipeline mismo que suman pequeñas demoras.

El pipeline entonces no reduce el tiempo de ejecución de cada instrucción
individual, sino que al aplicarse en paralelo a un flujo de instrucciones,
incrementa la cantidad completada por unidad de tiempo. De esa forma mejora
notablemente el **throughput** del procesador, y los programas ejecutan
notablemente más rápido.

### Obstáculos

Hay obstáculos que conspiran contra la eficiencia de un pipeline, y que terminan
causando un efecto denominado **pipeline stall**, que degrada la performance
del procesador.

#### Obstáculos Estructurales

Por ejemplo, una etapa no está suficientemente atomizada, y requiere más de
un ciclo de clock para completarse.
De haber dos instrucciones que la utilizan que estén más proximas en el tiempo
que lo que tarde en finalizarse, caerán en conflicto de recursos para su
ejecución. Causando que no puedan pasar por esa etapa del pipeline en un solo
ciclo de clock, sino más.

Una de las instrucciones debe detenerse. Como consecuencia, el CPI se incrementa
en 1 o más respecto del valor ideal.

##### Memoria

Un procesador tiene solo una etapa para acceder a memoria y la comparte para
acceso a datos e instrucciones.

Si se necesita un operando de memoria, el acceso para traerlo interfiere con
la búsqueda del operando de una instrucción más adelante del programa, y
también con el fetch de la siguiente instrucción

Por ejemplo, saliendo del siguiente escenario donde las etapas que hacen uso
de memoria están marcadas en rojo,

![Ideal](img/ILP/pipeline/ideal.png)

Cómo no se pueden realizar a la vez dos etapas que hagan uso de memoria,
entonces las que corresponden a instrucciones posteriores se quedan esperando,
y así se aumenta la cantidad de ciclos de clock que lleva.

![Final](img/ILP/pipeline/real.png)

##### Estructurales - solución

Para todas es necesario agregar hardware.

Para accesos a memoria,

- Separar el cache L1 en datos e instrucciones.
- Emplear buffers de instrucciones impelementados como colas FIFO.
- Ensanchar los buses mas que la word del procesador.

#### Obstáculos de Datos

Se producen cuando por efecto del pipeline, una instrucción requiere de un dato
antes de que esté disponible.

    dadd r1, r2, r3
    dsub r4, r1, r5
    and  r6, r1, r7
    or   r8, r1, r9
    xor  r10, r1, r11

Hay dependencias para el registro `r1`. hasta que la instrucción `add` no
complete su operación, `r1` no tendrá un valor válido, por lo tanto no puede
continuar aplicándolo en las restantes que lo usan.

![Obstaculo de datos](img/ILP/pipeline/data-obs.png)
![Obstaculo de datos resultado](img/ILP/pipeline/data-obs-result.png)

##### Forwarding

Se extrae el resultado directo de la unidad de ejecución (ALU, FPU, etc.) según
la instrucción ni bien está disponible y se lo envía a la entrada de la etapa
que lo requiera en el mismo ciclo de clock que se escribe en el operando dst.

Esto permite ahorrar el tiempo de escritura del dato destino, y se aplica solo
a las etapas posteriores que quedarían en estado stall. A las etapas que no
quedarían en estado stall como consecuencia de una dependencia de datos, se les
enviaría la salida del resultado normalmente, cuando sea aplicado al operando
destino.

A esto se lo llama **forwarding**

![Pipeline forwarding](img/ILP/pipeline/forwarding.png)

Esto no siempre es factible, por ejemplo

    ld   r1, 0(r2)
    dsub r4, r1, r5
    and  r6, r1, r7
    or   r8, r1, r9
    xor  r10, r1, r11

### Obstáculos de Control

Estos son los **branches**, que son la peor situación en cuanto a pérdida de
performance, ya que representan una discontinuidad en el flujo de ejecución, y
el pipeline busca ejecutar instrucciones en secuencia.

Causa que todo lo que estaba pre procesado deba descartarse, debiendo
transcurrir n - 1 ciclos de clock hasta el proximo resultado, donde n es la
cantidad de etapas del pipeline.
Este fenómeno es conocido como **branch penalty**

#### Branches

El principal inconveniente es cuando es un salto condicional, ya que hay que
determinar si la condición es `true` o `false`.

Si es `true`, se habla de **branch taken** (cambia el registro PC a la dirección
del salto) y sino de **branch untaken** (el PC apunta a la instrucción
siguiente)

Como determinar si es taken?

- En la fase de ejecución si es condicional
- En la fase de busqueda de operando si es un jmp (salto incondicional) o un
  call con direccionamiento indirecto (la dirección de salto está en memoria).
- En la fase de decodificación si es un jmp o call con direccionamiento
  directo (la dir de salto viene a continuación del opcode)

Soluciones posibles

- **Forwarding**: Puede ayudar a disminuir el efecto, pero no es óptima ya que solo
  se disminuyen algunos ciclos del **branch penalty**, y no se elimina del todo
  su efecto.

- Para soluciones más eficientes es necesario recurrir a análisis más detallados
  y minuciosos, que suelen tener en cuenta el comportamiento de los algoritmos
  y los saltos.

## Unidad de Predicción de Saltos

Viene a solucionar el **branch penalty**.

A medida que aumenta la complejidad de un procesador, aumentan las etapas del
pipeline, para así poder paralelizar la mayor cantidad de tareas posibles.
Esto hace que la cantidad de tiempo que pasa en stall luego de un branch penalty
sea directamente proporcional a su cantidad de etapas.

### Criterios

- **predicted-non-taken**

  El procesador asume por defecto que el salto nunca se toma, continúa la
  búsqueda del opcode de las instrucciones siguientes como si el salto fuese una
  instrucción común.
  
  Funciona bien cuando el salto es *hacia adelante*,
  
      instrucción branch
      instrucción sucesora secuencial
      instrucción destino para branch taken

- **predicted-taken**

  El procesador asume por defecto que el salto se toma siempre, continúa la
  búsqueda del código de operación a partir de la dirección target.
  
  Funciona adecuadamente en estructuras de iteración
  
      instrucción de destino para branch taken
      grupo de instrucciones a ejecutar iterativamente
      instrucción branch
  
  La gran ventaja es que siempre se acierta, solo falla cuando expira la
  condición de lazo.

- **delayed-branch**

  Suponiendo la siguiente estructura de programa

      instrucción branch
      instrucción sucesora secuencial
      instrucción destino para branch taken

  La instrucción sucesora se envía al slot de salto demorado, y se ejecuta
  si o si independientemente del resultado de la evaluación del branch, y se
  aplica o no su resultado dependiendo de la evaluación de la condición.

  Si es non-taken, no genera ninguna demora, y si es taken, se descarta la
  ejecución y se tiene un ciclo de clock para que salga el resultado de la
  instrucción de destino.

La decisión de que criterio tomar depende del criterio adoptado en el diseño
del set de instrucciones. El compilador, conociendo el criterio asumido por el
procesador, debe organizar el código de la manera adecuada para aprovecharlo.

### Predicción dinámica

Estos modelos dependen del compilador. El hardware interno del procesador no
realiza ningún análisis de código. Si lo hiciera, y tomase decisiones en
función de lo que encuentra, está un paso adelante en cuanto a predicción de
saltos. Esto es llamado **predicción dinámica**.

#### Branch Prediction Buffer

Modelos:

- Predicción simple de 1 bit

  Es una tabla indexada por la posición de memoria de la instrucción de salto
  y un bit que indica el resultado reciente del salto (**taken** o **non-taken**)

  ![Branch Prediction Buffer](img/ILP/branch-prediction/buffer-1b.png)

  Este bit es una pista para la unidad de ejecución.
  Si el resultado del salto coincide con el valor almacenado, se mantiene,
  y sino se complementa a 1 (i.e se invierte).

  La limitación que tiene es que cuando un salto siempre resulta **taken**,
  y falla una vez, produce dos predicciones fallidas seguidas, ya que el bit
  se invierte.

- Predicción de 2 bits

  Sigue un diagrama de estados como el siguiente

  ![Predicción de 2 bits](img/ILP/branch-prediction/2b-prediction.png)

Implementaciones en la práctica:

- En la etapa de Instruction Fetch del pipeline, como un pequeño cache de
  direcciones de salto accesible mediante las direcciones de las instrucciones.

- Otra forma es agregar el par de bits a cada bloque de líneas en el cache de
  instrucciones, que se usan solo si ese bloque tiene instrucciones de salto
  condicional.

##### Benchmarks

Benchmarks de branch prediction

![Benchmarks](img/ILP/branch-prediction/benchmarks.png)

Conclusiones:

- Tiene una eficicencia > 82% para diferentes tipos de programas
- Es superior en programas de punto flotante (< 4%) y menor en programas de
  cálculo entero (< 18%)
- El tamaño del buffer de predicción no genera efecto después de los 4KB
- Tampoco se obtienen mejoras aumentando la cantidad de bits de predicción
  más allá de 2. En general, un branch predictor de n bits toma valores entre
  0 y 2^n - 1, tomando el salto para los valores de la mitad más significativa,
  y no para la menos. La complejidad en el diseño no se ve compensada por la
  mejora en la funcionalidad.

### Branch Target Buffer

Caché de instrucciones de salto que contiene para cada entrada el par (dirección
de la instrucción de salto, dirección target resuelta) y **no** tiene los bits
**taken** o **non-taken**.

![Branch Target Buffer](img/ILP/branch-prediction/branch-target-buffer.png)

A este se accede con el valor completo del PC.

- Si el valor no se encuentra, se asume **taken**
  - Si el resultado es **non-taken**, se acepta el stall, y no se almacena nada
    en el BTB.
  - Si el resultado es **taken**, se ingresa el valor al BTB.
- Si el valor se encuentra en el BTB, se aplica el target almacenado
  - Si es **non-taken**, guarda el nuevo valor en el BTB luego de la penalidad
    correspondiente en el pipeline.
  - Si es **taken** no hay penalidad, y no se guarda ningún nuevo valor.

## Superscalar

Se puede trabajar a nivel de microarquitectura y hardware para aumentar la
paralelización, ejecutando más de una instrucción por ciclo de clock.

Se hacen superscalars de n vías,

![Superscalar de 2 vías](img/ILP/superscalar/2-vias.png)

Aumentan los obstáculos:

- Los obstáculos estructurales quedan más expuestos
- El acceso simultáneo a memoria puede ocurrir entre etapas de distintos
  pipelines, y la probabilidad de ocurrencia aumenta con la cantidad de vías
  del superscalar.
- Se pueden ejecutar en dos ALUs dos instrucciones, pero si una depende de la
  otra entonces no es posible.
- Una falla en el branch prediction es letal. Limpia ambos pipelines.

## Scheduling dinámico

Contexto actual:

- Hasta aquí fueron todos pipelines con scheduling de instrucciones estático,
  simplemente buscan una instrucción, y la envían a la unidad de ejecución
  (proceso conocido como **dispatch**)
- En el caso de tener dependencias con otra instrucción, el envío es demorado
  (**pipeline stall**)
- Y en el caso de superscalars se deben considerar dependencias entre vías.

Todo esto hace que se vuelva insuficiente el método de forwarding que soluciona
los **obstáculos de datos**.

La solución a esto es la ejecución fuera de orden.

## Ejecución fuera de orden

WIP

## Procesadores multithread

## Multicore y manycore
