#ifndef TIPOS_H
#define TIPOS_H

#define MAX_CANT_PALABRAS_X_LINEA 5   //cantidad maxima de palabras por linea, los ejemplos de la letra suponen que vale 5

typedef char *Cadena;   //tipo para las palabras, cadenas terminadas en '\0' en memoria dinamica

enum retorno
{
	OK, ERROR, NO_IMPLEMENTADA
};
typedef enum retorno TipoRetorno;

typedef unsigned int Posicion;   //posicion de una linea o de una palabra, la primera es la 1

unsigned int largoCadena(Cadena);   //devuelve la cantidad de caracteres de la cadena (sin contar el '\0')
bool cadenasIguales(Cadena, Cadena);   //compara dos cadenas sin distinguir mayusculas de minusculas
#endif
