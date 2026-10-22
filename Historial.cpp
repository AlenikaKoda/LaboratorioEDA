#include <iostream>
#include "Historial.hpp"
using namespace std;

//agrega un nuevo nodo de palabra al inicio de la lista del historial
//si la cantidad de palabras guardadas supera el maximo indicada por la 
//constante MAX_CANT_ULTIMAS_PALABRAS, se elimina el ultimo nodo de la lista 
//(la palabra mas antigua)
void agregarPalabraHistorial(Palabra &his, Palabra nueva)
{
	//punteros auxiliares para borrar el ultimo nodo
	Palabra borrar = NULL;
	Palabra aux = NULL;
	
	//el nuevo nodo apunta a lo que sea que este apuntando la cabeza de la lista
	//actualmente, ya sea NULL u otro nodo.
	nueva->siguiente = his;
	his = nueva; //el nuevo nodo pasa a ser la cabeza
	
	//si se supero el limite de palabras guardadas, se elimina la mas antigua
	if (cantidadPalabras(his) > MAX_CANT_ULTIMAS_PALABRAS)
	{
		aux = his;
		
		//se mueve el puntero auxiliar hasta el ante-ultimo nodo
		while (aux->siguiente->siguiente != NULL)
		{
			aux = aux->siguiente;
		}
		
		borrar = aux->siguiente; //guarda la direccion del ultimo nodo
		aux->siguiente = NULL; //el ante-ultimo nodo pasa a apuntar a NULL
		
		liberarPalabra(borrar); //se elimina en ultimo nodo
	}
}

//Muestra las palabras guardadas en el historial
void mostrarHistorial(Palabra his)
{
	while (his != NULL)
	{
		cout << his->texto << endl;
		his = his->siguiente;
	}
}

//libera la memoria del historial
//nunca da error, si el historial esta vacio se deja asi
void BorrarHistorial(Palabra &his)
{
	liberarPalabras(his);
}
