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


void insertar(Diccionario &arbol, Diccionario v)
{
	if (arbol==NULL)
	{
		arbol = v;
		return;
	}
	
	
	if(textoMenor(v->valor, arbol->valor))
	{
		insertar(arbol->izq, v);
		return;
	}
	
	if(textoMayor(v->valor, arbol->valor))
	{
		insertar(arbol->der, v);
	}
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
			delete[] p->valor; //eliminar cadena en memoria dinamica
			delete p;
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
