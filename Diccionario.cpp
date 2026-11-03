#include "Diccionario.hpp"
#include <iostream>

using namespace std;

// Crear un 'nodoDiccionario' nuevo, la cadena 'valor'
// es copiada en memoria dinamica para evitar compartimiento de memoria.
Diccionario crearNodoDiccionario(Cadena valor)
{
	Diccionario nuevo = new nodoDiccionario;
	nuevo->cadena = copiarCadena(valor);
	nuevo->izq = NULL;
	nuevo->der = NULL;
	return nuevo;
}

// Inserta un nodo de diccionario llamado 'nodo' en 'diccionario'.
// Importante que el nodo sea nuevo o que no sea referenciado por otro nodo.
// Esta operacion es sensible ante mayusculas.
// Retorna true si la insersion fue correcta, false el valor del nodo ya existia.
bool insertarEnDiccionario(Diccionario &diccionario, Diccionario nodo)
{
	if (diccionario == NULL)
	{
		diccionario = nodo;
		return true;
	}
	
	if(cadenasIgualesInsensibles(diccionario->cadena, nodo->cadena))
	{
		return false;
	}
	
	// Usamos la version 'Sensible' ya que se pide que las palabras
	// en el diccionario se guarden respetando la entrada del usuario,
	// por lo que 'hola' y 'hOla' son diferentes al GUARDARLAS del diccionario.
	// sin embargo, al consultar el diccionario 'hola' y 'hOla' son iguales.

	if(cadenaMenorSensible(nodo->cadena, diccionario->cadena))
	{
		insertarEnDiccionario(diccionario->izq, nodo);
	}
	if(cadenaMayorSensible(nodo->cadena, diccionario->cadena))
	{
		insertarEnDiccionario(diccionario->der, nodo);
	}
	
	return true;
}


void preOrden(Diccionario diccionario)
{
	if (diccionario == NULL)
	{
		return;
	}
	
	mostrarNodoDiccionario(diccionario);
	preOrden(diccionario->izq);
	preOrden(diccionario->der);
}


void postOrden(Diccionario diccionario)
{
	if (diccionario == NULL)
	{
		return;
	}
	
	postOrden(diccionario->izq);
	postOrden(diccionario->der);
	mostrarNodoDiccionario(diccionario);
}


void inOrden(Diccionario diccionario)
{
	if (diccionario == NULL)
	{
		return;
	}
	
	inOrden(diccionario->izq);
	mostrarNodoDiccionario(diccionario);
	inOrden(diccionario->der);
}


// Borra la ocurrencia de 'valorABorrar' del 'diccionario',
// esta operacion es sensible para mayusculas.
void borrarValorDiccionarioSensible(Diccionario &diccionario, Cadena valorABorrar)
{
	if (diccionario == NULL)
	{
		return;
	}
	
	if(cadenaMenorSensible(valorABorrar, diccionario->cadena))
	{
		borrarValorDiccionarioSensible(diccionario->izq, valorABorrar);
	}
	else
	{
		if(cadenaMayorSensible(valorABorrar, diccionario->cadena))
		{		  
			borrarValorDiccionarioSensible(diccionario->der, valorABorrar);
		}
		else
		{
			Diccionario p = diccionario;
			diccionario = unirDiccionario(diccionario->izq, diccionario->der);
			destruirNodoDiccionario(p);
		}
	}
}


Diccionario unirDiccionario(Diccionario izq, Diccionario der)
{
	if(izq==NULL) return der;
	if(der==NULL) return izq;
	
	Diccionario centro = unirDiccionario(izq->der, der->izq);
	izq->der = centro;
	der->izq = izq;
	return der;
}

// Muestra el valor de un nodo de diccionario
void mostrarNodoDiccionario(Diccionario diccionario)
{
	cout << diccionario->cadena << endl;
}

// Destruye un solo nodo, librerando la cadena y el nodo mismo de la memoria dinamica.
// No destruye el arbol o sub-arbol, solo el nodo especificado.
void destruirNodoDiccionario(Diccionario& nodo)
{
	delete[] nodo->cadena; //eliminar cadena en memoria dinamica creada por 'crearNodoDiccionario'
	delete nodo; //eliminar el nodo en memoria dinamica creada por 'crearNodoDiccionario
}

// Retorna si existe la ocurrencia de 'valorABorrar' del 'diccionario',
// esta operacion es insensible para mayusculas.

bool existeEnDiccionarioInsensible(Diccionario& diccionario, Cadena valorObjetivo)
{
	if(!diccionario)
	{
		return false;
	}
	
	if(textoMenorInsensible(diccionario->cadena, valorObjetivo))
	{
		return existeEnDiccionarioInsensible(diccionario->der, valorObjetivo);
	}
	
	if(textoMayorInsensible(diccionario->cadena, valorObjetivo))
	{
		return existeEnDiccionarioInsensible(diccionario->izq, valorObjetivo);
	}
	
	return true;
}
