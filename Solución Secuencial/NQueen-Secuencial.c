/*Proyecto Final de Algoritmos
Sebastian Gonzalo Vives Faus - A01025211
Sergio Hernandez Castillo - A01025210
Descripción: Problema de las N Reinas resuelto secuencialmente
*/

#include <omp.h>
#include <stdio.h>
#include <stdbool.h>

//Variables globales
int n = 0; //Tamaño del tablero
int soluciones = 0;
bool imprimir = false;

//Metodo para imprimir
void print(int arr[]){
    printf("Soulcion %d \n", soluciones);
    
    for(int i =0; i<n;i++){
        for(int j = 0; j<n; j++){
            if(arr[i] == j){ //Si el valor en mi hilera es el mismo que en mi columna (Hay una reinas)
                printf("Q ");
            }
            else{ printf("0 ");}
        }
        printf("\n");
    }
}

//Metodo complementario a Reinas
void InsertarReinas(int arr[], int row, int col){
    //Tenemos que comprobar en cada hilera si podemos insertar a una reina
    //Para que cumpla la regla, ninguna reina se puede atacar entre si (siguiendo las reglas del ajedrez), por lo que hay comprobar ataques verticales y diagonales.
    for(int i = 0; i<row; i++){
        //Ataques verticales
        if (arr[i] == col){ //Si la reina se enucentra en la misma columna, nos salimos
        //printf("V Ouch! en la hilera %d",row);
            return;
        }
        //Ataques diagonales (Hay que utilizar la formula de diagonal)
        if((abs(arr[i] - col) == (row-i))){
            //printf("Q Ouch! en la hilera %d",row);
            return;
        }

    }
    //Si ninguna de esos dos ataques se cumplen, podemos asumir que es seguro colocar la reina en esta columna en la hilera actual.
    arr[row] = col;
    
    //Checamos si hay mas hileras o si llegamos a la hilera final
    if(row == n-1){//Si llegamos a la ultima hilera y pusimos una reina, podemos asumir que la tabla es una solucion.
        soluciones++; //Le sumamos 1 a las soluciones
        //Aqui imprimimos la tabla, si el usuario eligio imprimirla
        if(imprimir == true){
            print(arr);
        }
    }
    else{ //Si aun quedan mas hileras, vamos a la siguiente hilera, tratando de encontrar una solucion poniendo una reina en cada columna de la siguiente hilera.
        for(int i = 0; i<n; i++){
            InsertarReinas(arr, row+1, i);
        }
    }
}//Terminar metodo


//Metodo principal
void Reinas(int arr[]){
    for (int i = 0; i<n; i++){
        //Vamos a probar poniendo una reina en cada columna de la primer fila.
        //printf("Buscando solucion en el tablero donde la reina empieza en la hilera 0 y columna %d \n", i);
        InsertarReinas(arr, 0, i); //Donde: arr (Arreglo/tablero), 0 (row 0 en donde vamos a probar acada reina), i (columna en donde ponemos la primer reina.)
        
    }
}//terminar metodo

//Main
int main(int argc, const char* argv[]){
    //Inilizacion al ejecutar el programa ./a.out
    if(argc < 3){
        printf("Error!: Ejecutar como ./a.out <tamaño del tablero> <0/1 para imprimir tablas o no> \n");
        return 0;
    }
    //Asignar el tama;o del tablero
    n = atoi(argv[1]); //Donde argv[1] (string) es el numero que el usuario asigna al ejectuar el programa

    //Si se imprimen las soluciones o no.
    int option = atoi(argv[2]);
    if(option == 1){
        imprimir = true;
    }

    //Declarar arreglo
    int arr[n];
    //Llamar al metodo
    double start = omp_get_wtime();
    Reinas(arr);
    double finish = omp_get_wtime();
    printf("Soluciones con un tablero de %d x %d : %d con un tiempo de ejecucion de: %f \n",n,n,soluciones, finish-start);


}