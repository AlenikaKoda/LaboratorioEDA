#ifndef LINEA_H
#define LINEA_H
#include "Tipos.hpp"
#include "Palabra.hpp"

struct nodoLinea
{
	Palabra palabras;   //lista de palabras de la linea
	nodoLinea *siguiente;
};

typedef nodoLinea *Linea;   //tipo para declarar el texto (lista de lineas)

Linea crearLinea();   //devuelve el nodo de una linea vacia (sin palabras)
bool textoVacio(Linea);   //devuelve true si el texto no tiene lineas
unsigned int cantidadLineas(Linea);   //devuelve la cantidad de lineas del texto
Linea obtenerLinea(Linea, Posicion);   //devuelve la linea de la posicion indicada (NULL si no existe)
void insertarLineaFinal(Linea &, Linea);   //inserta la linea al final del texto
void insertarLineaEnPos(Linea &, Linea, Posicion);   //inserta la linea en la posicion indicada (1 <= pos <= cantidad + 1)
void eliminarLineaEnPos(Linea &, Posicion);   //elimina la linea de la posicion indicada (1 <= pos <= cantidad)
void propagarExceso(Linea);   //si la linea supera el maximo de palabras, pasa el exceso a las lineas siguientes
void liberarLinea(Linea &);   //libera la memoria de una linea (y de sus palabras)
void liberarTexto(Linea &);   //libera la memoria de todas las lineas
void mostrarLinea(Linea, Posicion);   //muestra una linea con su numero
void mostrarTexto(Linea);   //muestra todas las lineas con su numero
#endif
