#include "Diccionario.hpp"
#include <iostream>

using namespace std;

Diccionario crearNodoDiccionario(Cadena valor)
{
	Diccionario nuevo=new nodoDiccionario;
	nuevo->valor = copiarCadena(valor);
	nuevo->izq=NULL;
	nuevo->der=NULL;
	return nuevo;
}


bool insertar(Diccionario &arbol, Diccionario v)
{
	if (arbol==NULL)
	{
		arbol = v;
		return true;
	}
	
	if(cadenasIguales(arbol->valor, v->valor))
	{
		return false;
	}
	
	if(textoMenor(v->valor, arbol->valor))
	{
		insertar(arbol->izq, v);
	}
	if(textoMayor(v->valor, arbol->valor))
	{
		insertar(arbol->der, v);
	}
	
	return true;
}


void preOrden(Diccionario arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	
	mostrarNodo(arbol);
	preOrden(arbol->izq);
	preOrden(arbol->der);
}


void postOrden(Diccionario arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	
	postOrden(arbol->izq);
	postOrden(arbol->der);
	mostrarNodo(arbol);
}


void inOrden(Diccionario arbol)
{
	if (arbol == NULL)
	{
		return;
	}
	
	inOrden(arbol->izq);
	mostrarNodo(arbol);
	inOrden(arbol->der);
}


void borrar(Diccionario &arbol, Cadena x)
{
	if (arbol == NULL)
	{
		return;
	}
	
	if(textoMenor(x, arbol->valor))
	{
		borrar(arbol->izq, x);
	}
	else
	{
		if(textoMayor(x, arbol->valor))
		{		  
			borrar(arbol->der, x);
		}
		else
		{
			Diccionario p = arbol;
			arbol = unirABB(arbol->izq, arbol->der);
			destruirNodo(p);
		}
	}
}


Diccionario unirABB(Diccionario izq, Diccionario der)
{
	if(izq==NULL) return der;
	if(der==NULL) return izq;
	
	Diccionario centro = unirABB(izq->der, der->izq);
	izq->der = centro;
	der->izq = izq;
	return der;
}

void mostrarNodo(Diccionario arbol)
{
	cout << arbol->valor << endl;
}

void destruirNodo(Diccionario& nodo)
{
	delete[] nodo->valor; //eliminar cadena en memoria dinamica
	delete nodo;
}
