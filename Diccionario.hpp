#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include "Tipos.hpp"

struct nodoDiccionario
{
	Cadena valor;
	nodoDiccionario *izq;
	nodoDiccionario *der;
};
typedef nodoDiccionario *Diccionario;

void mostrarNodo(Diccionario);
Diccionario crearNodoDiccionario(Cadena);
void insertar (Diccionario &, Diccionario);
void preOrden(Diccionario);
void postOrden(Diccionario);
void inOrden(Diccionario);
void borrar(Diccionario &, Cadena);
Diccionario unirABB(Diccionario, Diccionario);
#endif
