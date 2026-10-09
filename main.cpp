#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Tipos.hpp"
#include "Linea.hpp"
#include "Practico.hpp"
using namespace std;

#define MAX_LARGO_ENTRADA 256   //largo maximo de una linea de entrada (comando + argumentos, incluye el '\0')

//lee una linea completa (hasta el enter): el comando y sus argumentos vienen juntos en la misma linea.
//Devuelve false cuando se acaba la entrada. Si la linea no entra en el buffer, se avisa y se descarta completa.
bool leerEntrada(char entrada[])
{
	int caracter = getchar();
	unsigned int largo = 0;
	bool hayEntrada = (caracter != EOF);
	bool demasiadoLarga = false;

	while (caracter != '\n' && caracter != EOF)
	{
		if (largo < MAX_LARGO_ENTRADA - 1)
		{
			entrada[largo] = (char) caracter;
			largo++;
		}
		else
		{
			demasiadoLarga = true;   //no entra en el buffer: se sigue leyendo hasta el enter, pero se descarta
		}
		caracter = getchar();
	}
	entrada[largo] = '\0';
	if (demasiadoLarga)
	{
		cout << "Linea demasiado larga" << endl;
		entrada[0] = '\0';
	}
	return hayEntrada;
}

//muestra el resultado de una operacion (si fue OK no muestra nada)
void mostrarRetorno(TipoRetorno ret)
{
	if (ret == ERROR)
	{
		cout << "ERROR" << endl;
	}
	else if (ret == NO_IMPLEMENTADA)
	{
		cout << "NO_IMPLEMENTADA" << endl;
	}
}

void mostrarParametrosInvalidos()
{
	cout << "Parametros invalidos" << endl;
}

//separa la linea en el comando (primera palabra) y sus argumentos (el resto, sin blancos en los extremos)
void separarComando(Cadena entrada, Cadena &comando, Cadena &argumentos)
{
	Cadena fin = NULL;

	comando = recortarCadena(entrada);
	fin = comando;
	while (*fin != '\0' && !esBlanco(*fin))
	{
		fin++;
	}
	if (*fin == '\0')
	{
		argumentos = fin;   //la linea solo tiene el comando: los argumentos son la cadena vacia
	}
	else
	{
		*fin = '\0';   //termina el comando
		argumentos = recortarCadena(fin + 1);
	}
}

//devuelve true si el comando no trae argumentos
bool sinArgumentos(Cadena argumentos)
{
	return (argumentos[0] == '\0');
}

//argumentos con formato "pos" (se ignoran los blancos alrededor de cada argumento)
bool obtenerUnaPosicion(Cadena argumentos, Posicion &pos)
{
	Cadena token = strtok(argumentos, ",");
	bool valido = false;

	if (token != NULL)
	{
		token = recortarCadena(token);
		valido = (esNumero(token) && strtok(NULL, ",") == NULL);
	}
	if (valido)
	{
		pos = cadenaAPosicion(token);
	}
	return valido;
}

//argumentos con formato "pos1,pos2"
bool obtenerDosPosiciones(Cadena argumentos, Posicion &pos1, Posicion &pos2)
{
	Cadena token1 = strtok(argumentos, ",");
	Cadena token2 = strtok(NULL, ",");
	bool valido = false;

	if (token1 != NULL && token2 != NULL)
	{
		token1 = recortarCadena(token1);
		token2 = recortarCadena(token2);
		valido = (esNumero(token1) && esNumero(token2) && strtok(NULL, ",") == NULL);
	}
	if (valido)
	{
		pos1 = cadenaAPosicion(token1);
		pos2 = cadenaAPosicion(token2);
	}
	return valido;
}

//argumentos con formato "posLinea,posPalabra,palabra"
bool obtenerPosicionesYPalabra(Cadena argumentos, Posicion &posLinea, Posicion &posPalabra, Cadena &palabra)
{
	Cadena token1 = strtok(argumentos, ",");
	Cadena token2 = strtok(NULL, ",");
	Cadena token3 = strtok(NULL, "");   //lo que queda de los argumentos es la palabra (puede llevar comas)
	bool valido = false;

	if (token1 != NULL && token2 != NULL && token3 != NULL)
	{
		token1 = recortarCadena(token1);
		token2 = recortarCadena(token2);
		token3 = recortarCadena(token3);
		valido = (esNumero(token1) && esNumero(token2) && largoCadena(token3) > 0);
	}
	if (valido)
	{
		posLinea = cadenaAPosicion(token1);
		posPalabra = cadenaAPosicion(token2);
		palabra = token3;
	}
	return valido;
}

