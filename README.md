# *Problema de las N Reinas*
---
#### Materia: *Análisis y Diseño de Algoritmos (TC2017)*

#### Semestre: *Otoño 2019*

##### Campus: *Santa Fe*

##### Integrantes:
1. *Sebastian Gonzalo Vives Faus* *A01025211*
2. *Sergio Hernandez Castillo* *A01025210*

---
## 1. Aspectos generales

### 1.1 Requerimientos

A continuación se mencionan los requerimientos mínimos del proyecto, favor de tenerlos presente para que cumpla con todos.

* El equipo tiene la libertad de elegir el problema a resolver.
* El proyecto deberá utilizar [OpenMP](https://www.openmp.org/) para la implementación del código paralelo.
* Todo el código y la documentación del proyecto debe alojarse en este repositorio de GitHub. Favor de mantener la estructura de carpetas propuesta.

### 1.2 Estructura del repositorio
El proyecto debe seguir la siguiente estructura de carpetas:
```
- / 			        # Raíz de todo el proyecto
    - README.md			# este archivo
    - secuencial		# Carpeta con la solución secuencial
    - paralelo			# Carpeta con la solución paralela
    - docs              # Carpeta con los documentos, tablas, gráficas, imágenes
```

### 1.3 Documentación  del proyecto

Como parte de la entrega final del proyecto, se debe incluir la siguiente información:

* Descripción del problema a resolver.
* Descripción de la solución secuencial con referencia (enlace) al código secuencial alojado en la carpeta [secuencial](secuencial/).
* Análisis de los inhibidores de paralelismo presente y una explicación de cómo se solucionaron.
* Descripción de la solución paralela con referencia (enlace) al código paralelo alojado en la carpeta [paralelo](paralelo/).
* Tabla de resultados con los tiempos de ejecución medidos para cada variante de la solución secuencial vs. la solución paralela, teniendo en cuenta: 5 tamaños diferentes de las entradas, 5 opciones diferentes de números de CPU (threads), 4 ocpiones diferentes de balanceo (*auto, guided, static, dynamic*).
* Gráfica(s) comparativa(s) de los resultados obtenidos en las mediciones.
* Interpretación de los resultados obtenidos.
* Guía paso a paso para la ejecución del código y replicar los resultados obtenidos.
* El código debe estar documentado siguiendo los estándares definidos para el lenguaje de programación seleccionado.

## 2. Descripción del problema

*El problema de las N Reinas consiste en posicionar una cantidad de Reinas en un tablero de ajedrez de tal forma de que no se pueden atacar. Es decir, ninguna reina podra hacer toparse con otra al moverse horizontal/verticalmente, siguiendo las reglas del ajedrez. La cantidad de reinas depende del tamaño del tablero.*

## 3. Solución secuencial

*El programa recibe como entrada el tamaño del tablero de ajedrez y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for y dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Esta función recibe como entrada el arreglo con el cuál va a trabajar, la fila, y la columna. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada). Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. El programa seguirá así hasta que haya determinado si ya no hay más hileras. Esta solución mantiene una complejidad O(n) por solo tener un ciclo for en el metodo de "InsertarReinas()" y "Reinas()".*

## 4. Análisis de los inhibidores del paralelismo

*[Incluya aquí el análisis de los inhibidores presentes en su problema, así como la solución a los mismos.]*

## 5. Solución paralela

*El programa recibe como entrada el tamaño del tablero de ajedrez, el numero de threads en el cual se ejecutaran las partes más importantes del código, y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for cubierto por una pragma que privatiza la variable de “t_Id” (la que guarda el número de cada thread) y incluye un scheduler de tipo static, auto, dynamic, o guided. Los tipos de schedulers se tiene que cambiar manualmente en el código. Dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Pero antes, inicializa un arreglo separado para cada thread. “InsertarReinas()” recibe como entrada el arreglo con el cuál va a trabajar, la fila, la columna, y el respectivo thread. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada) junto con el número de thread en el que se ejecutó. Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. El programa seguirá así hasta que haya determinado si ya no hay más hileras. Esta solución mantiene una complejidad O(n) por solo tener un ciclo for en el metodo de "InsertarReinas()" y "Reinas()".*

## 6. Tabla de resultados

[Ver Excel en la carpeta de "docs"]

## 7. Gráfica(s) comparativa(s)

[Ver Excel en la carpeta de "docs"]

## 8. Interpretación de los resultados

*Generalmente, paralelizar un programa que resuelve un problema, es mucho más eficiente que dejarlo como secuencial. Pero en este caso, depende mucho de la cantidad de threads siendo utilizadas y el tamaño del tablero de ajedrez. Como se puede ver en las gráficas de tamaño de tablero 6 y 8, paralelizar el programa y incluir cualquier numero de threads, estos siendo 2, 4, 8, 16, y 32, es inecesario. La versión secuencial corre más rápido que el paralelizado, en todos los casos. Dejando el programa como secuencial es la mejor opción, seguramente por el hecho de que los tableros de 6x6 y 8x8 son más pequeños comparados con los otros. Ahora bien, para los casos de los tableros de 10x10 y 12x12, lo mejor sería usar la versión paralelizada. Para el tablero de tamaño 10x10, es mucho mejor usar la versión paralizada con el scheduler de tipo guided, utilizando 16 threads. Esta versión corre y finaliza con 0.0031304 segundos, mientras que la versión secuencial corre y finalize con 0.008442. Para el tablero de 12x12, la mejor versión es la paralelizada con el scheduler tipo static, también utilizando 16 threads. Esta versión corre y finaliza en 0.0586962 segundos, mientras que la versión secuencial corre y finaliza en 0.234226. Finalmente, el tablero de 14x14, el más grande, obvio es más eficiente siendo paralelizado. Especificamente, la versión paralelizada con el scheduler tipo guided, utilizando 32 threads es el mejor. Es el que correy finalize en menor tiempo, 1.928452 segundos. La versión secuencial corre y finaliza en 9.1787602 segundos, casi 10 veces más. Para concluir, la cuestión de cuál versión es mejor para utilizar depende enteramente del tamaño del tablero, el tipo de scheduler, y la cantidad de threads utilizados. Mientras más grande sea el tablero, mejor es utilizar una versión paralela a este problema.*

## 9. Guía paso a paso

*Para cambiar de tipo de scheduler en la versión paralela, simplemente hay que cambiar en la linea 89 la palabra "guided" por "static", "dynamic", o "auto". Para compilar el secuencial, escriba "gcc -fopenmp NQueen-Secuencial.c -o NQueen-Secuencial" en la terminal, dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Secuencial <tamaño del tablero (6, 8, 10, 12, 14)> <0 u 1 si desea imprimir los resultados como matrices>". Para compilar el paralelo, escriba "gcc -fopenmp NQueen-Paralelo.c -o NQueen-Paralelo" en la terminal, dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Paralelo <tamaño del tablero> <número de threads> <0 u 1 si desea imprimir los resultados como matrices>".*

## 10. Referencias

*[Incluya aquí las referencias a sitios de interés y cualquier otra información que haya utilizado para realizar el proyecto y que le puedan ser de utilidad a otras personas que quieran usarlo como referencia]*
