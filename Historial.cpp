#include <iostream>
#include "Historial.hpp"

using namespace std;

Palabra crearNodo(Cadena val)
{
	Palabra aux = new nodoPalabra;
	if(aux)
	{
		aux->texto = copiarCadena(val);
		aux->siguiente = NULL;
		return aux;	
	}
	else
	{
		return NULL;	
	}
}

bool colaVacia(ColaPalabras c)
{
	return c.frente == NULL;
}

Palabra primero (ColaPalabras cola)
{  
	return cola.frente; 
}

void encolar(ColaPalabras &cola, Palabra q)
{  
	if (!cola.frente)
	{
		cola.frente=q;
		cola.fondo=q;
	}
	else 
	{
		cola.fondo->siguiente=q; 
		cola.fondo=q;
	}
}

Palabra desencolar(ColaPalabras& cola)
{
	if(!cola.frente)
	{
		return NULL;	
	}
	Palabra aux = new nodoPalabra, eliminar;
	aux->texto = cola.frente->texto;
	aux->siguiente = NULL;
	eliminar = cola.frente; 
	cola.frente = cola.frente->siguiente;
	delete[] eliminar->texto;
	delete eliminar;  
	return aux;
}

void verCola(ColaPalabras c)
{
	if(colaVacia(c))
	{
		cout<<"La cola está vacío";	
	}
	else
	{
		while(c.frente)
		{
			cout << c.frente->texto << "->";
			c.frente = c.frente->siguiente;		
		}	
	}
}

// Se agrega una copia de la palabra al historial
void agregarAHistorial(Historial& historial, Cadena textoPalabra)
{
	encolar(historial.cola, crearPalabra(textoPalabra));
	historial.longitud++;
	
	if(historial.longitud > MAX_HISTORIAL)
	{
		desencolar(historial.cola);
		historial.longitud--;
	}
	
	mostrarHistorial(historial);
}

void mostrarHistorial(Historial historial)
{
	verCola(historial.cola);
}
