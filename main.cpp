#include <iostream>
#include <stdio.h>
#include <string.h>
#include "Tipos.hpp"
#include "Linea.hpp"
#include "Practico.hpp"
using namespace std;

#define MAX_LARGO_ENTRADA 256   //largo maximo de una linea de entrada, incluye el '\0'
#define SEPARADORES " ,\t\r\n"   //el comando y los argumentos se separan con comas o con blancos

//lee una linea completa de la entrada con getchar y la guarda en entrada sin el enter
//devuelve false cuando se acaba la entrada
//si la linea no entra en el buffer avisa Linea demasiado larga y la devuelve vacia para que la linea siguiente se lea bien
bool leerEntrada(Cadena entrada)
{
	int caracter = getchar();   //es int porque EOF no es un caracter
	unsigned int largo = 0;
	bool hayEntrada = (caracter != EOF);
	bool demasiadoLarga = false;

	//lee hasta el enter o hasta el fin de la entrada
	while (caracter != '\n' && caracter != EOF)
	{
		//si no hay lugar en el buffer el caracter se descarta pero se sigue leyendo hasta el enter
		if (largo < MAX_LARGO_ENTRADA - 1)
		{
			entrada[largo] = (char) caracter;
			largo++;
		}
		else
		{
			demasiadoLarga = true;
		}
		caracter = getchar();
	}
	entrada[largo] = '\0';
	//una linea demasiado larga se avisa y se devuelve vacia para que la linea siguiente se lea bien
	if (demasiadoLarga)
	{
		cout << "Linea demasiado larga" << endl;
		entrada[0] = '\0';
	}
	return hayEntrada;
}

//interpreta una linea de entrada con el comando y sus argumentos separados por comas o blancos y ejecuta la operacion
//si la operacion devuelve ERROR o NO_IMPLEMENTADA lo muestra, con OK no muestra nada
//si el comando no existe o sus argumentos no son los esperados muestra Comando invalido
//las lineas en blanco se ignoran
//devuelve false cuando el comando es Salir y true en cualquier otro caso
bool ejecutarComando(Linea &texto, Cadena entrada)
{
	Cadena comando = strtok(entrada, SEPARADORES);   //el comando es el primer token de la linea
	Cadena arg1 = strtok(NULL, SEPARADORES);   //los argumentos son los tokens que le siguen
	Cadena arg2 = strtok(NULL, SEPARADORES);
	Cadena arg3 = strtok(NULL, SEPARADORES);
	Cadena arg4 = strtok(NULL, SEPARADORES);   //solo sirve para detectar que sobran argumentos
	Posicion pos1 = 0;
	Posicion pos2 = 0;
	TipoRetorno ret = OK;
	bool seguir = true;

	//las lineas en blanco no tienen comando y se ignoran
	if (comando != NULL)
	{
		//cada condicion verifica el nombre del comando y que sus argumentos sean los esperados
		if (cadenasIguales(comando, "InsertarLinea") && arg1 == NULL)
		{
			ret = insertarLinea(texto, crearLinea());
		}
		else if (cadenasIguales(comando, "InsertarLineaEnPosicion") && cadenaAPosicion(arg1, pos1) && arg2 == NULL)
		{
			ret = InsertarLineaEnPosicion(texto, pos1);
		}
		else if (cadenasIguales(comando, "BorrarLinea") && cadenaAPosicion(arg1, pos1) && arg2 == NULL)
		{
			ret = BorrarLinea(texto, pos1);
		}
		else if (cadenasIguales(comando, "BorrarTodo") && arg1 == NULL)
		{
			ret = BorrarTodo(texto);
		}
		else if (cadenasIguales(comando, "ImprimirTexto") && arg1 == NULL)
		{
			ret = ImprimirTexto(texto);
		}
		else if (cadenasIguales(comando, "InsertarPalabra") && cadenaAPosicion(arg1, pos1)
				&& cadenaAPosicion(arg2, pos2) && arg3 != NULL && arg4 == NULL)
		{
			ret = InsertarPalabra(texto, pos1, pos2, arg3);
		}
		else if (cadenasIguales(comando, "BorrarPalabra") && cadenaAPosicion(arg1, pos1)
				&& cadenaAPosicion(arg2, pos2) && arg3 == NULL)
		{
			ret = BorrarPalabra(texto, pos1, pos2);
		}
		else if (cadenasIguales(comando, "ImprimirLinea") && cadenaAPosicion(arg1, pos1) && arg2 == NULL)
		{
			ret = ImprimirLinea(texto, pos1);
		}
		else if (cadenasIguales(comando, "Salir") && arg1 == NULL)
		{
			seguir = false;
		}
		else
		{
			//no es un comando conocido o sus argumentos no son los esperados
			cout << "Comando invalido" << endl;
		}
		//si la operacion fallo se muestra el resultado, con OK no se muestra nada
		if (ret == ERROR)
		{
			cout << "ERROR" << endl;
		}
		else if (ret == NO_IMPLEMENTADA)
		{
			cout << "NO_IMPLEMENTADA" << endl;
		}
	}
	return seguir;
}

//lee comandos de la entrada y los ejecuta sobre un texto que empieza vacio
//al terminar libera la memoria
int main()
{
	Linea texto = NULL;   //al iniciar el texto es vacio
	char entrada[MAX_LARGO_ENTRADA];   //unico arreglo de caracteres, se usa para leer la entrada del usuario
	bool seguir = true;

	//lee y ejecuta comandos hasta que se ingrese Salir o se acabe la entrada
	while (seguir && leerEntrada(entrada))
	{
		seguir = ejecutarComando(texto, entrada);
	}
	//libera la memoria antes de terminar
	BorrarTodo(texto);
	return 0;
}
