#include "JonSnow.h"

WinterIsHere crearGrafo(u32 cantVertices, u32 cantLados) {
	//Valores iniciales para la estructura de grafo
	//Asignar memoria inicial para la estructura
	WinterIsHere grafo = NULL;
	grafo = malloc(sizeof(struct WinterSt));
	grafo->cantVertices = cantVertices;
	grafo->cantLados = cantLados;
	grafo->cantColores = 0;
	//Asignar memoria para un numero n (= cantVertices) de vertices
	grafo->hashTable = malloc(cantVertices*sizeof(Vertice));
	for(u32 i = 0; i < grafo->cantVertices; i++) {
		grafo->hashTable[i] = malloc(sizeof(struct vertice_t));
		grafo->hashTable[i]->inicializado = false;
	}
	grafo->ordenNatural = calloc(cantVertices, sizeof(Vertice));
	grafo->orden = malloc(cantVertices * sizeof(Vertice));
	grafo->vertUsados = calloc(cantVertices, sizeof(bool));
	//Devolver un puntero al grafo generado
	return grafo;
}

u32 gradoDelVertice(WinterIsHere grafo, u32 etiqueta) {
	return grafo->hashTable[etiqueta]->cantidadVecinos;
}


int insertarEnHash(WinterIsHere grafo, u32 nombre) {
	/*
	Define una posición i utilizando el modulo entre el nombre del vertice
	y la cantidad de vertices del grafo
	*/
	int posicion = nombre % grafo->cantVertices;
	u32 busquedas = 0;
	Vertice iesimoVertice;
	
	/*
	Recorre linealmente la tabla desde la posición i dada
	*/
	while(busquedas < grafo->cantVertices){
		//Comprueba que el iesimo lugar de la tabla no esté asignado
		if(!grafo->hashTable[posicion]->inicializado) {
			//En caso de no estarlo, inicializa el vertice "nombre" en esa posición
			Vertice vertice = grafo->hashTable[posicion];
			inicializarVertice(vertice, nombre, posicion);
			//Retorna la posición para terminar el ciclo
			return posicion;
		}
		else if (grafo->hashTable[posicion]->nombre == nombre){
			//En caso de ya estar en la tabla, devolver su posición
			return posicion;
		}
		else {
			//En caso de estar asignado:
			iesimoVertice = grafo->hashTable[posicion];
			//Probar en la siguiente posición
			if (iesimoVertice->nombre != nombre)
				posicion = (posicion + 1) % grafo->cantVertices;
			++busquedas;
		}
	}
	//Devuelve la posición de la tabla en que se inserto al vertice
	return posicion;
}

void agregarLado(WinterIsHere grafo, u32 nombreA, u32 nombreB) {
	int posicionA, posicionB;
	/*
	Comprobar que los vértices con nombres A y B estén en el grafo,
	si alguno no esté, crearlo, 
	y si estén, obtener su posición en la tabla
	*/

	//Primero para el vértice A
	posicionA = insertarEnHash(grafo, nombreA);

	//Luego para el vértice B
	posicionB = insertarEnHash(grafo, nombreB);

	Vertice verticeA = grafo->hashTable[posicionA];
	Vertice verticeB = grafo->hashTable[posicionB];
	/*
	Agrega el lado entre el vértice A y B
	Como el grafo NO es dirigido, agrega el lado entre B y A también
	*/
	agregarVecino(verticeA, verticeB);
	agregarVecino(verticeB, verticeA);
}

WinterIsHere cargarGrafo() {
	int tamanoLinea = 256;
	char linea[tamanoLinea];
	linea[0] = 'c';
	
	//Leer las primeras lineas (comentarios)
	while(linea[0] == 'c') {
		if(fgets(linea, tamanoLinea, stdin) == NULL) {
			printf("Error en el input, intente nuevamente\n");
			return NULL;
		}
	}

	/*
	Comprobar que luego de los comentarios siga una linea con el formato
	"p edge x y", donde 'x' es el número de vértices e 'y' el de lados
	*/
	if(linea[0] != 'p') {
		printf("Formato del input no corresponde a DIMACS\n");
		return NULL;
	}

	u32 cantVertices, cantLados;
	char comando;
	char edge[4];
	
	sscanf(linea,"%c %s %d %d", &comando, edge, &cantVertices, &cantLados);
	//En caso de no cumplir con el formato, devolver puntero a NULL
	if(strcmp(edge, "edge") != 0) {
		printf("Formato del input para grafo no corresponde a DIMACS\n");
		return NULL;
	}
	//En caso de haber lados y no haber vértices, devolver puntero a NULL
	if(cantVertices <= 0 && cantLados > 0) {
		printf("Formato del input para grafo no corresponde a DIMACS\n");
		return NULL;
	}

	//Crear el grafo con los parámetros dados
	WinterIsHere grafo = crearGrafo(cantVertices, cantLados);
	
	u32 nombreA, nombreB;
	//Parsear las n (= cantLados) lineas con lados siguientes
	for (u32 i = 0; i < cantLados; i++) {
		if (fgets(linea, sizeof(linea), stdin) != NULL) {
			sscanf(linea,"%c %u %u", &comando, &nombreA, &nombreB);
			//En caso de no cumplir el formato, devolver NULL
			if(comando != 'e') {
				printf("Formato del input para lados no corresponde a DIMACS\n");
				free(grafo);
				return NULL;
			}
			//Agregar el lado ingresado
			agregarLado(grafo, nombreA, nombreB);

		} else {
			printf("Error en el input, intente nuevamente\n");
			free(grafo);
			return NULL;
		}
	}
	//Eliminar memoria sobrante en los arrays de vecinos de los vértices
	Vertice vertice = NULL;
	for (u32 i = 0; i < grafo->cantVertices ; i++) {
		vertice = grafo->hashTable[i];
		optimizarMemoria(vertice);
	}
	//Devolver un puntero al grafo creado, con sus vértices y lados almacenados
	return grafo;
}

int destruirGrafo(WinterIsHere grafo) {
	//Liberar la memoria pedida para cada uno de los vértices
	for (u32 i = 0; i < grafo->cantVertices; i++) {
		destruirVertice(grafo->hashTable[i]);
	}
	//Liberar la memoria pedida para el arreglo de punteros a vértices
	free(grafo->hashTable);
	//Liberar la memoria pedida para la estructura del grafo
	free(grafo);

	return 1;
}

int main() {
	WinterIsHere grafo = cargarGrafo();
	destruirGrafo(grafo);
	return 0;
}