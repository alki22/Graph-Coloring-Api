#include "JonSnow.h"

u32 *verticesDelColor;
u32 *ordenDeColores;

int compOrdenNatural(const void *a, const void *b) {
	//Casteo
	Vertice verticeA = *(Vertice*)a;
	Vertice verticeB = *(Vertice*)b;
	//Comparación
	if (verticeA->nombre > verticeB->nombre)
		return 1;
	else
		return -1;
}

int compWelshPowell(const void *a, const void *b) {
	//Casteo
	Vertice verticeA = *(Vertice*)a;
	Vertice verticeB = *(Vertice*)b;
	//Comparación
	if (verticeA->cantVecinos > verticeB->cantVecinos)
		return -1;
	else if (verticeA->cantVecinos == verticeB->cantVecinos)
		return 0;
	else
		return 1;
}

int compFuncionDos(const void *a, const void *b) {
	//Casteo
	Vertice verticeA = *(Vertice*)a;
	Vertice verticeB = *(Vertice*)b;
	//Comparación
	if (verticesDelColor[verticeA->color] < verticesDelColor[verticeB->color])
		return -1;
	else if (verticesDelColor[verticeA->color] == verticesDelColor[verticeB->color]) {
		if (verticeA->color == verticeB->color)
			return 0;
		else if (verticeA->color > verticeB->color)
			return -1;
		else
			return 1;
	}
	else
		return 1;
}

int compFuncionTres(const void *a, const void *b) {
	//Casteo
	Vertice verticeA = *(Vertice*)a;
	Vertice verticeB = *(Vertice*)b;
	//Comparación
	if (verticesDelColor[verticeA->color] > verticesDelColor[verticeB->color])
		return -1;
	else if (verticesDelColor[verticeA->color] == verticesDelColor[verticeB->color]) {
		if (verticeA->color == verticeB->color)
			return 0;
		else if (verticeA->color > verticeB->color)
			return -1;
		else
			return 1;
	}
	else
		return 1;
}

void mezclarColores(u32 *array, u32 tamano, u32 semilla) {
	//Da una permutación de un arreglo de u32 y depende determinísticamente de x
	srand(semilla);
	if (tamano > 1) {
		for (u32 i = 0; i < tamano - 1; ++i) {
			u32 j = (i + rand()) / ((RAND_MAX / (tamano - i)) + 1);
			u32 temp = array[j];
			array[j] = array[i];
			array[i] = temp;
		}
	}
}

void mezclarVertices(Vertice *array, u32 tamano, u32 semilla) {
	//Da una permutación de un arreglo de vértices y depende determinísticamente de x
	srand(semilla);
	if (tamano > 1) {
		for (u32 i = 0; i < tamano; ++i) {
			u32 j = (i + rand()) / ((RAND_MAX / (tamano - i)) + 1);
			Vertice temp = array[j];
			array[j] = array[i];
			array[i] = temp;
		}
	}
}

void ordenarPorBloques(WinterIsHere W, u32 *colores, u32 cantColores) {
	u32 tamano = W->cantVertices;
	Vertice *nuevoOrden = malloc(tamano * sizeof(Vertice));
	//Copiar el orden actual en el nuevo orden
	memcpy(nuevoOrden, W->orden, tamano * sizeof(Vertice));
	u32 posicion = 0;
	u32 i = 0;
	Vertice temp;
	//Buscar linealmente para cada color:
	while (i < cantColores - 1 && posicion < tamano - 1) {
		//Para cada vértice en el orden:
		for(u32 j = 0; j < tamano; ++j) {
			/*
			Si su color coincide con el del color actual,
			swapear ese elemento con el que se encuentra en el lugar 'posicion'
			e incrementar posicion
			*/
			if (nuevoOrden[j]->color == colores[i]) {
				temp = nuevoOrden[posicion];
				nuevoOrden[posicion] = nuevoOrden[j];
				nuevoOrden[j] = temp;
				++posicion;
			}
		}
		++i;
	}
	memcpy(W->orden, nuevoOrden, tamano * sizeof(Vertice));
	free(nuevoOrden);
}

