#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

struct vertice_t{
u32 nombre;
u32 color;
u32 cantidadVecinos;
u32 *vecinos;
};

typedef struct vertice_t *Vertice;

Vertice inicializarVertice(u32 nombre, u32 nVertices) {
	Vertice vertice = malloc(1*sizeof(Vertice));
	//Valores iniciales para los atributos
	vertice->nombre = nombre;
	vertice->color = 0;
	vertice->cantidadVecinos = 0;
	//Asignar memoria equivalente al resto de los vértices (Estrategia: array fijo)
	vertice->vecinos = malloc((nVertices - 1) * sizeof(u32));
	//Retornar puntero al vértice creado
	return vertice;
}

int comparacionQSort(const void * a, const void * b) {
	return (*(int*)a - *(int*)b);
}

void agregarVecino(Vertice vertice, u32 nombreVecino) {
	u32 posicion = vertice->cantidadVecinos;
	//Insertar el vecino al final del array
	vertice->vecinos[posicion] = nombreVecino;
	//Actualizar el n° de vecinos
	++vertice->cantidadVecinos;
}

void imprimirVecinos(Vertice vertice) {
	printf("Los vecinos del vertice %u son:\n", vertice->nombre);
	//Recorrer el arreglo de vecinos linealmente e imprimir los valores
	for (int i = 0; i < vertice->cantidadVecinos; i++)
		printf("%d\n", vertice->vecinos[i]);
}
