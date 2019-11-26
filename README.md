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

*Primero que nada, hay dos opciones de resolver este problema: Utilizando Backtracking y Recursividad, nosotros elegimos Recursividad ya que el metodo recursivo (mas adelante) puede ser asignado a cada thread durante la paralelizacion. El programa recibe como entrada el tamaño del tablero de ajedrez y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for y dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Esta función recibe como entrada el arreglo con el cuál va a trabajar, la fila, y la columna. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada). Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. El programa seguirá así hasta que haya determinado si ya no hay más hileras. Esta solución mantiene una complejidad O(n) por solo tener un ciclo for en el metodo de "InsertarReinas()" y "Reinas()".*

## 4. Análisis de los inhibidores del paralelismo

*El programa paralelo contiene 4 metodos:
    print (el cual imprime el tablero)
    InsertarReina (funcion recursiva donde tratamos de resolver el tablero con la primer reina ya colocada)
    Reinas (mi loop principal donde inserto una reina por columna en la primer hilera y se la asigno a un thread)
    y el Main()
 El print y el main quedan fuera de la idea de ser paralelizados, ya que el main no se puede paralelizar y no requiero repartir la funcion de imprimir entre varios threads, ya que es opcional y no afecta el rendimiendo del programa a menos que sea activado. Incluso si estuviese activado, en una funcion relativamente sencilla y rapida, no vale la pena paralelizar y no es necesario.
 
 InsertarReina es mi metodo recursivo, el cual no hace sentido paralelizar (a parte de ser muy complicado poder paralelizar recursividad) ya que es el metodo que se le va a asignar a cada thread creado, por lo que nos queda la funcion Reinas().
 
 Esta funcion es perfecta para paralelizar, no solo incluye un for si no que, en el for, puedo asignarle un tablero y el metodo recursivo a cada thread distinto.*

## 5. Solución paralela

*El programa recibe como entrada el tamaño del tablero de ajedrez, el numero de threads en el cual se ejecutaran las partes más importantes del código, y un 0 o 1 para determinar si el usuario desea imprimir las soluciones como una matriz. En base al tamaño dado del tablero, se inicializa un arreglo de ese tamaño. De ahí, el programa llama a la función “Reinas()” donde se va a inicializar un ciclo for cubierto por una pragma que privatiza la variable de “t_Id” (la que guarda el número de cada thread) y incluye un scheduler de tipo static, auto, dynamic, o guided. Los tipos de schedulers se tiene que cambiar manualmente en el código. Dentro de ese ciclo va a llamar a la función “InsertarReinas()”. Pero antes, inicializa un arreglo separado para cada thread. “InsertarReinas()” recibe como entrada el arreglo con el cuál va a trabajar, la fila, la columna, y el respectivo thread. Esencialmente, el ciclo for de “Reinas()” posiciona una reina en cada columna de la primera fila al llamar a “InsertarReinas()”. Dentro de “InsertarReinas()” se tiene que comprobar en cada hilera si se puede insertar una reina. Pero para que cumple con la regla, ninguna reina se podrá atacar entre si (siguiendo las reglas del ajedrez), por lo que hay que verificar ataques verticales y diagonales. En ese momento, se inicializa un ciclo for, donde si la reina se encuentra en la misma columna que otra, se sale. También aplica lo mismo si hay un ataque diagonal. Si ninguno de esos ataques se cumple, el programa puede asumir que es seguro colocar la reina en esa columna en la hilera actual. Al final, el programa revisa si hay más hileras o si llegó a la hilera final. Si el programa llegó a la hilera final y colocó una reina, asume que es una solución y la imprime (si el usuario puso un 1 como entrada) junto con el número de thread en el que se ejecutó. Si aun quedan mas hileras, se mueve a la siguiente, tratando de encontrar una solución posicionando una reina en cada columna de la siguiente hilera. Cuando el thread enucentra una solucion, le asigno una seccion "atomica", donde le da acceso a una parte especifica de la memoria (en esta caso es mi int de soluciones) para que modifique especificamente esa variable (sin locks) si ese thread en especifico encuentra una solucion. Mi funcion de print le asigno una seccion critica, ya que solo quiero que ese thread en especifico imprima la solucion (si es que encuentra alguna). El programa seguirá así hasta que haya determinado si ya no hay más hileras. Esta solución mantiene una complejidad O(n!) al ser recursivo".*

## 6. Tabla de resultados

[Ver Excel en la carpeta de "docs"]

## 7. Gráfica(s) comparativa(s)

[Ver Excel en la carpeta de "docs"]

## 8. Interpretación de los resultados

