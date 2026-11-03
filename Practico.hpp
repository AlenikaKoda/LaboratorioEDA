#ifndef PRACTICO_H
#define PRACTICO_H
#include "Tipos.hpp"
#include "Linea.hpp"
#include "Historial.hpp"
#include "Diccionario.hpp"

TipoRetorno insertarLinea(Linea &, Linea);   //(1) inserta la linea indicada (vacia) al final del texto
TipoRetorno InsertarLineaEnPosicion(Linea &, Posicion);   //(2) inserta una linea vacia en la posicion indicada
TipoRetorno BorrarLinea(Linea &, Posicion);   //(3) borra la linea de la posicion indicada
TipoRetorno BorrarTodo(Linea &);   //(4) borra todas las lineas del texto
TipoRetorno BorrarOcurrenciasPalabraEnTexto(Linea, Cadena); //(5) borra todas las ocurrencias de una palabra en el texto
TipoRetorno ImprimirTexto(Linea);   //(6) imprime el texto por pantalla
TipoRetorno InsertarPalabra(Linea &, Posicion, Posicion, Cadena);   //(8) inserta una palabra en una linea
TipoRetorno BorrarPalabra(Linea &, Posicion, Posicion);   //(9) borra la palabra de la posicion indicada de una linea
TipoRetorno ImprimirLinea(Linea, Posicion);   //(11) imprime una linea por pantalla

TipoRetorno IngresarPalabraDiccionario(Diccionario&, Cadena); // (14) Ingresa una palabra al diccionario si ésta no se encuentra en el diccionario.
TipoRetorno ImprimirTextoIncorrecto(Diccionario, Linea); // (15) Muestra todas las líneas del texto, pero exhibiendo solamente las palabras que no se encuentran en el diccionario.
TipoRetorno ImprimirUltimasPalabras(Historial);	//(16) imprime las ultimas palabras ingresadas por el usuario

#endif
