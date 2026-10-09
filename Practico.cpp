#include <iostream>
#include "Practico.hpp"
using namespace std;

//la linea nueva (vacia) la crea quien llama, como crearNodo + insertarFinal en las listas de clase
TipoRetorno insertarLinea(Linea &texto, Linea nueva)
{
	insertarLineaFinal(texto, nueva);
	return OK;
}

TipoRetorno InsertarLineaEnPosicion(Linea &texto, Posicion posicionLinea)
{
	TipoRetorno ret = OK;

	//la posicion es valida si 1 <= posicionLinea <= cantidad de lineas + 1
	if (posicionLinea < 1 || posicionLinea > cantidadLineas(texto) + 1)
	{
		ret = ERROR;
	}
	else
	{
		insertarLineaEnPos(texto, crearLinea(), posicionLinea);
	}
	return ret;
}

TipoRetorno BorrarLinea(Linea &texto, Posicion posicionLinea)
{
	TipoRetorno ret = OK;

	//la posicion es valida si 1 <= posicionLinea <= cantidad de lineas
	if (posicionLinea < 1 || posicionLinea > cantidadLineas(texto))
	{
		ret = ERROR;
	}
	else
	{
		eliminarLineaEnPos(texto, posicionLinea);   //primero libera las palabras de la linea y despues la linea
	}
	return ret;
}

TipoRetorno BorrarTodo(Linea &texto)
{
	liberarTexto(texto);
	return OK;
}

TipoRetorno ImprimirTexto(Linea texto)
{
	if (textoVacio(texto))
	{
		cout << "Texto vacio" << endl;
	}
	else
	{
		mostrarTexto(texto);
	}
	return OK;
}

TipoRetorno InsertarPalabra(Linea &texto, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	if (linea == NULL)
	{
		ret = ERROR;   //la linea no existe en el texto
	}
	else if (posicionPalabra < 1 || posicionPalabra > cantidadPalabras(linea->palabras) + 1)
	{
		ret = ERROR;   //la posicion de la palabra no es valida
	}
	else if (!esPalabraValida(palabraAIngresar))
	{
		ret = ERROR;   //las palabras no pueden ser vacias ni tener espacios en blanco
	}
	else
	{
		insertarPalabraEnPos(linea->palabras, crearPalabra(palabraAIngresar), posicionPalabra);
		propagarExceso(linea);   //si la linea quedo con mas palabras que el maximo, el exceso pasa a las siguientes
	}
	return ret;
}

TipoRetorno BorrarPalabra(Linea &texto, Posicion posicionLinea, Posicion posicionPalabra)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	if (linea == NULL)
	{
		ret = ERROR;   //la linea no existe en el texto
	}
	else if (posicionPalabra < 1 || posicionPalabra > cantidadPalabras(linea->palabras))
	{
		ret = ERROR;   //la palabra no existe en la linea
	}
	else
	{
		eliminarPalabraEnPos(linea->palabras, posicionPalabra);
	}
	return ret;
}

TipoRetorno ImprimirLinea(Linea texto, Posicion posicionLinea)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	if (linea == NULL)
	{
		ret = ERROR;   //la linea no existe en el texto
	}
	else
	{
		mostrarLinea(linea, posicionLinea);
	}
	return ret;
}
