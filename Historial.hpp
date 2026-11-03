#ifndef HISTORIAL_H
#define HISTORIAL_H

#include "Palabra.hpp"

struct ColaPalabras {
	Palabra frente;
	Palabra fondo;
};
Palabra primero(ColaPalabras);
void encolar(ColaPalabras&, Palabra);
Palabra desencolar(ColaPalabras&);
void verCola(ColaPalabras);
Palabra crearNodo(Cadena);
bool colaVacia(ColaPalabras);

#define MAX_CANT_ULTIMAS_PALABRAS 3

struct Historial
{
	ColaPalabras cola;
	int longitud;
};
void agregarAHistorial(Historial&, Cadena); // La cadena es copiada para ser insertada como palabra en el historial
void mostrarHistorial(Historial);

#endif