void comandoInsertarLinea(Linea &texto, Cadena argumentos)
{
	if (sinArgumentos(argumentos))
	{
		mostrarRetorno(insertarLinea(texto, crearLinea()));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoInsertarLineaEnPosicion(Linea &texto, Cadena argumentos)
{
	Posicion posLinea = 0;

	if (obtenerUnaPosicion(argumentos, posLinea))
	{
		mostrarRetorno(InsertarLineaEnPosicion(texto, posLinea));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoBorrarLinea(Linea &texto, Cadena argumentos)
{
	Posicion posLinea = 0;

	if (obtenerUnaPosicion(argumentos, posLinea))
	{
		mostrarRetorno(BorrarLinea(texto, posLinea));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoBorrarTodo(Linea &texto, Cadena argumentos)
{
	if (sinArgumentos(argumentos))
	{
		mostrarRetorno(BorrarTodo(texto));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoImprimirTexto(Linea texto, Cadena argumentos)
{
	if (sinArgumentos(argumentos))
	{
		mostrarRetorno(ImprimirTexto(texto));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoInsertarPalabra(Linea &texto, Cadena argumentos)
{
	Posicion posLinea = 0;
	Posicion posPalabra = 0;
	Cadena palabra = NULL;

	if (obtenerPosicionesYPalabra(argumentos, posLinea, posPalabra, palabra))
	{
		mostrarRetorno(InsertarPalabra(texto, posLinea, posPalabra, palabra));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoBorrarPalabra(Linea &texto, Cadena argumentos)
{
	Posicion posLinea = 0;
	Posicion posPalabra = 0;

	if (obtenerDosPosiciones(argumentos, posLinea, posPalabra))
	{
		mostrarRetorno(BorrarPalabra(texto, posLinea, posPalabra));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

void comandoImprimirLinea(Linea texto, Cadena argumentos)
{
	Posicion posLinea = 0;

	if (obtenerUnaPosicion(argumentos, posLinea))
	{
		mostrarRetorno(ImprimirLinea(texto, posLinea));
	}
	else
	{
		mostrarParametrosInvalidos();
	}
}

//ejecuta el comando con sus argumentos; devuelve false si no es un comando conocido
bool ejecutarComando(Linea &texto, Cadena comando, Cadena argumentos)
{
	bool reconocido = true;

	if (cadenasIguales(comando, "InsertarLinea"))
	{
		comandoInsertarLinea(texto, argumentos);
	}
	else if (cadenasIguales(comando, "InsertarLineaEnPosicion"))
	{
		comandoInsertarLineaEnPosicion(texto, argumentos);
	}
	else if (cadenasIguales(comando, "BorrarLinea"))
	{
		comandoBorrarLinea(texto, argumentos);
	}
	else if (cadenasIguales(comando, "BorrarTodo"))
	{
		comandoBorrarTodo(texto, argumentos);
	}
	else if (cadenasIguales(comando, "ImprimirTexto"))
	{
		comandoImprimirTexto(texto, argumentos);
	}
	else if (cadenasIguales(comando, "InsertarPalabra"))
	{
		comandoInsertarPalabra(texto, argumentos);
	}
	else if (cadenasIguales(comando, "BorrarPalabra"))
	{
		comandoBorrarPalabra(texto, argumentos);
	}
	else if (cadenasIguales(comando, "ImprimirLinea"))
	{
		comandoImprimirLinea(texto, argumentos);
	}
	else
	{
		reconocido = false;
	}
	return reconocido;
}

int main()
{
	Linea texto = NULL;   //al iniciar el texto es vacio (0 lineas)
	char entrada[MAX_LARGO_ENTRADA];
	Cadena comando = NULL;
	Cadena argumentos = NULL;
	bool salir = false;

	//termina al leer "Salir" o cuando se acaba la entrada
	while (!salir && leerEntrada(entrada))
	{
		separarComando(entrada, comando, argumentos);
		if (comando[0] != '\0')   //las lineas en blanco se ignoran
		{
			if (cadenasIguales(comando, "Salir"))
			{
				salir = true;
			}
			else if (!ejecutarComando(texto, comando, argumentos))
			{
				cout << "Comando no reconocido" << endl;
			}
		}
	}
	BorrarTodo(texto);   //libera la memoria antes de terminar
	return 0;
}
