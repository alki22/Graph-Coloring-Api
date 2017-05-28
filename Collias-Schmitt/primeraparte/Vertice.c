#include "JonSnow.h"

void inicializarVertice(Vertice vertice, u32 nombre, u32 etiqueta) {
	//Valores iniciales para los atributos
	vertice->inicializado = true;
	vertice->nombre = nombre;
	vertice->etiqueta = etiqueta;
	vertice->color = 0;
	vertice->cantVecinos = 0;
	vertice->tamanoArray = 1;
	/*
	Estrategia:
	duplicar el tamaño del array con realloc cuando se llene 
	y al final de la carga del grafo eliminar los espacios sobrantes
	*/
	vertice->vecinos = malloc(1 * sizeof(Vertice));
}

void destruirVertice(Vertice vertice) {
	free(vertice->vecinos);
	free(vertice);
}

void agregarVecino(Vertice verticeA, Vertice verticeB) {
	//El elemento se insertará en el último lugar del arreglo
	u32 posicion = verticeA->cantVecinos;
	//Si el arreglo está lleno, duplicar su tamaño
	if(verticeA->cantVecinos >= verticeA->tamanoArray) {
		Vertice *vecinos;
		verticeA->tamanoArray += 4;
		vecinos = realloc(verticeA->vecinos, verticeA->tamanoArray * sizeof(*verticeA->vecinos));
		verticeA->vecinos = vecinos;
	}
	//Insertar el vecino al final del array
	verticeA->vecinos[posicion] = verticeB;
	//Actualizar el n° de vecinos
	++verticeA->cantVecinos;
}

void optimizarMemoria(Vertice vertice) {
	Vertice* vecinos = realloc(vertice->vecinos, (vertice->cantVecinos) * sizeof(*vertice->vecinos));
	vertice->vecinos = vecinos;
}

void imprimirVecinos(Vertice vertice) {
	printf("Los vecinos del vertice %u son:\n", vertice->nombre);
	//Recorrer el arreglo de vecinos linealmente e imprimir los valores
	for (u32 i = 0; i < vertice->cantVecinos; i++)
		printf("%u ", vertice->vecinos[i]->nombre);
	printf("\n");
}
