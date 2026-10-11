#ifndef PRACTICO_H
#define PRACTICO_H
#include "Tipos.hpp"
#include "Linea.hpp"

TipoRetorno insertarLinea(Linea &, Linea);   //(1) inserta la linea indicada (vacia) al final del texto
TipoRetorno InsertarLineaEnPosicion(Linea &, Posicion);   //(2) inserta una linea vacia en la posicion indicada
TipoRetorno BorrarLinea(Linea &, Posicion);   //(3) borra la linea de la posicion indicada
TipoRetorno BorrarTodo(Linea &);   //(4) borra todas las lineas del texto
TipoRetorno ImprimirTexto(Linea);   //(6) imprime el texto por pantalla
TipoRetorno InsertarPalabra(Linea &, Posicion, Posicion, Cadena);   //(8) inserta una palabra en una linea
TipoRetorno BorrarPalabra(Linea &, Posicion, Posicion);   //(9) borra la palabra de la posicion indicada de una linea
TipoRetorno ImprimirLinea(Linea, Posicion);   //(11) imprime una linea por pantalla
#endif