void funcionCero(WinterIsHere W) {
	//Crear array con los colores del grafo
	u32 array[W->cantColores];
	//Llenar el array con 1,2,...,cantColores
	for (u32 i = 0; i < W->cantColores; ++i) {
		array[i] = i+1;
	}
	//Guardar el último elemento
	u32 temp = array[W->cantColores-1];
	//Mover el resto un lugar hacia la izquierda
	for(u32 i = W->cantColores - 1; i>0; i--)
		array[i] = array[i-1];
	//Poner el último elemento al principio
	array[0] = temp;
	//Ordenar según el nuevo orden de colores
	ordenarPorBloques(W, array, W->cantColores);
}

void funcionUno(WinterIsHere W) {
	//Crear array con los colores del grafo
	u32 array[W->cantColores];
	//Llenar el array con 1,2,...,cantColores
	for (u32 i = 0; i < W->cantColores; ++i) {
		array[i] = i+1;
	}
	//Guardar los últimos dos elementos
	u32 temp1 = array[W->cantColores-1];
	u32 temp2 = array[W->cantColores-2];
	//Mover el resto un lugar hacia la izquierda
	for(u32 i = W->cantColores - 1; i > 1; i--)
		array[i] = array[i-2];
	//Poner los últimos elementos al principio en espejo
	array[0] = temp1;
	array[1] = temp2;
	//Ordenar según el nuevo orden de colores
	ordenarPorBloques(W, array, W->cantColores);
}

void funcionDos(WinterIsHere W) {
	verticesDelColor = calloc(W->cantColores + 1, sizeof(u32));
	for(u32 i = 0; i < W->cantVertices; ++i) {
		//Contar la cantidad de vértices de cada color
		u32 color = W->orden[i]->color;
		++verticesDelColor[color];
	}
	//Ordenar en función de dichas cantidades
	qsort(W->orden, W->cantVertices, sizeof(Vertice), compFuncionDos);
	
	free(verticesDelColor);
}

void funcionTres(WinterIsHere W) {
	verticesDelColor = calloc(W->cantColores + 1, sizeof(u32));
	for(u32 i = 0; i < W->cantVertices; ++i) {
		//Contar la cantidad de vértices de cada color
		u32 color = W->orden[i]->color;
		++verticesDelColor[color];
	}
	//Ordenar en función de dichas cantidades
	qsort(W->orden, W->cantVertices, sizeof(Vertice), compFuncionTres);
	
	free(verticesDelColor);
}

void funcionMayorTres(WinterIsHere W, u32 x) {
	//Crear array con los colores del grafo
	u32 array[W->cantColores];
	//Llenar el array con 1,2,...,cantColores
	for (u32 i = 0; i < W->cantColores; ++i) {
		array[i] = i+1;
	}
	//Mezclar el array de colores determinísticamente
	mezclarColores(array, W->cantColores, x);
	//Ordenar según el nuevo orden de colores
	ordenarPorBloques(W, array, W->cantColores);
}

void OrdenNatural(WinterIsHere W) {
	qsort(W->orden, W->cantVertices, sizeof(Vertice), compOrdenNatural);
}

void OrdenWelshPowell(WinterIsHere W) {
	qsort(W->orden, W->cantVertices, sizeof(Vertice), compWelshPowell);
}

void AleatorizarVertices(WinterIsHere W, u32 x) {
	srand(x);
	if (W->cantVertices > 1) {
		// Pedir memoria para el nuevo orden
		Vertice* nuevoOrden = malloc(W->cantVertices * sizeof(Vertice));
		// Copiar el orden inicial de la hash (Orden en que se insertaron los vértices) 
		memcpy(nuevoOrden, W->hashTable, W->cantVertices * sizeof(Vertice));
		
		for (u32 i = 0; i < W->cantVertices; ++i) {
			u32 j = (i + rand()) / ((RAND_MAX / (W->cantVertices - i)) + 1);
			Vertice temp = nuevoOrden[j];
			nuevoOrden[j] = nuevoOrden[i];
			nuevoOrden[i] = temp;
		}
		// Reemplazar el orden del grafo por el que se generó
		W->orden = nuevoOrden;
	}
}

void ReordenManteniendoBloqueColores(WinterIsHere W,u32 x) {
	switch (x) {
		case 0:
			funcionCero(W);
			break;
		case 1:
			funcionUno(W);
			break;
		case 2:
			funcionDos(W);
			break;
		case 3:
			funcionTres(W);
			break;
		default:
			funcionMayorTres(W, x);
	}
}