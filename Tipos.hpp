#ifndef TIPOS_H
#define TIPOS_H

#define MAX_CANT_PALABRAS_X_LINEA 3   //cantidad maxima de palabras por linea (los ejemplos de la letra usan 3)

typedef char *Cadena;   //tipo para las palabras (se guardan siempre en memoria dinamica)

enum retorno
{
	OK, ERROR, NO_IMPLEMENTADA
};
typedef enum retorno TipoRetorno;

typedef unsigned int Posicion;

unsigned int largoCadena(Cadena);   //devuelve la cantidad de caracteres de la cadena (sin contar el '\0')
Cadena crearCadena(Cadena);   //devuelve una copia de la cadena en memoria dinamica
void borrarCadena(Cadena &);   //libera la memoria de la cadena
bool esBlanco(char);   //devuelve true si el caracter es un blanco (espacio, tab, salto de linea, etc.)
bool cadenasIguales(const char *, const char *);   //compara dos cadenas sin distinguir mayusculas de minusculas
Cadena recortarCadena(Cadena);   //quita los blancos del principio y del final; devuelve el inicio de la cadena recortada (modifica la cadena)
bool esNumero(Cadena);   //devuelve true si la cadena es un numero natural (solo digitos)
Posicion cadenaAPosicion(Cadena);   //convierte una cadena numerica (valida) en una posicion
#endif
