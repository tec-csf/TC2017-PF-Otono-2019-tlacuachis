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

*El programa recibe como entrada el tamaño del tablero de ajedrez y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for y dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Esta función recibe como entrada el arreglo con el cuál va a trabajar, la fila, y la columna. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada). Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. El programa seguirá así hasta que haya determinado si ya no hay más hileras.*

## 4. Análisis de los inhibidores del paralelismo

*[Incluya aquí el análisis de los inhibidores presentes en su problema, así como la solución a los mismos.]*

## 5. Solución paralela

*El programa recibe como entrada el tamaño del tablero de ajedrez, el numero de threads en el cual se ejecutaran las partes más importantes del código, y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for cubierto por una pragma que privatiza la variable de “t_Id” (la que guarda el número de cada thread) y incluye un scheduler de tipo static, auto, dynamic, o guided. Los tipos de schedulers se tiene que cambiar manualmente en el código. Dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Pero antes, inicializa un arreglo separado para cada thread. “InsertarReinas()” recibe como entrada el arreglo con el cuál va a trabajar, la fila, la columna, y el respectivo thread. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada) junto con el número de thread en el que se ejecutó. Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. El programa seguirá así hasta que haya determinado si ya no hay más hileras.*

## 6. Tabla de resultados

[Ver Excel en la carpeta de "docs"]

## 7. Gráfica(s) comparativa(s)

[Ver Excel en la carpeta de "docs"]

## 8. Interpretación de los resultados

*[Incluya aquí la interpretación de los resultados.]*

## 9. Guía paso a paso

*Para compilar el secuencial, escriba "gcc -fopenmp NQueen-Secuencial.c -o NQueen-Secuencial" en la terminal y dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Secuencial <tamaño del tablero> <0 u 1 si desea imprimir los resultados como matrices>". Para compilar el paralelo, escriba "gcc -fopenmp NQueen-Paralelo.c -o NQueen-Paralelo" en la terminal y dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Paralelo <tamaño del tablero> <número de threads> <0 u 1 si desea imprimir los resultados como matrices>".*

## 10. Referencias

*[Incluya aquí las referencias a sitios de interés y cualquier otra información que haya utilizado para realizar el proyecto y que le puedan ser de utilidad a otras personas que quieran usarlo como referencia]*
