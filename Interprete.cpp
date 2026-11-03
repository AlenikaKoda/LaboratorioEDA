#include "Interprete.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

// Lee una linea completa de la entrada con getchar y la guarda en entrada sin el enter.
// Devuelve false cuando se acaba la entrada.
// Si la linea no entra en el buffer avisa Linea demasiado larga y la devuelve vacia
// para que la linea siguiente se lea bien.
bool leerEntrada(Cadena entrada)
{
	int caracter = getchar();

	// Si no hay entrada disponible, termina.
	if (caracter == EOF)
	{
		entrada[0] = '\0';
		return false;
	}

	unsigned int largo = 0;
	bool demasiadoLarga = false;

	// Lee hasta el enter o el final de la entrada.
	while (caracter != '\n' && caracter != EOF)
	{
		// Si hay lugar en el buffer, guarda el caracter.
		if (largo < MAX_LARGO_ENTRADA - 1)
		{
			entrada[largo] = caracter;
			largo++;
		}
		else
		{
			// Si no hay lugar, descarta el caracter pero sigue leyendo.
			demasiadoLarga = true;
		}

		caracter = getchar();
	}

	entrada[largo] = '\0';

	// Elimina el caracter CR si la entrada utiliza CRLF.
	if (largo > 0 && entrada[largo - 1] == '\r')
	{
		entrada[largo - 1] = '\0';
	}

	// Una linea demasiado larga se avisa y se devuelve vacia.
	if (demasiadoLarga)
	{
		cout << "Linea demasiado larga" << endl;
		entrada[0] = '\0';
	}

	return true;
}

// Devuelve el nombre del comando con sus argumentos esperados, o NULL si el comando no existe.
// En esperados deja la cantidad de argumentos que lleva el comando.
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

	if (cadenasIguales(comando, (Cadena)"BorrarOcurrenciasPalabraEnTexto"))
	{
		uso = (Cadena)"BorrarOcurrenciasPalabraEnTexto <palabra>";
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

	// No lleva argumentos.
	if (cadenasIguales(comando, (Cadena)"ImprimirUltimasPalabras"))
	{
		uso = (Cadena)"ImprimirUltimasPalabras";
	}

	// Lleva un argumento: la palabra.
	if (cadenasIguales(comando, (Cadena)"IngresarPalabraDiccionario"))
	{
		uso = (Cadena)"IngresarPalabraDiccionario <palabra>";
		esperados = 1;
	}

	// No lleva argumentos.
	if (cadenasIguales(comando, (Cadena)"ImprimirTextoIncorrecto"))
	{
		uso = (Cadena)"ImprimirTextoIncorrecto";
		esperados = 0;
	}

	if (cadenasIguales(comando, (Cadena)"Salir"))
	{
		uso = (Cadena)"Salir";
	}

	return uso;
}

