#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FILE_NAME "registro.bin"

typedef struct{
    int dia;
    int mes;
    int anio;
}Fecha;

typedef struct{
    char nombre[20];
    int dni;
    char email[20];
}Pasajero;

typedef struct{
    char origen[20];
    char destino[20];
    Pasajero pasajero;
    Fecha salida;
    int numeroVuelo;
} Pasaje;

void crearArchivo(char fileName[]){
    FILE *file = fopen(fileName, "wb");
    if(file != NULL){
        fclose(file);
    }else{
        printf("\n-----Error creando el archivo-----\n");
    }

}

Pasaje inputPasaje(){
    Pasaje newPasaje;
    printf("Ingrese los datos del pasajero: \n");
    printf("Origen: ");
    fflush(stdin);
    gets(newPasaje.origen);
    printf("Destino:");
    fflush(stdin);
    gets(newPasaje.destino);
    printf("Datos del pasajero:\n");
    printf("> Nombre : ");
    fflush(stdin);
    gets(newPasaje.pasajero.nombre);
    printf("> DNI: ");
    scanf(" %i", &newPasaje.pasajero.dni);
    printf("> EMAIL: ");
    fflush(stdin);
    gets(newPasaje.pasajero.email);
    printf("Fecha del vuelo: \n");
    printf(">> DIA:");
    scanf(" %i", &newPasaje.salida.dia);
    printf(">> MES: ");
    scanf(" %i", &newPasaje.salida.mes);
    printf(">> AÑO: ");
    scanf(" %i", &newPasaje.salida.anio);
    return newPasaje;


}


void addPasaje(char fileName[]){
    FILE *file = fopen(fileName, "ab");

    if(file != NULL){
        Pasaje newPasaje = inputPasaje();
        fwrite(&newPasaje, sizeof(Pasaje), 1, file);
        fclose(file);
    }else{
        printf("\n---ERROR---\n");
    }
}

void addPasajes(char fileName[]){
    char seguirCargando = 's';
    while(seguirCargando != 'n'){
        addPasaje(fileName);
        ///Condicion de corte
        printf("Cargar otro? (s/n)");
        fflush(stdin);
        scanf(" %c", &seguirCargando);
    }
}
///EJERCICIO 2
void mostrarPorDNI(char fileName[], int targetDNI){

    FILE *file = fopen(fileName, "rb");
    if(file != NULL){
        Pasaje auxPasaje;
        while(fread(&auxPasaje, sizeof(Pasaje), 1, file) > 0){
            if(targetDNI == auxPasaje.pasajero.dni){
                printf("%i", auxPasaje.numeroVuelo);
            }
            mostrarPorDNI(fileName, targetDNI);
        }
    }
    fclose(file);
}
//EJERCICIO 3
int contarVuelos(char fileName[], int target){
    int contador = 0;
    FILE *file = fopen(fileName, "rb");
    if(file != NULL){
        Pasaje auxPasaje;
        while(fread(&auxPasaje, sizeof(Pasaje), 1, file) > 0){
            if(auxPasaje.numeroVuelo == target){
                contador++;
            }
        }
    }
    return contador;
}

Pasaje* crearArrayPasaje(int cantidad){
    return (Pasaje*)malloc(cantidad*sizeof(Pasaje));
}

void filtrarPasajes(char fileName[]){
    int targetVuelo;
    printf("\nIngrese el numero de vuelo que desea filtrar:");
    scanf(" %i", &targetVuelo);
    int dim = contarVuelos(fileName, targetVuelo);
    Pasaje* pasajeList = crearArrayPasaje(dim);

    FILE *file = fopen(fileName, "rb");
    if(file != NULL){
        Pasaje aux ;
        int contador = 0;
        while(fread(&aux, sizeof(Pasaje), 1, file) > 0){
            if(aux.numeroVuelo == targetVuelo){
                pasajeList[contador] = aux;
                contador++;
            }
        }
    }

}


//EJERCICIO 4
int obtenerPosVuelo(char fileName[], int target){
    FILE *file = fopen(fileName, "rb");
    if(file != NULL){
        int contador = 1;
        Pasaje aux;
        while(fread(&aux, sizeof(Pasaje), 1, file) > 0){
            if(aux.numeroVuelo != target){
                contador++;
            }
        }
        return contador;
    }else{
        printf("El target no existe");
        return -1;
    }
}

void modificarVuelo(char fileName[] ){
    int auxVuelo;
    printf("Ingrese el Numero de vuelo que desea modificar:");
    scanf(" %i", &auxVuelo);
    int pos = obtenerPosVuelo(fileName, auxVuelo);
    FILE *file = fopen(fileName, "ab" );
    fseek(file, 0, pos);

}

int main()
{
    crearArchivo(FILE_NAME);
    addPasajes(FILE_NAME);
    system("cls");
    filtrarPasajes(FILE_NAME);
    return 0;
}



























