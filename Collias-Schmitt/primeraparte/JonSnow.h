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

/*
Vertice = puntero a struct vertice_t
Quizás no es el mejor nombre, pero al menos a la hora del desarrollo
nos lo simplificó mucho ver al puntero como una instancia de struct vertice_t
La misma aclaración vale para Cola = puntero a struct cola_t
*/
typedef struct vertice_t *Vertice;

/*
TAD vertice_t (vertice)
*/
struct vertice_t{
	bool inicializado;
	u32 nombre;
	u32 etiqueta;
	u32 color;
	u32 cantVecinos;
	u32 tamanoArray;
	Vertice *vecinos;
};



void inicializarVertice(Vertice vertice, u32 nombre, u32 etiqueta);


void destruirVertice(Vertice vertice);


void agregarVecino(Vertice verticeA, Vertice verticeB);


void optimizarMemoria(Vertice vertice);


void imprimirVecinos(Vertice vertice);

/*
TAD WinterSt (Grafo)
*/

struct WinterSt {
	//Atributos del vértice
	u32 cantVertices;
	u32 cantLados;
	u32 cantColores;
	//Hashtable de vértices
	Vertice *hashTable;
	/*
	Orden
	El orden inicial es el que se ingresa a la Hashtable
	*/
	Vertice *orden;
	//Array de booleanos utilizado para correr Greedy
	bool *vertUsados;
};

//Definición del puntero a grafo
typedef struct WinterSt *WinterIsHere;

/*
Funciones del grafo
*/

WinterIsHere crearGrafo(u32 cantVertices, u32 cantLados);


u32 gradoDelVertice(WinterIsHere grafo, u32 i);


u32 colorDelVertice(WinterIsHere grafo, u32 i);


u32 nombreDelVertice(WinterIsHere grafo, u32 i);


int insertarEnHash(WinterIsHere grafo, u32 nombre);


void agregarLado(WinterIsHere grafo, u32 nombreA, u32 nombreB);


int destruirGrafo(WinterIsHere grafo);


WinterIsHere cargarGrafo();


/*
TAD cola_t (cola)
*/

typedef struct cola_t *Cola;

struct cola_t {
	//Array de vértices
	Vertice *vertices;
	/*
	Primer y último elemento
	Se usa int y no u32 en este caso porque la inicialización
	requiere usar los valores -1, ya que al ser un array, 
	todos, los números desde el cero son indices del mismo
	*/
	int primero;
	int ultimo;
};

/*
Funciones de la cola
*/


//Constructor del TAD cola_t
Cola crearCola(u32 tamano);

//Devuelve si la cola está vacía o no
bool estaVacia(Cola cola);

//Añade un vértice a la cola
void agregarACola(Cola cola, Vertice vertice);

//No me gusta el nombre; "quita" al primer elemento de la cola y lo devuelve
Vertice Decolar(Cola cola);

//Destruye una cola creada previamente
int destruirCola(Cola cola);


/*
Funciones de coloreo
*/

u32 Greedy(WinterIsHere grafo);

int Bipartito(WinterIsHere grafo);

/*
Funciones de ordenamiento
*/

void OrdenNatural(WinterIsHere grafo);

void OrdenWelshPowell(WinterIsHere grafo);

#endif // JONSNOW_H_ 