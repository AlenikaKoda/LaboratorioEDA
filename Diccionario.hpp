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

Diccionario crearNodoDiccionario(Cadena);
bool insertar (Diccionario &, Diccionario);
void preOrden(Diccionario);
void postOrden(Diccionario);
void inOrden(Diccionario);
void borrar(Diccionario &, Cadena);
Diccionario unirABB(Diccionario, Diccionario);

void mostrarNodo(Diccionario);
void destruirNodo(Diccionario&);
#endif