// Interpreta una linea de entrada con el comando y sus argumentos separados por comas o blancos
// y ejecuta la operacion.
//
// Las posiciones se convierten con atoi, un argumento que no es un numero vale 0 y la operacion devuelve ERROR.
// Si la operacion devuelve ERROR o NO_IMPLEMENTADA lo muestra, con OK no muestra nada.
// Si el comando no existe muestra Comando invalido.
// Si existe pero le faltan o le sobran argumentos lo avisa y muestra como se usa.
// Las lineas en blanco se ignoran.
//
// Devuelve false cuando el comando es Salir y true en cualquier otro caso.
bool ejecutarComando(Linea &texto, Historial& historial, Diccionario& diccionario, Cadena entrada)
{
	Cadena comando = strtok(entrada, SEPARADORES);   // El comando es el primer token de la linea.
	Cadena arg1 = strtok(NULL, SEPARADORES);         // Los argumentos son los tokens que le siguen.
	Cadena arg2 = strtok(NULL, SEPARADORES);
	Cadena arg3 = strtok(NULL, SEPARADORES);
	Cadena arg4 = strtok(NULL, SEPARADORES);         // Solo sirve para detectar que sobran argumentos.

	TipoRetorno ret = OK;
	Cadena motivo = NULL;   // Explica por que fallo la operacion cuando devuelve ERROR.
	Cadena uso = NULL;      // Nombre del comando con sus argumentos.
	int esperados = 0;      // Cantidad de argumentos que lleva el comando.
	int recibidos = 0;      // Cantidad de argumentos que trajo la linea.
	bool valido = false;   // Pasa a true cuando el comando existe y trae los argumentos esperados.
	bool seguir = true;

	// Las lineas en blanco no tienen comando y se ignoran.
	if (comando != NULL)
	{
		// InsertarLinea no lleva argumentos.
		if (cadenasIguales(comando, (Cadena)"InsertarLinea") && arg1 == NULL)
		{
			ret = insertarLinea(texto, crearLinea());
			valido = true;
		}

		// InsertarLineaEnPosicion lleva la posicion de la linea.
		if (cadenasIguales(comando, (Cadena)"InsertarLineaEnPosicion") && arg1 != NULL && arg2 == NULL)
		{
			ret = InsertarLineaEnPosicion(texto, atoi(arg1));

			if (ret == ERROR)
			{
				motivo = (Cadena)"La posicion de la linea no es valida, debe estar entre 1 y la cantidad de lineas + 1";
			}

			valido = true;
		}

		// BorrarLinea lleva la posicion de la linea.
		if (cadenasIguales(comando, (Cadena)"BorrarLinea") && arg1 != NULL && arg2 == NULL)
		{
			ret = BorrarLinea(texto, atoi(arg1));

			if (ret == ERROR)
			{
				motivo = (Cadena)"La linea no existe";
			}

			valido = true;
		}

		// BorrarTodo no lleva argumentos.
		if (cadenasIguales(comando, (Cadena)"BorrarTodo") && arg1 == NULL)
		{
			ret = BorrarTodo(texto);
			valido = true;
		}

		// BorrarOcurrenciasPalabraEnTexto lleva la palabra a borrar.
		if (cadenasIguales(comando, (Cadena)"BorrarOcurrenciasPalabraEnTexto") && arg1 != NULL && arg2 == NULL)
		{
			ret = BorrarOcurrenciasPalabraEnTexto(texto, arg1);
			valido = true;
		}

		// ImprimirTexto no lleva argumentos.
		if (cadenasIguales(comando, (Cadena)"ImprimirTexto") && arg1 == NULL)
		{
			ret = ImprimirTexto(texto);
			valido = true;
		}

		// InsertarPalabra lleva la posicion de la linea, la posicion de la palabra y la palabra.
		if (cadenasIguales(comando, (Cadena)"InsertarPalabra") && arg1 != NULL && arg2 != NULL && arg3 != NULL && arg4 == NULL)
		{
			ret = InsertarPalabra(texto, atoi(arg1), atoi(arg2), arg3);

			if (ret == ERROR)
			{
				// Como la operacion no modifica el texto cuando falla,
				// se puede ver si lo que no existe es la linea.
				motivo = (obtenerLinea(texto, atoi(arg1)) == NULL)
					? (Cadena)"La linea no existe"
					: (Cadena)"La posicion de la palabra no es valida, debe estar entre 1 y la cantidad de palabras de la linea + 1";
			}
			else
			{
				agregarAHistorial(historial, arg3);
			}

			valido = true;
		}

		// BorrarPalabra lleva la posicion de la linea y la posicion de la palabra.
		if (cadenasIguales(comando, (Cadena)"BorrarPalabra") && arg1 != NULL && arg2 != NULL && arg3 == NULL)
		{
			ret = BorrarPalabra(texto, atoi(arg1), atoi(arg2));

			if (ret == ERROR)
			{
				motivo = (obtenerLinea(texto, atoi(arg1)) == NULL)
					? (Cadena)"La linea no existe"
					: (Cadena)"La palabra no existe en la linea";
			}

			valido = true;
		}

		// ImprimirLinea lleva la posicion de la linea.
		if (cadenasIguales(comando, (Cadena)"ImprimirLinea") && arg1 != NULL && arg2 == NULL)
		{
			ret = ImprimirLinea(texto, atoi(arg1));

			if (ret == ERROR)
			{
				motivo = (Cadena)"La linea no existe";
			}

			valido = true;
		}

		// ImprimirUltimasPalabras no lleva argumentos.
		if (cadenasIguales(comando, (Cadena)"ImprimirUltimasPalabras") && arg1 == NULL)
		{
			ret = ImprimirUltimasPalabras(historial);
			valido = true;
		}

		// IngresarPalabraDiccionario lleva un argumento: la palabra.
		if (cadenasIguales(comando, (Cadena)"IngresarPalabraDiccionario") && arg1 != NULL && arg2 == NULL)
		{
			ret = IngresarPalabraDiccionario(diccionario, arg1);

			if (ret == ERROR)
			{
				motivo = (Cadena)"La palabra ya existe en el diccionario";
			}

			valido = true;
		}

		// ImprimirTextoIncorrecto no lleva argumentos.
		if (cadenasIguales(comando, (Cadena)"ImprimirTextoIncorrecto") && arg1 == NULL)
		{
			ImprimirTextoIncorrecto(diccionario, texto);
			valido = true;
		}

		// Salir no lleva argumentos y corta la ejecucion.
		if (cadenasIguales(comando, (Cadena)"Salir") && arg1 == NULL)
		{
			seguir = false;
			valido = true;
		}

		// Si ningun comando coincidio con esos argumentos se avisa.
		if (!valido)
		{
			uso = usoComando(comando, esperados);

			recibidos = (arg1 != NULL) + (arg2 != NULL) + (arg3 != NULL) + (arg4 != NULL);

			// Un comando que existe pero no coincide con sus argumentos
			// tiene argumentos de menos o de mas.
			if (uso == NULL)
			{
				cout << "Comando '" << comando << "' no encontrado." << endl;
			}
			else
			{
				cout << ((recibidos < esperados) ? "Faltan argumentos" : "Sobran argumentos")
					<< ". Uso: " << uso << endl;
			}
		}

		// Si la operacion fallo se muestra el resultado.
		// Con OK no se muestra nada.
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