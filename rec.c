#include <stdio.h>
#include <stdlib.h>

void contarHastaCero(int);
int acumularValores(int);
void mostrarArrRecursivo(int[],int,int);
void recorrerArchivoRecursivo(FILE*);

int main()
{
    contarHastaCero(3);
    //int suma = acumularValores(0);
    //printf("el total es: %i", suma);

    //int arr[5] = {10,20,30,40,50};

    //mostrarArrRecursivo(arr, 5, 0);

    return 0;
}

void contarHastaCero(int num)
{

    //printf("%i\n", num);
    //sleep(1);
    if(num>0)  // -> condicion de corte
    {
        printf("realizo la llamada recursiva\n");
        //llamada recursiva
        contarHastaCero(num-1); //-> acercamiento al corte
    }
    printf("despues del llamado recursivo:\n");
    sleep(1);
    printf("%i\n", num);

}

int acumularValores(int suma)
{
    printf("ingrese un numero para acumular o 0 para finalizar: ");
    int num;
    scanf("%i", &num);

    if(num!=0)
    {
        suma = acumularValores(num+suma);
    }

    return suma;
}

void mostrarArrRecursivo(int arr[], int validos, int i)
{
    if(i<validos)
    {
        printf("pos: %i - valor:%i\n", i, arr[i]);
        mostrarArrRecursivo(arr, validos, i+1);
    }
}

void recorrerArchivoRecursivo(FILE *archivo)
{

    int num;

    if (fread(&num, sizeof(int), 1, archivo)>0)   // condicion de corte: si no se puede leer m�s, terminamos
    {
        printf("%i - ", num);
        recorrerArchivoRecursivo(archivo); // Llamada recursiva
    }
}

void abrirArchi(char nombreArch[]){
    FILE*fp= fopen(nombreArch, "rb");

    if(fp!=NULL){
        recorrerArchivoRecursivo(fp);
        fclose(fp);
    }

}

int buscarMenor(int arr[], int validos, int i, int menor){
    if(i<validos){

        if(menor>arr[i]){
            menor = arr[i];
        }
        menor = buscarMenor(arr, validos, i+1, menor);
    }

    return menor;

}






