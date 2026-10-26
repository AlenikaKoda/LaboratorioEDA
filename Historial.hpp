#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Palabra.hpp"

typedef nodoPalabra tipoNodo;
typedef Palabra pNodo;
struct ColaPalabras {
	pNodo frente;
	pNodo fondo;
};
pNodo primero(ColaPalabras);
void encolar(ColaPalabras&, pNodo);
pNodo desencolar(ColaPalabras&);
void verHistorial(ColaPalabras);
pNodo crearNodo(Cadena);
bool historialVacio(ColaPalabras);

#define MAX_HISTORIAL 3

struct Historial
{
	ColaPalabras cola;
	int longitud;
};
void agregarAHistorial(Historial&, Cadena); // La cadena es copiada para ser insertada como palabra en el historial
void mostrarHistorial(Historial);

#endif
