#include <iostream>
#include "Practico.hpp"
using namespace std;

//operacion 1 de la letra: inserta la linea nueva, que ya viene vacia, al final del texto
//nunca da error
//la linea la crea quien llama, como crearNodo e insertarFinal en las listas de clase
TipoRetorno insertarLinea(Linea &texto, Linea nueva)
{
	insertarLineaFinal(texto, nueva);
	return OK;
}

//operacion 2 de la letra: inserta una linea vacia en la posicion indicada, las lineas siguientes se corren una posicion
//devuelve ERROR si la posicion no cumple 1 <= posicionLinea <= cantidad de lineas + 1
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

//operacion 3 de la letra: borra la linea de la posicion indicada junto con sus palabras
//las lineas siguientes suben una posicion
//devuelve ERROR si la linea no existe en el texto
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

//operacion 4 de la letra: borra todas las lineas del texto con sus palabras
//nunca da error, si el texto ya estaba vacio queda igual
TipoRetorno BorrarTodo(Linea &texto)
{
	//libera todas las lineas con sus palabras, si el texto ya estaba vacio queda igual
	liberarTexto(texto);
	return OK;
}

//operacion 6 de la letra: muestra todas las lineas del texto con su numero y sus palabras
//si el texto no tiene lineas muestra Texto vacio
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

//operacion 8 de la letra: inserta la palabra en la linea posicionLinea y en la posicion posicionPalabra de esa linea
//las palabras siguientes de la linea se corren una posicion
//si la linea queda con mas palabras que MAX_CANT_PALABRAS_X_LINEA el exceso pasa a las lineas siguientes
//y si hace falta se agrega una linea nueva al final del texto
//devuelve ERROR si la linea no existe o si la posicion de la palabra no cumple 1 <= posicionPalabra <= cantidad de palabras + 1
TipoRetorno InsertarPalabra(Linea &texto, Posicion posicionLinea, Posicion posicionPalabra, Cadena palabraAIngresar)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;
	Palabra sobrante = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	//es ERROR si la linea no existe o si la posicion de la palabra no cumple 1 <= posicionPalabra <= cantidad de palabras + 1
	//la linea se verifica primero para no usarla cuando es NULL
	if (linea == NULL || posicionPalabra < 1 || posicionPalabra > cantidadPalabras(linea->palabras) + 1)
	{
		ret = ERROR;
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

//operacion 9 de la letra: borra la palabra de la posicion posicionPalabra de la linea posicionLinea
//las palabras siguientes de esa linea suben una posicion
//devuelve ERROR si la linea no existe o si la palabra no existe en la linea
TipoRetorno BorrarPalabra(Linea &texto, Posicion posicionLinea, Posicion posicionPalabra)
{
	TipoRetorno ret = OK;
	Linea linea = NULL;

	linea = obtenerLinea(texto, posicionLinea);
	//es ERROR si la linea no existe o si la palabra no existe en la linea, o sea 1 <= posicionPalabra <= cantidad de palabras
	//la linea se verifica primero para no usarla cuando es NULL
	if (linea == NULL || posicionPalabra < 1 || posicionPalabra > cantidadPalabras(linea->palabras))
	{
		ret = ERROR;
	}
	else
	{
		//las palabras siguientes de esa linea suben una posicion, no se traen palabras de otras lineas
		eliminarPalabraEnPos(linea->palabras, posicionPalabra);
	}
	return ret;
}

//operacion 11 de la letra: muestra la linea de la posicion indicada con su numero y sus palabras
//devuelve ERROR si la linea no existe en el texto
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

//operacion 16 de la letra: muestra las ultimas palabras ingresadas, siendo
//el maximo de palabras recordadas el numero indicado por la constante
//"MAX_CANT_ULTIMAS_PALABRAS"
//nunca falla, si no hay palabras se le muestra un mensaje al usuario
TipoRetorno ImprimirUltimasPalabras(Historial historial)
{
	mostrarHistorial(historial);
	return OK;
}
