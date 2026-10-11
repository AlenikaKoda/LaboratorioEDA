#include <iostream>
#include "Linea.hpp"
using namespace std;

//crea el nodo de una linea vacia, sin palabras y sin enlazar a otra linea
Linea crearLinea()
{
	Linea nueva = new nodoLinea;

	//la linea nueva no tiene palabras y todavia no esta enlazada a ninguna otra
	nueva->palabras = NULL;
	nueva->siguiente = NULL;
	return nueva;
}

//devuelve true si el texto no tiene ninguna linea
bool textoVacio(Linea texto)
{
	return (texto == NULL);
}

//devuelve la cantidad de lineas del texto recorriendolo de principio a fin
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

//devuelve el nodo de la linea que esta en la posicion pos, la primera es la 1
//si la posicion no existe devuelve NULL, la posicion 0 tampoco existe
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

//inserta el nodo nueva como ultima linea del texto
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

//inserta el nodo nueva en la posicion pos del texto
//las lineas que estaban desde esa posicion quedan una posicion mas adelante
//precondicion: 1 <= pos <= cantidad de lineas + 1
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

//elimina la linea de la posicion pos y libera su memoria, incluidas sus palabras
//las lineas siguientes suben una posicion
//precondicion: 1 <= pos <= cantidad de lineas
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

//libera la memoria de una linea, primero sus palabras y despues el nodo
//deja el puntero en NULL
void liberarLinea(Linea &linea)
{
	//primero se liberan las palabras de la linea y despues el nodo de la linea
	liberarPalabras(linea->palabras);
	delete linea;
	linea = NULL;
}

//libera la memoria de todas las lineas del texto y de sus palabras
//el texto queda vacio
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

//muestra una linea con su numero y sus palabras, por ejemplo 2: hola mundo
//una linea vacia muestra solo su numero
void mostrarLinea(Linea linea, Posicion numero)
{
	//una linea vacia muestra solo su numero
	cout << numero << ": ";
	mostrarPalabras(linea->palabras);
	cout << endl;
}

//muestra todas las lineas del texto numeradas desde 1
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