*Generalmente, paralelizar un programa que resuelve un problema, es mucho más eficiente que dejarlo como secuencial. Pero en este caso, depende mucho de la cantidad de threads siendo utilizadas y el tamaño del tablero de ajedrez. Como se puede ver en las gráficas de tamaño de tablero 6 y 8, paralelizar el programa y incluir cualquier numero de threads, estos siendo 2, 4, 8, 16, y 32, es inecesario. La versión secuencial corre más rápido que el paralelizado, en todos los casos. Dejando el programa como secuencial es la mejor opción, seguramente por el hecho de que los tableros de 6x6 y 8x8 son más pequeños comparados con los otros. Ahora bien, para los casos de los tableros de 10x10 y 12x12, lo mejor sería usar la versión paralelizada. Para el tablero de tamaño 10x10, es mucho mejor usar la versión paralizada con el scheduler de tipo guided, utilizando 16 threads. Esta versión corre y finaliza con 0.0031304 segundos, mientras que la versión secuencial corre y finaliza con 0.008442. Para el tablero de 12x12, la mejor versión es la paralelizada con el scheduler tipo static, también utilizando 16 threads. Esta versión corre y finaliza en 0.0586962 segundos, mientras que la versión secuencial corre y finaliza en 0.234226. Finalmente, el tablero de 14x14, el más grande, obvio es más eficiente siendo paralelizado. Especificamente, la versión paralelizada con el scheduler tipo guided, utilizando 32 threads es el mejor. Es el que corre y finaliza en menor tiempo, 1.928452 segundos. La versión secuencial corre y finaliza en 9.1787602 segundos, casi 10 veces más. Para concluir, la cuestión de cuál versión es mejor para utilizar depende enteramente del tamaño del tablero, el tipo de scheduler, y la cantidad de threads utilizadas. Mientras más grande sea el tablero, mejor es utilizar una versión paralela.*

## 9. Guía paso a paso

*Para cambiar de tipo de scheduler en la versión paralela, simplemente hay que cambiar en la linea 89 la palabra "guided" por "static", "dynamic", o "auto". Para compilar el secuencial, escriba "gcc -fopenmp NQueen-Secuencial.c -o NQueen-Secuencial" en la terminal, dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Secuencial <tamaño del tablero (6, 8, 10, 12, 14)> <0 u 1 si desea imprimir los resultados como matrices>". Para compilar el paralelo, escriba "gcc -fopenmp NQueen-Paralelo.c -o NQueen-Paralelo" en la terminal, dentro del folder en el cual está guardado el archivo. Para correrlo, escriba "./NQueen-Paralelo <tamaño del tablero> <número de threads> <0 u 1 si desea imprimir los resultados como matrices>".*

## 10. Referencias

*Mattson, Tim & Meadows, Larry. (na). A "Hands-On" Introduction to OpenMP* [PDF file]. Retrived from https://www.openmp.org/wp-content/uploads/omp-hands-on-SC08.pdf

(n.d.). Retrieved November 24, 2019, from https://www.ibm.com/support/knowledgecenter/SSGH2K_12.1.0/com.ibm.xlc121.aix.doc/compiler_ref/ruomprun1.html.(n.d.). 

Retrieved November 24, 2019, from http://jakascorner.com/blog/2016/06/omp-for-scheduling.html.(n.d.). 

Retrieved November 24, 2019, from https://www.youtube.com/watch?v=wGbuCyNpxIg.Admin. (2019, October 1). OpenMP* Loop Scheduling. 

Retrieved November 25, 2019, from https://software.intel.com/en-us/articles/openmp-loop-scheduling.AmirAmir 39711 gold badge33 silver badges1010 bronze badges, GillesGilles 7, & Hristo IlievHristo Iliev 58.4k99 gold badges9797 silver badges145145 bronze badges. (1966, January 1). difference between omp critical and omp single. 

Retrieved November 24, 2019, from https://stackoverflow.com/questions/33441767/difference-between-omp-critical-and-omp-single.Esraa, E. E. E. (1966, February 1). Optimizing N-queen with openmp c. 

Retrieved November 24, 2019, from https://stackoverflow.com/questions/34141909/optimizing-n-queen-with-openmp-c.N Queen Problem: Backtracking-3. (2019, October 16). 

Retrieved November 24, 2019, from https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/.Printing all solutions in N-Queen Problem. (2019, July 19). 

Retrieved November 24, 2019, from https://www.geeksforgeeks.org/printing-solutions-n-queen-problem/.Victoraldecoa. (n.d.). victoraldecoa/N-Queens-Solver_OpenMP_Example. 

Retrieved November 24, 2019, from https://github.com/victoraldecoa/N-Queens-Solver_OpenMP_Example/blob/master/src/nqueens-openmp.c.*
