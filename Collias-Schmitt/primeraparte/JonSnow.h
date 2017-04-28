/*
Integrantes:
Federico Schmitt - e-mail: kolo_schmitt@gmail.com
Theo Alkibiades Collias - e-mail: alki.collias@gmail.com
*/

#ifndef JONSNOW_H_
#define JONSNOW_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

typedef unsigned int u32;

typedef struct vertice_t *Vertice;

struct vertice_t{
	bool inicializado;
	u32 nombre;
	u32 etiqueta;
	u32 color;
	u32 cantidadVecinos;
	u32 tamanoArray;
	Vertice *vecinos;
};

void inicializarVertice(Vertice vertice, u32 nombre, u32 etiqueta);

u32 colorDelVertice(Vertice vertice);

u32 nombreDelVertice(Vertice vertice);

void destruirVertice(Vertice vertice);

void agregarVecino(Vertice verticeA, Vertice verticeB);

void optimizarMemoria(Vertice vertice);

void imprimirVecinos(Vertice vertice);

struct WinterSt {
	//Atributos del vértice
	u32 cantVertices;
	u32 cantLados;
	u32 cantColores;
	//Hashtable de vértices
	Vertice *hashTable;
	//Órdenes
	Vertice *ordenNatural;
	Vertice *orden;
	bool *vertUsados;
};

typedef struct WinterSt *WinterIsHere;

WinterIsHere crearGrafo(u32 cantVertices, u32 cantLados);

u32 gradoDelVertice(WinterIsHere grafo, u32 nombreDelVertice);

int insertarEnHash(WinterIsHere grafo, u32 nombre);

void agregarLado(WinterIsHere grafo, u32 nombreA, u32 nombreB);

int destruirGrafo(WinterIsHere grafo);

WinterIsHere cargarGrafo();

#endif // JONSNOW_H_ 