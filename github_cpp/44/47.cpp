#include "stack.h"
#include <assert.h>

//Constructor
template <class T> Stack<T>::Stack(){
  sz = 0;
  index = NULL;
}
//Push
template <class T> void Stack<T>::push(T value){ 
  Nodo* tmp = new Nodo(value,index);  //Se inicializa un nuevo espacio de memoria apuntando a index y con valor igual a "value"
  index = tmp;                        //Index ahora apunta al espacio recien inicializado
  ++sz;                               //La pila crece en 1
}
//Pop
template <class T> void Stack<T>::pop(){ 
   assert(index != NULL);             //Si la pila esta vacia, regresa SEGMENTATION FAULT
   Nodo* tmp = index;                 //tmp apunta a index
   index = index->nxt;                //Index apunta al siguiente en la pila
   delete tmp;                        //tmp borra el primer elemento de la memoria
   --sz;                              //La pila decrece en 1
}
//Top
template <class T> T Stack<T>::top(){
  assert(index != NULL);              //Si la pila esta vacia, regresa SEGMENTATION FAULT
  return index->val;                  //Regresa el valor dentro de index
}
//Size
template <class T> int Stack<T>::size(){
  return sz;                          //Regresa la cantidad de elementos en la pila
}
