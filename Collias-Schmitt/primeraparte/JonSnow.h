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


/*
Asigna valores a los atributos del vértice. No hay un constructor para este TAD,
ya que todos los struct grafo_t son inicializados durante la carga del grafo.
^Para más info ver Grafo.c:13:5^
*/
void inicializarVertice(Vertice vertice, u32 nombre, u32 etiqueta);

/*
Libera memoria asignada a un puntero a vértice,
vale la misma aclaración que para inicializarVertice
*/
void destruirVertice(Vertice vertice);

//Añade un vecino al array de vecinos del vértice
void agregarVecino(Vertice verticeA, Vertice verticeB);

/*
Libera excedente de memoria usado para los vecinos del vértice
(Ver detalles de la estrategia usada en Vertice:12:5)
*/
void optimizarMemoria(Vertice vertice);

//Imprime los vecinos del vértice
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
};

//Definición del puntero a grafo
typedef struct WinterSt *WinterIsHere;

/*
Funciones del grafo
*/

//Constructor de puntero a grafo, incluye la creación del grafo y de vértices
WinterIsHere crearGrafo(u32 cantVertices, u32 cantLados);


u32 NumeroDeVertices(WinterIsHere W);


u32 NumeroDeLados(WinterIsHere W);


u32 NumeroVerticesDeColor(WinterIsHere W,u32 i);


u32 NumeroDeColores(WinterIsHere W);


u32 IesimoVerticeEnElOrden(WinterIsHere W,u32 i);

//Devuelve el grado del vértice con la etiqueta 'i'
u32 gradoDelVertice(WinterIsHere grafo, u32 i);

//Devuelve el color del vértice con la etiqueta 'i'
u32 colorDelVertice(WinterIsHere grafo, u32 i);

//Devuelve el nombre del vértice con la etiqueta 'i'
u32 nombreDelVertice(WinterIsHere grafo, u32 i);

//Devuelve el grado del vértice con la etiqueta 'i'
u32 IesimoVecino(WinterIsHere W, u32 x,u32 i);

/*
Inserta un vértice en la tabla,
en caso de haber un vértice con ese nombre, devuelve su etiqueta
*/
int insertarEnHash(WinterIsHere grafo, u32 nombre);

//Añade como vecino del vértice de nombreA al de nombreB y viceversa(grafo no dirigido)
void agregarLado(WinterIsHere grafo, u32 nombreA, u32 nombreB);

//Libera la memoria pedida para el grafo y su estructura
int Primavera(WinterIsHere grafo);

//Lee el grafo por stdin y genera la estructura de acuerdo a lo leido
WinterIsHere WinterIsComing();


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

/*
Dado que su funcionamiento está explicado ahí y que son las 5:10 del sábado,
leer detalles en Ordenes.c . Gracias
*/
void mezclarColores(u32 *array, u32 tamano, u32 semilla);


void mezclarVertices(Vertice *array, u32 tamano, u32 semilla);


void ordenarPorBloques(WinterIsHere W, u32* colores, u32 cantColores);


void funcionCero(WinterIsHere W);


void funcionUno(WinterIsHere W);


void funcionDos(WinterIsHere W);


void funcionTres(WinterIsHere W);


void funcionMayorTres(WinterIsHere W, u32 x);


void OrdenNatural(WinterIsHere grafo);


void OrdenWelshPowell(WinterIsHere grafo);


void AleatorizarVertices(WinterIsHere W, u32 x);


void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x);


#endif // JONSNOW_H_ 