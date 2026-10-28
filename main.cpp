#include <iostream>
#include "Interprete.hpp"
#include "Historial.hpp"
#include "Diccionario.hpp"
using namespace std;

//lee comandos de la entrada y los ejecuta sobre un texto que empieza vacio
//al terminar libera la memoria
int main()
{
// Prueba para el TAD Diccionario, eliminar para la entrega
#if 0
#define I(X) insertar(d, crearNodoDiccionario((Cadena)X))
	
	Diccionario d = NULL;
	I("a");
	I("aa");
	I("aaa");
	I("aac");
	I("aba");
	I("cab");
	I("ca");
	I("1");
	I("10");
	I("3");
	inOrden(d); cout << endl;
	
	borrar(d, "ca");
	inOrden(d); cout << endl;

	return 0;
#endif
	
	Linea texto = NULL;   //al iniciar el texto es vacio
	Historial historial;		  //al iniciar el historial es vacio
	historial.longitud = 0;
	historial.cola.fondo = NULL;
	historial.cola.frente = NULL;
	
	char entrada[MAX_LARGO_ENTRADA];   //unico arreglo de caracteres, se usa para leer la entrada del usuario
	bool seguir = true;

	//lee y ejecuta comandos hasta que se ingrese Salir o se acabe la entrada
	while (seguir && leerEntrada(entrada))
	{
		seguir = ejecutarComando(texto, historial, entrada);
		cout << endl;
	}
	
	//libera la memoria antes de terminar
	BorrarTodo(texto);
	return 0;
}
