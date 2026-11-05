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

// Quita el primer nodo de la cola y lo devuelve (NULL si la cola esta vacia).
// El nodo devuelto NO se libera: quien llama es responsable de liberarlo.
Palabra desencolar(ColaPalabras& cola)
{
	Palabra extraido = cola.frente;
	
	if(extraido != NULL)
	{
		cola.frente = extraido->siguiente;
		// Si la cola quedo vacia, el fondo tampoco debe apuntar al nodo extraido.
		if(cola.frente == NULL)
		{
			cola.fondo = NULL;
		}
		extraido->siguiente = NULL;
	}
	return extraido;
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
			cout << c.frente->texto << endl;
			c.frente = c.frente->siguiente;		
		}	
	}
}

// Se agrega una copia de la palabra al historial
void agregarAHistorial(Historial& historial, Cadena textoPalabra)
{
	encolar(historial.cola, crearPalabra(textoPalabra));
	historial.longitud++;
	
	// Si se supera el maximo se descarta la palabra mas vieja y se libera.
	if(historial.longitud > MAX_CANT_ULTIMAS_PALABRAS)
	{
		Palabra descartada = desencolar(historial.cola);
		liberarPalabra(descartada);
		historial.longitud--;
	}
}

// Libera todas las palabras del historial y lo deja vacio.
void liberarHistorial(Historial& historial)
{
	liberarPalabras(historial.cola.frente);
	historial.cola.fondo = NULL;
	historial.longitud = 0;
}

// Muestra las palabras desde la ultima ingresada hasta la mas vieja.
// La cola guarda las palabras de la mas vieja a la mas nueva, por eso se
// recorre recursivamente y se muestra al volver (orden inverso).
static void mostrarPalabrasInverso(Palabra palabra)
{
	if(palabra == NULL)
	{
		return;
	}
	
	mostrarPalabrasInverso(palabra->siguiente);
	cout << palabra->texto << endl;
}

void mostrarHistorial(Historial historial)
{
	if(colaVacia(historial.cola))
	{
		cout << "No se ingresaron palabras" << endl;
		return;
	}
	
	mostrarPalabrasInverso(historial.cola.frente);
}
