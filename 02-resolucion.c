#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char ArchivoPasajes[30] = "pasajes.bin";

typedef struct
{
    char nombre[20];
    int dni;
    char email[20];
} Pasajero;

typedef struct
{
    int dia;
    int mes;
    int anio;
} Fecha;

typedef struct
{
    char origen[20];
    char destino[20];
    Pasajero pasajero;
    Fecha salida;
    int numeroVuelo;
} Pasaje;



///Punto 1:
void cargarFecha(Fecha *fc);
void cargarPasajero(Pasajero *pj);
Pasaje cargarUnPasaje ( Pasaje aux);
void cargarMuchosPasajeros ();
///Punto 2:
void mostrarFecha(Fecha fc);
void mostrarPasajero (Pasajero pj);
void MostrarPasaje(Pasaje aux);
void buscarPasajero (FILE *archi, int dni);///funcion recursiva
void abrirArchi (int dni);
///Punto 3:
int contarRegistrosVuelo (int numVuelo);
Pasaje* crearArreglo (int numVuelo, int *val);
void mostrarArreglo (Pasaje arreglo[], int val);
///Punto 4:
int contarRegistrosTotales ();
void modificarPosicion (int numVuelo, int posicion);
void mostrarArchivo ();


int main()
{
    int  val = 0;
    int dni=0;
    int numVuelo = 0;
    int vueloModificado = 0;
    int posicion = 0;
    int contador = 0;
    int opcion = 0;
    char seguir = 's';
    Pasaje *arreglo;

    while (seguir == 's')
    {
        printf ("Ingrese el punto que desea ejecutar: ");
        fflush (stdin);
        scanf ("%d", &opcion);

        switch (opcion)
        {
        case 1:
            cargarMuchosPasajeros ();
            printf ("\n");
            break;

        case 2:
            abrirArchi (dni);
            printf ("\n");
            break;

        case 3:
            printf ("Ingrese el numero de vuelo que desea buscar: ");
            fflush (stdin);
            scanf ("%d", &numVuelo);

            contador = contarRegistrosVuelo (numVuelo);
            printf ("\nLos vuelos con ese numero son: %d\n", contador);
            printf ("\n");

            arreglo = crearArreglo (numVuelo, &val);
            mostrarArreglo (arreglo, val);
            printf ("\n");
            break;

        case 4:
            printf ("Ingrese el nuevo numero de vuelo: ");
            fflush (stdin);
            scanf ("%d", &vueloModificado);

            printf ("Ingrese la posicion que desea modificar: ");
            fflush (stdin);
            scanf ("%d", &posicion);

            modificarPosicion (vueloModificado, posicion);
            mostrarArchivo ();
            printf ("\n");
            break;

        default:
            printf ("Opcion invalida. ");
            break;
        }

        printf ("Desea volver al menu? s/n");
        fflush (stdin);
        scanf (" %c", &seguir);
    }

    return 0;
}


/// /////////////Punto 1\\\\\\\\\\\\\\

void cargarFecha(Fecha *fc)
{


        printf ("Dia : ");
        fflush (stdin);
        scanf ("%d", &fc->dia);

        printf ("Mes : ");
        fflush (stdin);
        scanf ("%d", &fc->mes);

        printf ("Anio : ");
        fflush (stdin);
        scanf ("%d", &fc->anio);

}

void cargarPasajero(Pasajero *pj)
{

        printf ("Nombre del pasajero: ");
        fflush (stdin);
        gets (pj->nombre);

        printf ("DNI: ");
        fflush (stdin);
        scanf ("%d", &pj->dni);

        printf ("Mail: ");
        fflush (stdin);
        gets (pj->email);
}

Pasaje cargarUnPasaje ( Pasaje aux)
{


        printf ("Origen: ");
        fflush (stdin);
        gets (aux.origen);

        printf ("Destino: ");
        fflush (stdin);
        gets (aux.destino);

        cargarPasajero(&aux.pasajero);
        cargarFecha(&aux.salida);


        printf ("Numero de vuelo: ");
        fflush (stdin);
        scanf ("%d", &aux.numeroVuelo);

        printf("===========================");
    return aux;
}




void cargarMuchosPasajeros ()
{
    char seguir = 's';
    FILE* buff=fopen(ArchivoPasajes,"ab");
    Pasaje aux;
    if(buff)
    {
        while (seguir == 's')
        {
            aux =cargarUnPasaje(aux);

            fwrite(&aux,sizeof(Pasaje),1,buff);

            printf ("Desea agregar otro pasajero? s/n  ");
            fflush (stdin);
            scanf (" %c", &seguir);
        }
        fclose(buff);
    }

}

