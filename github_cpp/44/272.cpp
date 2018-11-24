#include "stack.h"
#include <assert.h>

//Constructor
Stack::Stack(){
  sz = 0;
  index = NULL;
}
//Push
void Stack::push(int value){ 
  Nodo* tmp = new Nodo(value,index);  //Se inicializa un nuevo espacio de memoria apuntando a index y con valor igual a "value"
  index = tmp;                        //Index ahora apunta al espacio recien inicializado
  ++sz;                               //La pila crece en 1
}
//Pop
void Stack::pop(){ 
   assert(index != NULL);             //Si la pila esta vacia, regresa SEGMENTATION FAULT
   Nodo* tmp = index;                 //tmp apunta a index
   index = index->nxt;                //Index apunta al siguiente en la pila
   delete tmp;                        //tmp borra el primer elemento de la memoria
   --sz;                              //La pila decrece en 1
}
//Top
int Stack::top(){
  assert(index != NULL);              //Si la pila esta vacia, regresa SEGMENTATION FAULT
  return index->val;                  //Regresa el valor dentro de index
}
//Size
int Stack::size(){
  return sz;                          //Regresa la cantidad de elementos en la pila
}
