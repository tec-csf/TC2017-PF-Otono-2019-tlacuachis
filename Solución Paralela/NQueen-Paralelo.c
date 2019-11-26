/*Proyecto Final de Algoritmos
Sebastian Gonzalo Vives Faus - A01025211
Sergio Hernandez Castillo - A01025210
Descripción: Problema de las N Reinas resuelto paralelizado
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
            }//Close if 

            else{
                printf("0 ");
            }//Close else 
        }//Close for 

        printf("\n");
    }//Close for 
}//Close print()

//Metodo complementario a Reinas
void InsertarReinas(int arr[], int row, int col, int t_id){
    /*Tenemos que comprobar en cada hilera si podemos insertar a una reina.
    Para que cumpla la regla, ninguna reina se puede atacar entre si (siguiendo las reglas del ajedrez), 
    por lo que hay comprobar ataques verticales y diagonales.*/
    for(int i = 0; i < row; i++){
        //Ataques verticales
        if (arr[i] == col){ //Si la reina se encuentra en la misma columna, nos salimos
            //printf("V Ouch! en la hilera %d",row);
            return;
        }//Close if     

        //Ataques diagonales (Hay que utilizar la formula de diagonal)
        if((abs(arr[i] - col) == (row-i))){
            //printf("Q Ouch! en la hilera %d",row);
            return;
        }//Close if
    }//Close for 

    /*Si ninguna de esos dos ataques se cumplen, podemos asumir que es seguro colocar la reina en esta 
    columna en la hilera actual.*/
    arr[row] = col;
    
    //Checamos si hay mas hileras o si llegamos a la hilera final
    if(row == n-1){//Si llegamos a la ultima hilera y pusimos una reina, podemos asumir que la tabla es una solucion.
        #pragma omp atomic
        soluciones++; //Le sumamos 1 a las soluciones
        //Aqui imprimimos la tabla, si el usuario eligio imprimirla
        if(imprimir == true){
            #pragma omp critical 
            { 
                /*Si el usuario decide imprimir las soluciones, imprimira la solucion encontrada, la igual que el 
                thread que la encontro.*/
                printf("Thread %d encontro una solucion! \n",t_id);
                print(arr); 
            }//Close pragma
        }//Close if
    }//Close if 
    
    /*Si aun quedan mas hileras, vamos a la siguiente hilera, tratando de encontrar una solucion poniendo una 
    reina en cada columna de la siguiente hilera.*/
    else{ 
        for(int i = 0; i<n; i++){
            InsertarReinas(arr, row+1, i,t_id);
        }//Clos for
    }//Close else 
}//Close InsertarReinas()

//Metodo principal
void Reinas(){
    int t_id; //Variable para obtener el ID de cada thread
    int i;

    //AQUI MODIFICAMOS EL TIPO DE SCHEDULE, Aqui es donde implementamos nuestro parallel for.
    #pragma omp parallel for schedule(guided,1) private(t_id) 
    for (i = 0; i<n; i++){
        t_id = omp_get_thread_num(); //Obtenemos el id del thread
        //Vamos a probar poniendo una reina en cada columna de la primer fila.
        //printf("Buscando solucion en el tablero donde la reina empieza en la hilera 0 y columna %d \n", i);

        int arr[n]; //A diferencia del secuencial, le asignamos un tablero a cada thread.

        //Donde: arr (Arreglo/tablero), 0 (row 0 en donde vamos a probar acada reina), i (columna en donde ponemos la primer reina.)
        InsertarReinas(arr, 0, i, t_id); 
    }//Close for
}//Close Reinas()

//Main
int main(int argc, const char* argv[]){
    //Inilizacion al ejecutar el programa ./a.out
    if(argc < 4){
        printf("Error!: Ejecutar como ./a.out <tamaño del tablero> <numero de threads> <0/1 para imprimir tablas o no> \n");
        return 0;
    }//Close if 

    //Asignar el tama;o del tablero
    n = atoi(argv[1]); //Donde argv[1] (string) es el numero que el usuario asigna al ejectuar el programa

    //Obtener numero de threads
    int threads = atoi(argv[2]);
    omp_set_num_threads(threads);

    //Si se imprimen las soluciones o no.
    int option = atoi(argv[3]);

    if(option == 1){
        imprimir = true;
    }//Close if 

    //Llamar al metodo
    double start = omp_get_wtime();
    Reinas();
    double finish = omp_get_wtime();
    printf("Soluciones con un tablero de %d x %d : %d con un tiempo de ejecucion de: %f \n",n,n,soluciones, finish-start);
}//Close main()