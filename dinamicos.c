#include <stdio.h>
#include <stdlib.h>

void cargarArr(int[], int);
void agregarDatos(int [], int, int);
void mostrarArr(int[], int );

int* declararArr(int);
void declararArr2(int , int**);

int* redimensionarArr(int*,int);
void redimensionarArr2(int**, int);

int main()
{
    int cant = 10;
    int cantNueva = 15;

    // con punteros simples
    //int*arr = declararArr(cant);

    // con punteros dobles
    int* arr;
    declararArr2(cant, &arr);

    cargarArr(arr, cant);
    printf("arreglo dinamico:\n");
    mostrarArr(arr, cant);

    //con punteros simples
    //arr = redimensionarArr(arr, cantNueva);

    //con punteros dobles
    redimensionarArr2(&arr, cantNueva);

    agregarDatos(arr, cantNueva, 10);
    printf("\narreglo redimensionado:\n");
    mostrarArr(arr, cantNueva);

    int* arr2 = (int*) calloc(cant, sizeof(int));
    printf("\narreglo inicializado en 0:\n");
    mostrarArr(arr2, cant);

    return 0;
}

void mostrarArr(int arr[], int cant){
    for(int i=0; i<cant;i++){
        printf("%i- ", arr[i]);
    }
}

void agregarDatos(int arr[], int cant, int validos){
    for(int i=validos; i<cant;i++){
        arr[i]= i;
    }
}

void cargarArr(int arr[], int cant){
    for(int i=0; i<cant;i++){
        arr[i]= i;
    }
}

int* declararArr(int cant){

    int* arr = (int*) malloc(cant*sizeof(int));
    return arr;
}

void declararArr2(int cant, int**PuntArr){

    *PuntArr = (int*) malloc(cant*sizeof(int));
}

int* redimensionarArr(int* arr,int cantNueva){
    return (int*)realloc(arr, cantNueva*sizeof(int));
}

void redimensionarArr2(int** PuntArr, int cantNueva){
    *PuntArr = (int*) realloc(*PuntArr, cantNueva*sizeof(int));
}





