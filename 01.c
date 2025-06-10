// Apellido y Nombre: [COMPLETAR CON TU APELLIDO Y NOMBRE]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pila.h"	// Librería de Pilas del campus
#include "string.h" // Librería de Strings

#define MAX_COHETES 5
#define MAX_NOMBRE 50

// Estructuras necesarias para guardar la información de los cohetes
typedef struct
{
	char capitan[MAX_NOMBRE];
	char navegador[MAX_NOMBRE];
	char mecanico[MAX_NOMBRE];
	int puntaje;
} Tripulacion;

typedef struct
{
	char nombre[MAX_NOMBRE];
	int numero_identificador;
	float litros_combustible;
	int num_misiles;
	Tripulacion tripulacion;
} Cohete;

// Prototipos de funciones
void cargarCohetes(Cohete cohetes[], int tamanio);
void mostrarCohete(Cohete cohete);
void buscarTripulante(Cohete cohetes[], int indice, int tamanio, char *nombre_tripulante);
void subirArchivoCohetesInfo(Cohete cohetes[], int tamanio);
int contarCohetesSinMisiles();
Cohete *crearArregloSinMisiles(int *tamanio_nuevo);
void mostrarArreglo(Cohete cohetes[], int tamanio);

int main()
{
	printf("=== RECUPERATORIO 2DO PARCIAL - COHETES ===\n\n");

	// Ejercicio 1: Arreglo estático de cohetes
	Cohete cohetes[MAX_COHETES];

	printf("--- EJERCICIO 1: CARGA DE COHETES ---\n");
	cargarCohetes(cohetes, MAX_COHETES);

	// Ejercicio 2: Función recursiva para buscar tripulante
	printf("\n--- EJERCICIO 2: BUSCAR TRIPULANTE ---\n");
	char nombre_buscar[MAX_NOMBRE];
	printf("Ingrese el nombre del tripulante a buscar: ");
	fgets(nombre_buscar, MAX_NOMBRE, stdin);
	nombre_buscar[strcspn(nombre_buscar, "\n")] = '\0'; // Eliminar salto de línea

	buscarTripulante(cohetes, 0, MAX_COHETES, nombre_buscar);

	// Ejercicio 3: Subir información al archivo
	printf("\n--- EJERCICIO 3: GUARDANDO EN ARCHIVO ---\n");
	subirArchivoCohetesInfo(cohetes, MAX_COHETES);
	printf("Información guardada en 'cohetes.txt'\n");

	// Ejercicio 4: Contar cohetes sin misiles desde archivo
	printf("\n--- EJERCICIO 4: CONTAR COHETES SIN MISILES ---\n");
	int cohetes_sin_misiles = contarCohetesSinMisiles();
	printf("Cantidad de cohetes sin misiles: %d\n", cohetes_sin_misiles);

	// Ejercicio 5: Crear arreglo dinámico con cohetes sin misiles
	printf("\n--- EJERCICIO 5: ARREGLO DINAMICO SIN MISILES ---\n");
	int tamanio_nuevo = 0;
	Cohete *cohetes_sin_misiles_arr = crearArregloSinMisiles(&tamanio_nuevo);

	if (cohetes_sin_misiles_arr != NULL && tamanio_nuevo > 0)
	{
		printf("Cohetes sin misiles en arreglo dinámico:\n");
		mostrarArreglo(cohetes_sin_misiles_arr, tamanio_nuevo);
		free(cohetes_sin_misiles_arr);
	}
	else
	{
		printf("No hay cohetes sin misiles o error al crear el arreglo.\n");
	}

	printf("\n=== FIN DEL PROGRAMA ===\n");
	return 0;
}

// EJERCICIO 1: Función para cargar los cohetes manualmente
void cargarCohetes(Cohete cohetes[], int tamanio)
{
	for (int i = 0; i < tamanio; i++)
	{
		printf("\n--- Cargando Cohete %d ---\n", i + 1);

		printf("Nombre del cohete: ");
		fflush(stdin);
		gets(cohetes[i].nombre);

		printf("Número identificador: ");
		scanf("%d", &cohetes[i].numero_identificador);

		printf("Litros de combustible: ");
		scanf("%f", &cohetes[i].litros_combustible);

		printf("Número de misiles: ");
		scanf("%d", &cohetes[i].num_misiles);

		fflush(stdin);

		printf("--- Tripulación ---\n");
		printf("Capitán: ");
		gets(cohetes[i].tripulacion.capitan);

		printf("Navegador: ");
		gets(cohetes[i].tripulacion.navegador);

		printf("Mecánico: ");
		gets(cohetes[i].tripulacion.mecanico);

		printf("Puntaje histórico: ");
		scanf("%d", &cohetes[i].tripulacion.puntaje);
		fflush(stdin);
	}
}

