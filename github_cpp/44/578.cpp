#include "stdafx.h"
#include "Stack.h"



Stack::Stack() : Lista()
{
}


Stack::~Stack()
{
}

void Stack::push(Elemento* e)
{
	insertarUltimo(e);
}

Elemento* Stack::peek()
{
	return getUltimo();
}

Elemento* Stack::pop()
{
	Elemento* auxiliar = getUltimo();
	moverUltimo();
	return auxiliar;
}

ostream & operator<<(ostream & out, Stack& a) { //sobrecarga del operador <<
	a.imprimir(a.peek(), out, 1);
	return out;
}


void Stack::imprimir(Elemento * e, ostream & out, int posicion)  //se imprime el primer elemento y asi se continua hacia abajo un elemento por fila.
{
	if (e != NULL)
	{
		e->imprimir(out);
		cout << "       Posicion numero: " << posicion << endl;
		
		if (peek() != NULL)
		{
			pop();
			imprimir(peek(), out, posicion + 1);
		}

			

		
	}
}