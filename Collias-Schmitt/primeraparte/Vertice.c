#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned int u32;

struct vertice_t{
u32 nombre;
u32 color;
u32 cantidadVecinos;
u32 tamanoArray;
u32 *vecinos;
};

typedef struct vertice_t *Vertice;

void inicializarVertice(Vertice vertice, u32 nombre, u32 nVertices) {
	//Valores iniciales para los atributos
	vertice->nombre = nombre;
	vertice->color = 0;
	vertice->cantidadVecinos = 0;
	vertice->tamanoArray = 1;
	/*
	Asignar memoria equivalente al resto de los vértices 
	Estrategia: 
	duplicar el tamaño del array con realloc cuando se llene 
	y al final de la carga del grafo eliminar los espacios sobrantes
	*/
	vertice->vecinos = malloc(1 * sizeof(u32));
	//Devolver puntero al vértice creado

}

void destruirVertice(Vertice vertice) {
	free(vertice->vecinos);
	free(vertice);
	vertice = NULL;
}

void agregarVecino(Vertice vertice, u32 nombreVecino) {
	//El elemento se insertará en el último lugar del arreglo
	u32 posicion = vertice->cantidadVecinos;
	//Si el arreglo está lleno, duplicar su tamaño
	if(vertice->cantidadVecinos >= vertice->tamanoArray) {
		vertice->tamanoArray *= 2;
		realloc(vertice->vecinos, vertice->tamanoArray * sizeof(*vertice->vecinos));
	}
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
