#ifndef INTERPRETE_H
#define INTERPRETE_H

#include "Tipos.hpp"
#include "Linea.hpp"
#include "Practico.hpp"

#define MAX_LARGO_ENTRADA 256   //largo maximo de una linea de entrada, incluye el '\0'
#define SEPARADORES " ,\t\r\n"   //el comando y los argumentos se separan con comas o con blancos

bool leerEntrada(Cadena entrada);
Cadena usoComando(Cadena comando, int &esperados);
bool ejecutarComando(Linea &texto, Cadena entrada);

#endif