// EJERCICIO 2: Función recursiva que busca un tripulante específico
void buscarTripulante(Cohete cohetes[], int indice, int tamanio, char *nombre_tripulante)
{
	// Caso base: si hemos recorrido todo el arreglo
	if (indice >= tamanio)
	{
		return;
	}

	// Verificar si el tripulante está en el cohete actual
	if (strcmp(cohetes[indice].tripulacion.capitan, nombre_tripulante) == 0 ||
		strcmp(cohetes[indice].tripulacion.navegador, nombre_tripulante) == 0 ||
		strcmp(cohetes[indice].tripulacion.mecanico, nombre_tripulante) == 0)
	{

		printf("El tripulante '%s' está en el cohete:\n", nombre_tripulante);
		mostrarCohete(cohetes[indice]);
		printf("\n");
	}

	// Llamada recursiva para el siguiente índice
	buscarTripulante(cohetes, indice + 1, tamanio, nombre_tripulante);
}

// EJERCICIO 3: Función para subir información al archivo
void subirArchivoCohetesInfo(Cohete cohetes[], int tamanio)
{
	FILE *archivo = fopen("cohetes.txt", "wb");
	if (archivo == NULL)
	{
		printf("Error al abrir el archivo para escribir.\n");
		return;
	}

	fwrite(cohetes, sizeof(Cohete), tamanio, archivo);
	fclose(archivo);
}

// EJERCICIO 4: Función que cuenta cohetes sin misiles desde el archivo
int contarCohetesSinMisiles()
{
	FILE *archivo = fopen("cohetes.txt", "rb");
	if (archivo == NULL)
	{
		printf("Error al abrir el archivo para leer.\n");
		return 0;
	}

	Cohete cohete_temp;
	int contador = 0;

	while (fread(&cohete_temp, sizeof(Cohete), 1, archivo) == 1)
	{
		if (cohete_temp.num_misiles == 0)
		{
			contador++;
		}
	}

	fclose(archivo);
	return contador;
}

// EJERCICIO 5: Función que crea arreglo dinámico con cohetes sin misiles
Cohete *crearArregloSinMisiles(int *tamanio_nuevo)
{
	// Primero contar cuántos cohetes sin misiles hay
	int cantidad_sin_misiles = contarCohetesSinMisiles();

	if (cantidad_sin_misiles == 0)
	{
		*tamanio_nuevo = 0;
		return NULL;
	}

	// Crear arreglo dinámico del tamaño justo
	Cohete *arreglo_dinamico = (Cohete *)malloc(sizeof(Cohete) * cantidad_sin_misiles);
	if (arreglo_dinamico == NULL)
	{
		printf("Error al asignar memoria.\n");
		*tamanio_nuevo = 0;
		return NULL;
	}
	Elemento *arr = (int *)malloc()
		// Leer archivo y copiar cohetes sin misiles
		FILE *archivo = fopen("cohetes.txt", "rb");
	if (archivo == NULL)
	{
		printf("Error al abrir el archivo para leer.\n");
		free(arreglo_dinamico);
		*tamanio_nuevo = 0;
		return NULL;
	}

	Cohete cohete_temp;
	int indice = 0;

	while (fread(&cohete_temp, sizeof(Cohete), 1, archivo) == 1)
	{
		if (cohete_temp.num_misiles == 0)
		{
			arreglo_dinamico[indice] = cohete_temp;
			indice++;
		}
	}

	fclose(archivo);
	*tamanio_nuevo = cantidad_sin_misiles;
	return arreglo_dinamico;
}

// Función auxiliar para mostrar un cohete
void mostrarCohete(Cohete cohete)
{
	printf("Cohete: %s (ID: %d)\n", cohete.nombre, cohete.numero_identificador);
	printf("Combustible: %.2f litros\n", cohete.litros_combustible);
	printf("Misiles: %d\n", cohete.num_misiles);
	printf("Tripulación:\n");
	printf("  Capitán: %s\n", cohete.tripulacion.capitan);
	printf("  Navegador: %s\n", cohete.tripulacion.navegador);
	printf("  Mecánico: %s\n", cohete.tripulacion.mecanico);
	printf("  Puntaje: %d\n", cohete.tripulacion.puntaje);
}

// Función auxiliar para mostrar un arreglo de cohetes
void mostrarArreglo(Cohete cohetes[], int tamanio)
{
	for (int i = 0; i < tamanio; i++)
	{
		printf("\n--- Cohete %d ---\n", i + 1);
		mostrarCohete(cohetes[i]);
	}
}
