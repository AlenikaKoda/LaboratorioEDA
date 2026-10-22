#include <iostream>
#include <string.h>
#include "Palabra.hpp"
using namespace std;

//crea un nodo de palabra con una copia de la cadena recibida
//el nodo queda sin enlazar y se hace cargo de la memoria de su copia
Palabra crearPalabra(Cadena texto)
{
	Palabra nueva = new nodoPalabra;

	//el nodo guarda una copia de la palabra para hacerse cargo de su propia memoria
	nueva->texto = new char[largoCadena(texto) + 1];   //+1 para el '\0'
	strcpy(nueva->texto, texto);
	nueva->siguiente = NULL;
	return nueva;
}

//devuelve true si la lista de palabras no tiene ningun nodo
bool listaPalabrasVacia(Palabra palabras)
{
	return (palabras == NULL);
}

//devuelve la cantidad de palabras de la lista recorriendola de principio a fin
unsigned int cantidadPalabras(Palabra palabras)
{
	unsigned int cantidad = 0;

	//cuenta los nodos de la lista
	while (palabras != NULL)
	{
		cantidad++;
		palabras->texto;
		palabras = palabras->siguiente;
	}
	return cantidad;
}

//inserta el nodo nueva en la posicion pos de la lista
//las palabras que estaban desde esa posicion quedan una posicion mas adelante
//precondicion: 1 <= pos <= cantidad de palabras + 1
void insertarPalabraEnPos(Palabra &palabras, Palabra nueva, Posicion pos)
{
	Palabra anterior = NULL;
	Posicion actual = 0;

	//en la posicion 1 o con la lista vacia la nueva pasa a ser la primera palabra
	if (pos <= 1 || listaPalabrasVacia(palabras))
	{
		//la nueva apunta a la primera palabra actual y pasa a ser la primera
		nueva->siguiente = palabras;
		palabras = nueva;
	}
	else
	{
		anterior = palabras;
		actual = 2;   //posicion del nodo que sigue a anterior
		//avanza hasta el nodo anterior a la posicion de insercion
		while (actual < pos && anterior->siguiente != NULL)
		{
			anterior = anterior->siguiente;
			actual++;
		}
		//la nueva se enlaza a continuacion de anterior y antes del nodo que le seguia
		nueva->siguiente = anterior->siguiente;
		anterior->siguiente = nueva;
	}
}

//quita el ultimo nodo de la lista y lo devuelve sin liberarlo, si la lista esta vacia devuelve NULL
//se usa para pasar la palabra sobrante de una linea llena a la linea siguiente
Palabra extraerUltimaPalabra(Palabra &palabras)
{
	Palabra ultima = NULL;
	Palabra anterior = NULL;

	//si la lista esta vacia no hay nada para extraer y se devuelve NULL
	if (!listaPalabrasVacia(palabras))
	{
		//con una sola palabra la lista queda vacia
		if (palabras->siguiente == NULL)
		{
			ultima = palabras;
			palabras = NULL;
		}
		else
		{
			//busca el anteultimo nodo, el que apunta al ultimo
			anterior = palabras;
			while (anterior->siguiente->siguiente != NULL)
			{
				anterior = anterior->siguiente;
			}
			//el ultimo se desengancha y el anteultimo pasa a ser el final de la lista
			ultima = anterior->siguiente;
			anterior->siguiente = NULL;
		}
	}
	return ultima;
}

//elimina el nodo de la posicion pos y libera su memoria
//las palabras siguientes suben una posicion
//precondicion: 1 <= pos <= cantidad de palabras
void eliminarPalabraEnPos(Palabra &palabras, Posicion pos)
{
	Palabra anterior = NULL;
	Palabra aBorrar = NULL;
	Posicion actual = 0;

	//la primera palabra se borra moviendo el inicio de la lista a la segunda
	if (pos == 1)
	{
		aBorrar = palabras;
		palabras = palabras->siguiente;
	}
	else
	{
		//avanza hasta el nodo anterior al que se va a borrar
		anterior = palabras;
		for (actual = 2; actual < pos; actual++)
		{
			anterior = anterior->siguiente;
		}
		//anterior se enlaza con el nodo que sigue al borrado para sacarlo de la lista
		aBorrar = anterior->siguiente;
		anterior->siguiente = aBorrar->siguiente;
	}
	liberarPalabra(aBorrar);
}

//libera la memoria de un solo nodo, primero su cadena y despues el nodo
//deja el puntero en NULL
void liberarPalabra(Palabra &nodo)
{
	//primero se libera la cadena con delete[] porque se reservo con new[] y despues el nodo
	delete[] nodo->texto;
	delete nodo;
	nodo = NULL;
}

//libera la memoria de todos los nodos de la lista
//la lista queda vacia
void liberarPalabras(Palabra &palabras)
{
	Palabra aBorrar = NULL;

	//libera los nodos de a uno hasta vaciar la lista
	while (palabras != NULL)
	{
		//se avanza antes de liberar para no perder el resto de la lista
		aBorrar = palabras;
		palabras = palabras->siguiente;
		liberarPalabra(aBorrar);
	}
}

//muestra las palabras de la lista en orden separadas por un espacio
//no deja espacio despues de la ultima palabra
void mostrarPalabras(Palabra palabras)
{
	//recorre la lista mostrando cada palabra
	while (palabras != NULL)
	{
		cout << palabras->texto;
		//el espacio va solo entre palabras, no despues de la ultima
		if (palabras->siguiente != NULL)
		{
			cout << " ";
		}
		palabras = palabras->siguiente;
	}
}
