#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "Tipos.hpp"
#include "Linea.hpp"
#include "Historial.hpp"
#include "Practico.hpp"
#include "Diccionario.hpp"

#define MAX_LARGO_ENTRADA 256   //largo maximo de una linea de entrada, incluye el '\0'
#define SEPARADORES " ,\t\r\n"   //el comando y los argumentos se separan con comas o con blancos

bool leerEntrada(Cadena);
Cadena usoComando(Cadena, int&);
bool ejecutarComando(Linea&, Historial&, Diccionario&, Cadena);

#endif
