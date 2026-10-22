#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tipos.hpp"
#include "Linea.hpp"
#include "Historial.hpp"
#include "Practico.hpp"
using namespace std;

#define MAX_LARGO_ENTRADA 256   //largo maximo de una linea de entrada, incluye el '\0'
#define SEPARADORES " ,\t\r\n"   //el comando y los argumentos se separan con comas o con blancos

//lee una linea completa de la entrada con getchar y la guarda en entrada sin el enter
//devuelve false cuando se acaba la entrada
//si la linea no entra en el buffer avisa Linea demasiado larga y la devuelve vacia para que la linea siguiente se lea bien
bool leerEntrada(Cadena entrada)
{
	char caracter = getchar();
	unsigned int largo = 0;
	bool hayEntrada = caracter != '\0';
	bool demasiadoLarga = false;

	//lee hasta el enter
	while (caracter != '\n')
	{
		//si no hay lugar en el buffer el caracter se descarta pero se sigue leyendo hasta el enter
		if (largo < MAX_LARGO_ENTRADA - 1)
		{
			entrada[largo] = caracter;
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

//devuelve el nombre del comando con sus argumentos esperados, o NULL si el comando no existe
//en esperados deja la cantidad de argumentos que lleva el comando
Cadena usoComando(Cadena comando, int &esperados)
{
	Cadena uso = NULL;
	
	esperados = 0;
	if (cadenasIguales(comando, (Cadena)"InsertarLinea"))
	{
		uso = (Cadena)"InsertarLinea";
	}
	if (cadenasIguales(comando, (Cadena)"InsertarLineaEnPosicion"))
	{
		uso = (Cadena)"InsertarLineaEnPosicion <posicionLinea>";
		esperados = 1;
	}
	if (cadenasIguales(comando, (Cadena)"BorrarLinea"))
	{
		uso = (Cadena)"BorrarLinea <posicionLinea>";
		esperados = 1;
	}
	if (cadenasIguales(comando, (Cadena)"BorrarTodo"))
	{
		uso = (Cadena)"BorrarTodo";
	}
	if (cadenasIguales(comando, (Cadena)"ImprimirTexto"))
	{
		uso = (Cadena)"ImprimirTexto";
	}
	if (cadenasIguales(comando, (Cadena)"InsertarPalabra"))
	{
		uso = (Cadena)"InsertarPalabra <posicionLinea> <posicionPalabra> <palabra>";
		esperados = 3;
	}
	if (cadenasIguales(comando, (Cadena)"BorrarPalabra"))
	{
		uso = (Cadena)"BorrarPalabra <posicionLinea> <posicionPalabra>";
		esperados = 2;
	}
	if (cadenasIguales(comando, (Cadena)"ImprimirLinea"))
	{
		uso = (Cadena)"ImprimirLinea <posicionLinea>";
		esperados = 1;
	}
	if (cadenasIguales(comando, (Cadena)"Salir"))
	{
		uso = (Cadena)"Salir";
	}
	return uso;
}

//interpreta una linea de entrada con el comando y sus argumentos separados por comas o blancos y ejecuta la operacion
//las posiciones se convierten con atoi, un argumento que no es un numero vale 0 y la operacion devuelve ERROR
//si la operacion devuelve ERROR o NO_IMPLEMENTADA lo muestra, con OK no muestra nada
//si el comando no existe muestra Comando invalido, si existe pero le faltan o le sobran argumentos lo avisa y muestra como se usa
//las lineas en blanco se ignoran
//devuelve false cuando el comando es Salir y true en cualquier otro caso
bool ejecutarComando(Linea &texto, Palabra &historial, Cadena entrada)
{
	Cadena comando = strtok(entrada, SEPARADORES);   //el comando es el primer token de la linea
	Cadena arg1 = strtok(NULL, SEPARADORES);   //los argumentos son los tokens que le siguen
	Cadena arg2 = strtok(NULL, SEPARADORES);
	Cadena arg3 = strtok(NULL, SEPARADORES);
	Cadena arg4 = strtok(NULL, SEPARADORES);   //solo sirve para detectar que sobran argumentos
	TipoRetorno ret = OK;
	Cadena motivo = NULL;   //explica por que fallo la operacion cuando devuelve ERROR
	Cadena uso = NULL;   //nombre del comando con sus argumentos, para avisar cuando faltan o sobran argumentos
	int esperados = 0;   //cantidad de argumentos que lleva el comando
	int recibidos = 0;   //cantidad de argumentos que trajo la linea
	bool valido = false;   //pasa a true cuando el comando existe y trae los argumentos esperados
	bool seguir = true;

	//las lineas en blanco no tienen comando y se ignoran
	if (comando != NULL)
	{
		//InsertarLinea no lleva argumentos
		if (cadenasIguales(comando, (Cadena)"InsertarLinea") && arg1 == NULL)
		{
			ret = insertarLinea(texto, crearLinea());
			valido = true;
		}
		//InsertarLineaEnPosicion lleva la posicion de la linea
		if (cadenasIguales(comando, (Cadena)"InsertarLineaEnPosicion") && arg1 != NULL && arg2 == NULL)
		{
			ret = InsertarLineaEnPosicion(texto, atoi(arg1));
			if (ret == ERROR)
			{
				motivo = (Cadena)"La posicion de la linea no es valida, debe estar entre 1 y la cantidad de lineas + 1";
			}
			valido = true;
		}
		//BorrarLinea lleva la posicion de la linea
		if (cadenasIguales(comando, (Cadena)"BorrarLinea") && arg1 != NULL && arg2 == NULL)
		{
			ret = BorrarLinea(texto, atoi(arg1));
			if (ret == ERROR)
			{
				motivo = (Cadena)"La linea no existe";
			}
			valido = true;
		}
		//BorrarTodo no lleva argumentos
		if (cadenasIguales(comando, (Cadena)"BorrarTodo") && arg1 == NULL)
		{
			ret = BorrarTodo(texto);
			valido = true;
		}
		//ImprimirTexto no lleva argumentos
		if (cadenasIguales(comando, (Cadena)"ImprimirTexto") && arg1 == NULL)
		{
			ret = ImprimirTexto(texto);
			valido = true;
		}
		//InsertarPalabra lleva la posicion de la linea, la posicion de la palabra y la palabra
		if (cadenasIguales(comando, (Cadena)"InsertarPalabra") && arg1 != NULL && arg2 != NULL && arg3 != NULL && arg4 == NULL)
		{
			ret = InsertarPalabra(texto, atoi(arg1), atoi(arg2), arg3);
			if (ret == ERROR)
			{
				//como la operacion no modifica el texto cuando falla, se puede ver si lo que no existe es la linea
				motivo = (obtenerLinea(texto, atoi(arg1)) == NULL) ? (Cadena)"La linea no existe" : (Cadena)"La posicion de la palabra no es valida, debe estar entre 1 y la cantidad de palabras de la linea + 1";
			}
			else
			{
				agregarPalabraHistorial(historial, crearPalabra(arg3));
			}
			valido = true;
		}
		//BorrarPalabra lleva la posicion de la linea y la posicion de la palabra
		if (cadenasIguales(comando, (Cadena)"BorrarPalabra") && arg1 != NULL && arg2 != NULL && arg3 == NULL)
		{
			ret = BorrarPalabra(texto, atoi(arg1), atoi(arg2));
			if (ret == ERROR)
			{
				motivo = (obtenerLinea(texto, atoi(arg1)) == NULL) ? (Cadena)"La linea no existe" : (Cadena)"La palabra no existe en la linea";
			}
			valido = true;
		}
		//ImprimirLinea lleva la posicion de la linea
		if (cadenasIguales(comando, (Cadena)"ImprimirLinea") && arg1 != NULL && arg2 == NULL)
		{
			ret = ImprimirLinea(texto, atoi(arg1));
			if (ret == ERROR)
			{
				motivo = (Cadena)"La linea no existe";
			}
			valido = true;
		}
		//No lleva argumentos
		if (cadenasIguales(comando, (Cadena)"ImprimirUltimasPalabras") && arg1 == NULL)
		{
			ret = ImprimirUltimasPalabras(historial);
			valido = true;
		}
		//Salir no lleva argumentos y corta la ejecucion
		if (cadenasIguales(comando, (Cadena)"Salir") && arg1 == NULL)
		{
			seguir = false;
			valido = true;
		}
		//si ningun comando coincidio con esos argumentos se avisa
		if (!valido)
		{
			uso = usoComando(comando, esperados);
			recibidos = (arg1 != NULL) + (arg2 != NULL) + (arg3 != NULL) + (arg4 != NULL);
			//un comando que existe pero no coincide con sus argumentos tiene argumentos de menos o de mas
			if (uso == NULL)
			{
				cout << "Comando '" << comando <<  "' no encontrado." << endl;
			}
			else
			{
				cout << ((recibidos < esperados) ? "Faltan argumentos" : "Sobran argumentos") << ". Uso: " << uso << endl;
			}
		}
		//si la operacion fallo se muestra el resultado, con OK no se muestra nada
		if (ret == ERROR)
		{
			cout << "ERROR: " << motivo << endl;
		}
		if (ret == NO_IMPLEMENTADA)
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
	Palabra historial = NULL;	//el historial inicia vacio
	char entrada[MAX_LARGO_ENTRADA];   //unico arreglo de caracteres, se usa para leer la entrada del usuario
	bool seguir = true;

	//lee y ejecuta comandos hasta que se ingrese Salir o se acabe la entrada
	while (seguir && leerEntrada(entrada))
	{
		seguir = ejecutarComando(texto, historial, entrada);
		cout << endl;
	}
	//libera la memoria antes de terminar
	BorrarTodo(texto);
	BorrarHistorial(historial);
	return 0;
}
