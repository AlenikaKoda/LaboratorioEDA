#include <string.h>
#include <ctype.h>
#include "Tipos.hpp"

//devuelve la cantidad de caracteres de la cadena sin contar el '\0'
//si la cadena es NULL devuelve 0
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

//compara dos cadenas caracter a caracter sin distinguir mayusculas de minusculas
//las dos cadenas tienen que ser distintas de NULL y terminar en '\0'
//devuelve true si tienen los mismos caracteres y el mismo largo
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
