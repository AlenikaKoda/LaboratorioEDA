#include <iostream>
#include "Practico.hpp"
using namespace std;

//la linea nueva (vacia) la crea quien llama, como crearNodo e insertarFinal en las listas de clase
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
		//solo se reserva memoria cuando la posicion es valida
		insertarLineaEnPos(texto, crearLinea(), posicionLinea);
	}
	return ret;
}

TipoRetorno BorrarLinea(Linea &texto, Posicion posicionLinea)
{
	TipoRetorno ret = OK;

	//la posicion es valida si la linea existe, o sea 1 <= posicionLinea <= cantidad de lineas
	if (posicionLinea < 1 || posicionLinea > cantidadLineas(texto))
	{
		ret = ERROR;
	}
	else
	{
		//se liberan primero las palabras de la linea y despues la linea
		eliminarLineaEnPos(texto, posicionLinea);
	}
	return ret;
}

TipoRetorno BorrarTodo(Linea &texto)
{
	//libera todas las lineas con sus palabras, si el texto ya estaba vacio queda igual
	liberarTexto(texto);
	return OK;
}

TipoRetorno ImprimirTexto(Linea texto)
{
	//un texto sin lineas muestra un mensaje en vez de las lineas
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
	Palabra sobrante = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	//se verifica que la linea exista y que 1 <= posicionPalabra <= cantidad de palabras + 1
	if (linea == NULL)
	{
		ret = ERROR;   //la linea no existe en el texto
	}
	else if (posicionPalabra < 1 || posicionPalabra > cantidadPalabras(linea->palabras) + 1)
	{
		ret = ERROR;   //la posicion de la palabra no es valida
	}
	else
	{
		//el nodo guarda una copia de la palabra, asi que quien llama puede seguir usando la suya
		insertarPalabraEnPos(linea->palabras, crearPalabra(palabraAIngresar), posicionPalabra);
		//ejemplo con maximo 3: [A B C D] queda [A B C] y D pasa al inicio de la siguiente, que de [E F] pasa a [D E F]
		//mientras la linea tenga mas palabras que el maximo, su ultima palabra pasa a la linea siguiente
		while (cantidadPalabras(linea->palabras) > MAX_CANT_PALABRAS_X_LINEA)
		{
			sobrante = extraerUltimaPalabra(linea->palabras);
			//si era la ultima linea del texto se agrega una nueva al final
			if (linea->siguiente == NULL)
			{
				linea->siguiente = crearLinea();
			}
			//la sobrante pasa a ser la primera palabra de la linea siguiente, que se revisa en la proxima vuelta
			linea = linea->siguiente;
			insertarPalabraEnPos(linea->palabras, sobrante, 1);
		}
	}
	return ret;
}

TipoRetorno BorrarPalabra(Linea &texto, Posicion posicionLinea, Posicion posicionPalabra)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	//se verifica que la linea exista y que la palabra exista en la linea
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
		//las palabras siguientes de esa linea suben una posicion, no se traen palabras de otras lineas
		eliminarPalabraEnPos(linea->palabras, posicionPalabra);
	}
	return ret;
}

TipoRetorno ImprimirLinea(Linea texto, Posicion posicionLinea)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	//la posicion es valida si la linea existe en el texto
	if (linea == NULL)
	{
		ret = ERROR;
	}
	else
	{
		mostrarLinea(linea, posicionLinea);
	}
	return ret;
}
