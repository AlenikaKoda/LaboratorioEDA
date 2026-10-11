#include <string.h>
#include <ctype.h>
#include "Tipos.hpp"

#define MAX_DIGITOS_NUMERO 9   //con 9 digitos el numero siempre entra en un unsigned int
#define BASE_DECIMAL 10   //base para convertir una cadena de digitos en un numero

unsigned int largoCadena(Cadena cadena)
{
	unsigned int largo = 0;

	//una cadena NULL tiene largo 0
	if (cadena != NULL)
	{
		//cuenta los caracteres hasta llegar al '\0'
		while (cadena[largo] != '\0')
		{
			largo++;
		}
	}
	return largo;
}

bool cadenasIguales(Cadena cadena1, Cadena cadena2)
{
	unsigned int i = 0;

	//avanza mientras no termine la primera cadena y los caracteres coincidan, sin distinguir mayusculas
	//el cast a unsigned char evita problemas de tolower con caracteres con tilde o enie
	while (cadena1[i] != '\0' && tolower((unsigned char) cadena1[i]) == tolower((unsigned char) cadena2[i]))
	{
		i++;
	}
	//son iguales solo si las dos cadenas terminan en la misma posicion
	return (tolower((unsigned char) cadena1[i]) == tolower((unsigned char) cadena2[i]));
}

bool cadenaAPosicion(Cadena cadena, Posicion &pos)
{
	unsigned int i = 0;
	bool valida = false;

	//el largo tiene que estar entre 1 y MAX_DIGITOS_NUMERO para que el numero no desborde
	valida = (largoCadena(cadena) >= 1 && largoCadena(cadena) <= MAX_DIGITOS_NUMERO);
	pos = 0;
	//recorre los caracteres y corta en el primero que no es un digito
	while (valida && cadena[i] != '\0')
	{
		valida = (cadena[i] >= '0' && cadena[i] <= '9');
		//cada digito nuevo desplaza lo acumulado una posicion decimal
		if (valida)
		{
			pos = pos * BASE_DECIMAL + (cadena[i] - '0');
		}
		i++;
	}
	return valida;
}
