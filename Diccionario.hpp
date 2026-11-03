#ifndef DICCIONARIO_H
#define DICCIONARIO_H
#include "Tipos.hpp"

struct nodoDiccionario
{
	Cadena cadena;
	nodoDiccionario *izq;
	nodoDiccionario *der;
};
typedef nodoDiccionario *Diccionario;

// Estas operaciones son implementadas a nivel de TAD,
// no siguen las reglas o reestricciones de la letra.
// Esas restricciones se aplican en Practico.cpp y Practico.hpp

Diccionario crearNodoDiccionario(Cadena);
bool insertarEnDiccionario (Diccionario &, Diccionario);
void preOrden(Diccionario);
void postOrden(Diccionario);
void inOrden(Diccionario);
void borrarValorDiccionarioSensible(Diccionario &, Cadena);
Diccionario unirDiccionario(Diccionario, Diccionario);

void mostrarNodoDiccionario(Diccionario);
void destruirNodoDiccionario(Diccionario&);
bool existeEnDiccionarioInsensible(Diccionario&, Cadena);
#endif
