#include <iostream>
#include "Linea.hpp"
using namespace std;

Linea crearLinea()
{
	Linea nueva = new nodoLinea;

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

	if (pos >= 1)
	{
		while (texto != NULL && actual < pos)
		{
			texto = texto->siguiente;
			actual++;
		}
		resultado = texto;
	}
	return resultado;
}

void insertarLineaFinal(Linea &texto, Linea nueva)
{
	Linea aux = NULL;

	if (textoVacio(texto))
	{
		texto = nueva;
	}
	else
	{
		aux = texto;
		while (aux->siguiente != NULL)
		{
			aux = aux->siguiente;
		}
		aux->siguiente = nueva;
	}
}

void insertarLineaEnPos(Linea &texto, Linea nueva, Posicion pos)
{
	Linea anterior = NULL;

	if (pos <= 1)
	{
		nueva->siguiente = texto;
		texto = nueva;
	}
	else
	{
		anterior = obtenerLinea(texto, pos - 1);
		nueva->siguiente = anterior->siguiente;
		anterior->siguiente = nueva;
	}
}

void eliminarLineaEnPos(Linea &texto, Posicion pos)
{
	Linea anterior = NULL;
	Linea aBorrar = NULL;

	if (pos == 1)
	{
		aBorrar = texto;
		texto = texto->siguiente;
	}
	else
	{
		anterior = obtenerLinea(texto, pos - 1);
		aBorrar = anterior->siguiente;
		anterior->siguiente = aBorrar->siguiente;
	}
	liberarLinea(aBorrar);
}

void propagarExceso(Linea linea)
{
	Palabra sobrante = NULL;

	//mientras la linea tenga mas palabras que el maximo, la ultima pasa al inicio de la siguiente
	while (cantidadPalabras(linea->palabras) > MAX_CANT_PALABRAS_X_LINEA)
	{
		sobrante = extraerUltimaPalabra(linea->palabras);
		if (linea->siguiente == NULL)
		{
			linea->siguiente = crearLinea();   //era la ultima linea del texto: se agrega una nueva al final
		}
		linea = linea->siguiente;
		insertarPalabraEnPos(linea->palabras, sobrante, 1);
	}
}

void liberarLinea(Linea &linea)
{
	liberarPalabras(linea->palabras);
	delete linea;
	linea = NULL;
}

void liberarTexto(Linea &texto)
{
	Linea aBorrar = NULL;

	while (texto != NULL)
	{
		aBorrar = texto;
		texto = texto->siguiente;
		liberarLinea(aBorrar);
	}
}

void mostrarLinea(Linea linea, Posicion numero)
{
	cout << numero << ": ";
	mostrarPalabras(linea->palabras);
	cout << endl;
}

void mostrarTexto(Linea texto)
{
	Posicion numero = 1;

	while (texto != NULL)
	{
		mostrarLinea(texto, numero);
		texto = texto->siguiente;
		numero++;
	}
}