/// /////////////Punto 2\\\\\\\\\\\\\\

void mostrarFecha(Fecha fc)
{
    printf ("Dia : %i",fc.dia);

        printf ("Mes :%d", fc.mes);

        printf ("Anio : %d", fc.anio);
}

void mostrarPasajero (Pasajero pj)
{
        printf ("Nombre del pasajero: ");
        puts (pj.nombre);

        printf ("DNI:%d", pj.dni);

        printf ("Mail: ");
        puts (pj.email);
}

void MostrarPasaje(Pasaje aux)
{

      printf ("Origen: ");
        puts (aux.origen);

        printf ("Destino: ");
        puts (aux.destino);

        mostrarPasajero(aux.pasajero);
        mostrarFecha(aux.salida);


        printf ("Numero de vuelo: %d", aux.numeroVuelo);

        printf("===========================");
}


void buscarPasajero (FILE *archi, int dni)
{
    Pasaje aux;

    if(fread (&aux, sizeof (Pasaje), 1, archi) > 0)
    {
        if (aux.pasajero.dni == dni)
        {
           MostrarPasaje(aux);

        }
        buscarPasajero(archi,dni);
    }
}


void abrirArchi (int dni)
{

    printf ("Ingrese el dni del pasajero que desea buscar: ");
    fflush (stdin);
    scanf ("%d", &dni);

    FILE *buff = fopen (ArchivoPasajes, "rb");

    if (buff != NULL)
    {
        buscarPasajero (buff, dni);
        fclose (buff);
    }
}


/// /////////////Punto 3\\\\\\\\\\\\\\

int contarRegistrosVuelo (int numVuelo)
{
    int contador = 0;
    Pasaje aux;

    FILE *archi = fopen (ArchivoPasajes, "rb");

    if (archi != NULL)
    {
        while (fread (&aux, sizeof (Pasaje), 1, archi) > 0)
        {
            if (aux.numeroVuelo == numVuelo)
            {
                contador++;
            }
        }
        fclose (archi);
    }

    return contador;
}

Pasaje* crearArreglo (int numVuelo, int *val)
{
    int contador = contarRegistrosVuelo (numVuelo);
    Pasaje *arreglo = (Pasaje*) malloc (sizeof (Pasaje) * contador);

    Pasaje aux;
    FILE *archi = fopen (ArchivoPasajes, "rb");

    if (archi != NULL)
    {
        while (fread (&aux, sizeof (Pasaje), 1, archi) > 0)
        {
            if (aux.numeroVuelo == numVuelo)
            {
                arreglo[*val] = aux;
                (*val)++;
            }
        }
        fclose (archi);
    }

    return arreglo;
}

void mostrarArreglo (Pasaje arreglo[], int val)
{
    printf ("---- Arreglo Dinamico ----\n");

    for (int i = 0; i < val; i++)
    {
        MostrarPasaje(arreglo[i]);
        printf ("\n");
    }
}

/// /////////////Punto 4\\\\\\\\\\\\\\

int contarRegistrosTotales ()
{
    int registros = 0;
    FILE *archi = fopen (ArchivoPasajes, "rb");

    if (archi != NULL)
    {
        fseek (archi, sizeof (Pasaje), SEEK_END);

        registros = ftell (archi) / sizeof (Pasaje);

        fclose (archi);
    }

    return registros;
}

void modificarPosicion (int numVuelo, int posicion)
{
    int registros = contarRegistrosTotales();

    Pasaje aux;
    FILE *archi = fopen (ArchivoPasajes, "r+b");

    if (archi != NULL && posicion-1 <= registros)
    {
        fseek(archi, sizeof (Pasaje) * posicion-1, SEEK_SET);

        fread (&aux, sizeof (Pasaje), 1, archi);

        aux.numeroVuelo = numVuelo;

        fseek(archi, sizeof (Pasaje) * posicion-1, SEEK_SET);

        fwrite (&aux, sizeof (Pasaje), 1, archi);

        fclose (archi);
    }
}

void mostrarArchivo ()
{
    Pasaje aux;
    FILE *archi = fopen (ArchivoPasajes, "rb");

    if (archi != NULL)
    {
        printf ("--------------- Archivo ----------------\n");
        while(fread (&aux, sizeof (Pasaje), 1, archi) > 0)
        {
            MostrarPasaje(aux);
            printf ("\n");
        }
        fclose (archi);
    }
}
