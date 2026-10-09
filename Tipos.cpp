#include <string.h>
#include <ctype.h>
#include "Tipos.hpp"

#define MAX_DIGITOS_NUMERO 9   //con 9 digitos el numero siempre entra en un unsigned int

unsigned int largoCadena(Cadena cadena)
{
	unsigned int largo = 0;

	if (cadena != NULL)
	{
		while (cadena[largo] != '\0')
		{
			largo++;
		}
	}
	return largo;
}

Cadena crearCadena(Cadena origen)
{
	Cadena copia = NULL;

	if (origen != NULL)
	{
		copia = new char[largoCadena(origen) + 1];   //+1 para el '\0'
		strcpy(copia, origen);
	}
	return copia;
}

void borrarCadena(Cadena &cadena)
{
	if (cadena != NULL)
	{
		delete[] cadena;
		cadena = NULL;
	}
}

bool esBlanco(char caracter)
{
	//el cast a unsigned char evita problemas de isspace con caracteres con tilde o enie
	return (isspace((unsigned char) caracter) != 0);
}

bool cadenasIguales(const char *cadena1, const char *cadena2)
{
	unsigned int i = 0;

	//avanza mientras no termine la primera cadena y los caracteres coincidan (sin distinguir mayusculas)
	while (cadena1[i] != '\0' && tolower((unsigned char) cadena1[i]) == tolower((unsigned char) cadena2[i]))
	{
		i++;
	}
	//son iguales solo si se llego al final de las dos a la vez
	return (tolower((unsigned char) cadena1[i]) == tolower((unsigned char) cadena2[i]));
}

Cadena recortarCadena(Cadena cadena)
{
	unsigned int largo = 0;

	while (esBlanco(*cadena))
	{
		cadena++;   //se salta los blancos del principio
	}
	largo = largoCadena(cadena);
	while (largo > 0 && esBlanco(cadena[largo - 1]))
	{
		largo--;   //se descartan los blancos del final
	}
	cadena[largo] = '\0';
	return cadena;
}

bool esNumero(Cadena cadena)
{
	unsigned int i = 0;
	bool numero = (largoCadena(cadena) >= 1 && largoCadena(cadena) <= MAX_DIGITOS_NUMERO);

	while (numero && cadena[i] != '\0')
	{
		numero = (cadena[i] >= '0' && cadena[i] <= '9');
		i++;
	}
	return numero;
}

Posicion cadenaAPosicion(Cadena cadena)
{
	Posicion pos = 0;
	unsigned int i = 0;

	while (cadena[i] != '\0')
	{
		pos = pos * 10 + (cadena[i] - '0');
		i++;
	}
	return pos;
}
