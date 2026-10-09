#include <iostream>
#include "Palabra.hpp"
using namespace std;

Palabra crearPalabra(Cadena texto)
{
	Palabra nueva = new nodoPalabra;

	nueva->texto = crearCadena(texto);
	nueva->siguiente = NULL;
	return nueva;
}

bool esPalabraValida(Cadena texto)
{
	unsigned int i = 0;
	bool valida = (largoCadena(texto) > 0);

	while (valida && texto[i] != '\0')
	{
		valida = !esBlanco(texto[i]);
		i++;
	}
	return valida;
}

bool listaPalabrasVacia(Palabra palabras)
{
	return (palabras == NULL);
}

unsigned int cantidadPalabras(Palabra palabras)
{
	unsigned int cantidad = 0;

	while (palabras != NULL)
	{
		cantidad++;
		palabras = palabras->siguiente;
	}
	return cantidad;
}

void insertarPalabraEnPos(Palabra &palabras, Palabra nueva, Posicion pos)
{
	Palabra anterior = NULL;
	Posicion actual = 0;

	if (pos <= 1 || listaPalabrasVacia(palabras))
	{
		nueva->siguiente = palabras;
		palabras = nueva;
	}
	else
	{
		anterior = palabras;
		actual = 2;   //posicion del nodo que sigue a 'anterior'
		while (actual < pos && anterior->siguiente != NULL)
		{
			anterior = anterior->siguiente;
			actual++;
		}
		nueva->siguiente = anterior->siguiente;
		anterior->siguiente = nueva;
	}
}

Palabra extraerUltimaPalabra(Palabra &palabras)
{
	Palabra ultima = NULL;
	Palabra anterior = NULL;

	if (!listaPalabrasVacia(palabras))
	{
		if (palabras->siguiente == NULL)
		{
			//hay una sola palabra: la lista queda vacia
			ultima = palabras;
			palabras = NULL;
		}
		else
		{
			//se busca el anteultimo nodo
			anterior = palabras;
			while (anterior->siguiente->siguiente != NULL)
			{
				anterior = anterior->siguiente;
			}
			ultima = anterior->siguiente;
			anterior->siguiente = NULL;
		}
	}
	return ultima;
}

void eliminarPalabraEnPos(Palabra &palabras, Posicion pos)
{
	Palabra anterior = NULL;
	Palabra aBorrar = NULL;
	Posicion actual = 0;

	if (pos == 1)
	{
		aBorrar = palabras;
		palabras = palabras->siguiente;
	}
	else
	{
		anterior = palabras;
		for (actual = 2; actual < pos; actual++)
		{
			anterior = anterior->siguiente;
		}
		aBorrar = anterior->siguiente;
		anterior->siguiente = aBorrar->siguiente;
	}
	liberarPalabra(aBorrar);
}

void liberarPalabra(Palabra &nodo)
{
	borrarCadena(nodo->texto);
	delete nodo;
	nodo = NULL;
}

void liberarPalabras(Palabra &palabras)
{
	Palabra aBorrar = NULL;

	while (palabras != NULL)
	{
		aBorrar = palabras;
		palabras = palabras->siguiente;
		liberarPalabra(aBorrar);
	}
}

void mostrarPalabras(Palabra palabras)
{
	while (palabras != NULL)
	{
		cout << palabras->texto;
		if (palabras->siguiente != NULL)
		{
			cout << " ";
		}
		palabras = palabras->siguiente;
	}
}
