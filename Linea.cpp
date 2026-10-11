#include <iostream>
#include "Linea.hpp"
using namespace std;

Linea crearLinea()
{
	Linea nueva = new nodoLinea;

	//la linea nueva no tiene palabras y todavia no esta enlazada a ninguna otra
	nueva->palabras = NULL;
	nueva->siguiente = NULL;
	return nueva;
}

bool textoVacio(Linea texto)
{
	return (texto == NULL);
}

unsigned int cantidadLineas(Linea texto)
{
	unsigned int cantidad = 0;

	//cuenta los nodos de la lista de lineas
	while (texto != NULL)
	{
		cantidad++;
		texto = texto->siguiente;
	}
	return cantidad;
}

Linea obtenerLinea(Linea texto, Posicion pos)
{
	Linea resultado = NULL;
	Posicion actual = 1;

	//la posicion 0 no existe
	if (pos >= 1)
	{
		//avanza hasta la posicion pedida o hasta el final del texto
		while (texto != NULL && actual < pos)
		{
			texto = texto->siguiente;
			actual++;
		}
		//si se llego al final sin encontrar la posicion el resultado es NULL
		resultado = texto;
	}
	return resultado;
}

void insertarLineaFinal(Linea &texto, Linea nueva)
{
	Linea aux = NULL;

	//con el texto vacio la nueva pasa a ser la primera linea
	if (textoVacio(texto))
	{
		texto = nueva;
	}
	else
	{
		//avanza hasta la ultima linea
		aux = texto;
		while (aux->siguiente != NULL)
		{
			aux = aux->siguiente;
		}
		//la nueva se enlaza a continuacion de la ultima
		aux->siguiente = nueva;
	}
}

void insertarLineaEnPos(Linea &texto, Linea nueva, Posicion pos)
{
	Linea anterior = NULL;

	//en la posicion 1 la nueva pasa a ser la primera linea del texto
	if (pos <= 1)
	{
		nueva->siguiente = texto;
		texto = nueva;
	}
	else
	{
		//se busca la linea anterior a la posicion y la nueva se enlaza entre esa linea y la que le seguia
		anterior = obtenerLinea(texto, pos - 1);
		nueva->siguiente = anterior->siguiente;
		anterior->siguiente = nueva;
	}
}

void eliminarLineaEnPos(Linea &texto, Posicion pos)
{
	Linea anterior = NULL;
	Linea aBorrar = NULL;

	//la primera linea se borra moviendo el inicio del texto a la segunda
	if (pos == 1)
	{
		aBorrar = texto;
		texto = texto->siguiente;
	}
	else
	{
		//se busca la linea anterior a la que se borra y se la enlaza con la que sigue a la borrada
		anterior = obtenerLinea(texto, pos - 1);
		aBorrar = anterior->siguiente;
		anterior->siguiente = aBorrar->siguiente;
	}
	liberarLinea(aBorrar);
}

void liberarLinea(Linea &linea)
{
	//primero se liberan las palabras de la linea y despues el nodo de la linea
	liberarPalabras(linea->palabras);
	delete linea;
	linea = NULL;
}

void liberarTexto(Linea &texto)
{
	Linea aBorrar = NULL;

	//libera las lineas de a una hasta vaciar el texto
	while (texto != NULL)
	{
		//se avanza antes de liberar para no perder el resto del texto
		aBorrar = texto;
		texto = texto->siguiente;
		liberarLinea(aBorrar);
	}
}

void mostrarLinea(Linea linea, Posicion numero)
{
	//una linea vacia muestra solo su numero
	cout << numero << ": ";
	mostrarPalabras(linea->palabras);
	cout << endl;
}

void mostrarTexto(Linea texto)
{
	Posicion numero = 1;

	//recorre las lineas numerandolas desde 1
	while (texto != NULL)
	{
		mostrarLinea(texto, numero);
		texto = texto->siguiente;
		numero++;
	}
}
