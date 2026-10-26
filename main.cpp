#include <iostream>
#include "Interprete.hpp"
using namespace std;

//lee comandos de la entrada y los ejecuta sobre un texto que empieza vacio
//al terminar libera la memoria
int main()
{
	Linea texto = NULL;   //al iniciar el texto es vacio
	char entrada[MAX_LARGO_ENTRADA];   //unico arreglo de caracteres, se usa para leer la entrada del usuario
	bool seguir = true;

	//lee y ejecuta comandos hasta que se ingrese Salir o se acabe la entrada
	while (seguir && leerEntrada(entrada))
	{
		seguir = ejecutarComando(texto, entrada);
		cout << endl;
	}
	
	//libera la memoria antes de terminar
	BorrarTodo(texto);
	return 0;
}
