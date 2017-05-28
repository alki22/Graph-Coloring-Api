#include "JonSnow.h"
//Macro que devuelve el máximo entre dos valores
#define MAX(a,b) (((a)>(b))?(a):(b))

Cola crearCola(u32 tamano) {
	//Asignar memoria inicial para la estructura
	Cola cola = malloc(1 * sizeof(struct cola_t));
	cola->vertices = malloc(tamano * sizeof(Vertice));
	//Valores iniciales
	cola->primero = -1;
	cola->ultimo = -1;
	//Devolver un puntero a la cola creada
	return cola;
}

bool estaVacia(Cola cola) {
	//Primer elemento igual a último elemento => cola vacía
	return(cola->primero == cola->ultimo);
}

void agregarACola(Cola cola, Vertice vertice) {
	//Reposicionar último elemento
	++cola->ultimo;
	//Asignar el vértice ingresado al mismo
	cola->vertices[cola->ultimo] = vertice;
}

Vertice Decolar(Cola cola) {
	//Si la cola está vacía, no devolver nada
	if(estaVacia(cola))
		return NULL;
	//Reposicionar primer vértice a la cola
	++cola->primero;
	Vertice vertice = cola->vertices[cola->primero];
	//Devolver el vértice
	return vertice;
}

int destruirCola(Cola cola) {
	free(cola->vertices);
	free(cola);
	//Devolver 1 si todo anduvo bien
	return 1;
}

int Bipartito(WinterIsHere W) {
    Vertice vertDelOrden;
    Vertice vertDeCola;
    Cola cola;
    u32 indice = 0;
    u32 cantVertices = W->cantVertices;
    // For para resetear los colores de los vertices
    for(u32 i = 0; i < cantVertices; ++i) {
        W->orden[i]->color = 0;
    }

    u32 vertColoreados = 0;

    while (vertColoreados < cantVertices) {
        vertDelOrden = W->orden[indice];
        if(vertDelOrden->color == 0) {
            vertDelOrden->color = 1;
            vertColoreados++;
            cola = crearCola(cantVertices);
            agregarACola(cola, vertDelOrden);
            // While para desencolar q
            while(!estaVacia(cola)) {
                vertDeCola = Decolar(cola);
                // For para recorrer los vecino.
                for(u32 i = 0; i < vertDeCola->cantVecinos; i++) {
                    // Si el vecino no tiene color, se encola y se colorea.
                    if(vertDeCola->vecinos[i]->color == 0) {
                        agregarACola(cola, vertDeCola->vecinos[i]);
                        vertDeCola->vecinos[i]->color = (3 - vertDeCola->color);
                        //aumento los vertices coloreados
                        vertColoreados++;
                    }
                    // Si un vecino ya tenia el mismo color entonces no es bipartito. Hago return 0
                    else if (vertDeCola->color == vertDeCola->vecinos[i]->color) {
                        destruirCola(cola);
                        return 0;
                    }
                }
            }
            destruirCola(cola);
        }
        indice++;
    }
    Vertice vertice;
    // For que revisa que sea un coloreo propio.
    for(u32 i = 0; i < cantVertices; i++) {
        vertice = W->orden[i];
        for(u32 j = 0; j < vertice->cantVecinos; j++) {
            if(vertice->color == vertice->vecinos[j]->color)
                return 0;
        }
    }

    return 1;
}


u32 Greedy(WinterIsHere W) {
	u32 cantVertices = W->cantVertices;
	u32 colorMayor = 0;
	/* 
	cantVertices + 1 colores porque el 0 es el valor default del color
	y quedaría más feo que el codigo estuviera lleno de +1 para los colores
	*/
	bool coloresUsados[cantVertices + 1];
	//Inicializar todos los colores usados en 'false' (Todavía no se usó ninguno)
	for (u32 i = 0; i < cantVertices + 1; ++i) {
		coloresUsados[i] = false;
	}
	//Descolorear el grafo
	for(u32 i = 0; i < cantVertices; ++i) {
		W->hashTable[i]->color = 0;
	}
	//Tomar el primer vértice y colorearlo de color 1
	Vertice vertice = W->orden[0];
	vertice->color = 1;

	u32 color, cantVecinos;
	//Recorrer linealmente los vértices del orden del grafo
	for(u32 i = 1; i < cantVertices; ++i) {
		vertice = W->orden[i];
		cantVecinos = vertice->cantVecinos;
		//Buscar los colores de los vecinos y marcarlos como usados
		for(u32 j = 0; j < cantVecinos; ++j) {
			color = vertice->vecinos[j]->color;
			if (color)
				coloresUsados[color] = true;
		}
		//Encontrar el primer color disponible
		for (u32 j = 1; j < cantVertices + 1; j++) {
	        if (!coloresUsados[j]) {
	            //Colorear el vértice con dicho color y terminar el ciclo
	            vertice->color = j;
	            colorMayor = MAX(colorMayor, j);
	            break;
	        }
	    }
	    //Reinicializar todos los valores de coloresUsados a 'false'
		for(u32 m = 0; m < cantVecinos; ++m) {
			color = vertice->vecinos[m]->color;
			if (color)
				coloresUsados[color] = false;
		}
	}	
	//Guardar en el grafo la cantidad de colores usados
	W->cantColores = colorMayor;
	//Devolver dicha cantidad
	return colorMayor;	
}