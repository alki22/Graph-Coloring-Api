
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "Vertice.c"

typedef unsigned int u32;

struct grafo_t {
	u32 cantVertices;
	//Hashtable de vértices
	Vertice *hashTable;
};

typedef struct grafo_t *Grafo;


Grafo crearGrafo(u32 cantVertices) {
	//Valores iniciales para la estructura de grafo
	//Asignar memoria inicial para la estructura
	Grafo grafo = malloc(sizeof(struct grafo_t));
	grafo->cantVertices = cantVertices;
	//Asignar memoria para un numero n (= cantVertices) de vertices
	grafo->hashTable = calloc(cantVertices, sizeof(Vertice));
	//Devuelve un puntero al grafo generado
	return grafo;
}


int insertarEnHash(Grafo grafo, u32 nombre) {
	/*
	Define una posición i utilizando el modulo entre el nombre del vertice
	y la cantidad de vertices del grafo
	*/
	int posicion = nombre % grafo->cantVertices;
	bool insertado = false;
	Vertice iesimoVertice = NULL;
	
	//Recorre linealmente la tabla desde la posición i dada
	while(!insertado){
		//Comprueba que el iesimo lugar de la tabla no esté asignado
		if(grafo->hashTable[posicion] == NULL) {
			//En caso de no estarlo, inicializa el vertice "nombre" en esa posición
			Vertice nuevoVertice = inicializarVertice(nombre, grafo->cantVertices);
			grafo->hashTable[posicion] = nuevoVertice;
			//Liberar memoria asignada;
			free(nuevoVertice);
			//Asigna true al booleano para terminar el ciclo
			insertado |= 1;
		}
		else {
			//En caso de estar asignado:
			iesimoVertice = grafo->hashTable[posicion];
			//Probar en la siguiente posición
			if (iesimoVertice->nombre != nombre)
				posicion = (posicion + 1) % grafo->cantVertices;
		}
	}
	//Devuelve la posición de la tabla en que se inserto al vertice
	return posicion;
}


int buscarEnHash(Grafo grafo, u32 nombreBuscado) {
	/*
	Define una posición i utilizando el modulo entre el nombre del vertice
	y la cantidad de vertices del grafo
	*/
	int posicion = nombreBuscado % grafo->cantVertices;
	int busquedas = 0;
	Vertice iesimoVertice = NULL;
	
	//Recorre linealmente la tabla desde la posición i dada
	while(busquedas < grafo->cantVertices) {
		iesimoVertice = grafo->hashTable[posicion];
		/*
		Si el iésimo vértice tiene el nombre que estamos buscando,
		termina la ejecución y devuelve la posición del elemento
		*/
		if (iesimoVertice->nombre == nombreBuscado) {
			return posicion;
		}
		//Caso contrario, probar con la siguiente posicion
		posicion = (posicion + 1) % grafo->cantVertices;
		++busquedas;
	}
	/*
	En caso de haber buscado en todos los lugares de la tabla y 
	no haber encontrado al elemento(busquedas >= cantVertices), 
	devuelve -1
	*/
	return -1;
}


void agregarLado(Grafo grafo, u32 nombreA, u32 nombreB) {
	int posicionA, posicionB;
	bool estaA, estaB;
	
	/*
	Comprobar que los vértices con nombres A y B estén en el grafo,
	si alguno no esté, crearlo, 
	y si estén, obtener su posición en la tabla
	*/
	posicionA = buscarEnHash(grafo, nombreA);
	estaA = (posicionA != -1);
	
	if (!estaA)
		posicionA = insertarEnHash(grafo, nombreA);

	posicionB = buscarEnHash(grafo, nombreB);
	estaB = (posicionB != -1);

	if (!estaB)
		posicionB = insertarEnHash(grafo, nombreB);

	Vertice verticeA = grafo->hashTable[posicionA];
	Vertice verticeB = grafo->hashTable[posicionB];
	/*
	Agrega el lado entre el vértice A y B
	Como el grafo NO es dirigido, agrega el lado entre B y A también
	*/
	agregarVecino(verticeA, nombreB);
	agregarVecino(verticeB, nombreA);

	//Tareas de limpieza
	verticeA = NULL;
	verticeB = NULL;
}


int main () {
	Grafo grafo = crearGrafo(3);
	// SEGMENTATION PSV FAULT
	int posicion1 = insertarEnHash(grafo, 1);
	printf("Vertice 1 insertado en la posicion %d\n", posicion1);
	int posicion2 = insertarEnHash(grafo, 2);
	printf("Vertice 1 insertado en la posicion %d\n", posicion2);
	int posicion3 = insertarEnHash(grafo, 22);
	printf("Vertice 1 insertado en la posicion %d\n", posicion3);

	agregarLado(grafo, 2, 22);
	printf("Lado agregado entre 2 y 22\n");
	agregarLado(grafo, 2, 1);
	printf("Lado agregado entre 2 y 1\n");
	agregarLado(grafo, 1, 22);
	printf("Lado agregado entre 1 y 22\n");

	free(grafo);
	return 0;
}