#include "JonSnow.h"

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

void ordenarPorBloques(WinterIsHere W, u32 colores[], u32 cantColores) {
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
	//Asignar el nuevo orden como orden del grafo
	W->orden = nuevoOrden;
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
	//Crear array con los colores del grafo
	u32 colores[W->cantColores];
	u32 vecesColor[W->cantColores];
	u32 temp;
	/*
	Llenar el array con 1,2,...,cantColores 
	e inicializar con 0 la cantidad de grafos 
	coloreados de cada color
	*/
	for (u32 i = 0; i < W->cantColores; ++i) {
		colores[i] = i+1;
		vecesColor[i] = 0;
	}
	//Llenar vecesColor
	for (u32 i = 0; i < W->cantColores; ++i) {
		for(u32 j = 0; j < W->cantVertices; ++j) {
			if (W->orden[j]->color == colores[i])
				++vecesColor[i];
		}
	}
	//Recorrer vecesColor cantColor - 1 veces
	for(u32 i = 0; i < W->cantColores; ++i) {
		for(u32 j = i + 1; j < W->cantColores; j++) {
			/*
			Si el siguiente color aparece menos veces,
			cambiarlos de lugar 
			(al color y a la cantidad de veces que sale)
			*/
			if(vecesColor[i] > vecesColor[j]) {
				temp = vecesColor[i];
				vecesColor[i] = vecesColor[j];
				vecesColor[j] = temp;
				temp = colores[i];
				colores[i] =  colores[j];
				colores[j] = temp;
			}
		}
	}
	//Ordenar según el nuevo orden de colores
	ordenarPorBloques(W, colores, W->cantColores);

}

void funcionTres(WinterIsHere W) {
	//Crear array con los colores del grafo
	u32 colores[W->cantColores];
	u32 vecesColor[W->cantColores];
	u32 temp;
	/*
	Llenar el array con 1,2,...,cantColores 
	e inicializar con 0 la cantidad de grafos 
	coloreados de cada color
	*/
	for (u32 i = 0; i < W->cantColores; ++i) {
		colores[i] = i+1;
		vecesColor[i] = 0;
	}
	//Llenar vecesColor
	for (u32 i = 0; i < W->cantColores; ++i) {
		for(u32 j = 0; j < W->cantVertices; ++j) {
			if (W->orden[j]->color == colores[i])
				++vecesColor[i];
		}
	}
	//Recorrer vecesColor cantColor - 1 veces
	for(u32 i = 0; i < W->cantColores; ++i) {
		for(u32 j = i + 1; j < W->cantColores; j++) {
			/*
			Si el siguiente color aparece menos veces,
			cambiarlos de lugar 
			(al color y a la cantidad de veces que sale)
			*/
			if(vecesColor[i] < vecesColor[j]) {
				temp = vecesColor[i];
				vecesColor[i] = vecesColor[j];
				vecesColor[j] = temp;
				temp = colores[i];
				colores[i] =  colores[j];
				colores[j] = temp;
			}
		}
	}
	//Ordenar según el nuevo orden de colores
	ordenarPorBloques(W, colores, W->cantColores);

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
	mezclarVertices(W->orden, W->cantVertices, x);
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