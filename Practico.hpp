#ifndef PRACTICO_H
#define PRACTICO_H
#include "Tipos.hpp"
#include "Linea.hpp"

//operaciones relativas a las lineas (al documento)
TipoRetorno insertarLinea(Linea &, Linea);   //inserta la linea indicada (vacia) al final del texto
TipoRetorno InsertarLineaEnPosicion(Linea &, Posicion);   //inserta una linea vacia en la posicion indicada
TipoRetorno BorrarLinea(Linea &, Posicion);   //borra la linea de la posicion indicada
TipoRetorno BorrarTodo(Linea &);   //borra todas las lineas del texto
TipoRetorno ImprimirTexto(Linea);   //imprime el texto por pantalla

//operaciones relativas a las palabras
TipoRetorno InsertarPalabra(Linea &, Posicion, Posicion, Cadena);   //inserta una palabra en una linea
TipoRetorno BorrarPalabra(Linea &, Posicion, Posicion);   //borra la palabra de la posicion indicada de una linea
TipoRetorno ImprimirLinea(Linea, Posicion);   //imprime una linea por pantalla
#endif
