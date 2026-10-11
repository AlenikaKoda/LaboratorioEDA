#ifndef PALABRA_H
#define PALABRA_H
#include "Tipos.hpp"

struct nodoPalabra
{
	Cadena texto;   //la palabra, copia en memoria dinamica
	nodoPalabra *siguiente;   //proxima palabra de la linea
};

typedef nodoPalabra *Palabra;   //tipo para declarar listas de palabras

Palabra crearPalabra(Cadena);   //devuelve el nodo a insertar (guarda una copia de la cadena)
bool listaPalabrasVacia(Palabra);   //devuelve true si la lista esta vacia
unsigned int cantidadPalabras(Palabra);   //devuelve la cantidad de palabras de la lista
void insertarPalabraEnPos(Palabra &, Palabra, Posicion);   //inserta el nodo en la posicion indicada (1 <= pos <= cantidad + 1)
Palabra extraerUltimaPalabra(Palabra &);   //quita el ultimo nodo de la lista y lo devuelve (NULL si la lista esta vacia)
void eliminarPalabraEnPos(Palabra &, Posicion);   //elimina el nodo de la posicion indicada (1 <= pos <= cantidad)
void liberarPalabra(Palabra &);   //libera la memoria de un nodo (y de su cadena)
void liberarPalabras(Palabra &);   //libera la memoria de todos los nodos de la lista
void mostrarPalabras(Palabra);   //muestra las palabras separadas por un espacio
#endif
