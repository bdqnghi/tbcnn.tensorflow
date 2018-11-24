#include "stack.h"

template<class T> stack<T>::stack(int tam){
	N = 0;
	topo = -1;
	this->tam = tam;
	pilha = new T[tam];
}

template<class T> stack<T>::stack(){
	N = 0;
	topo = -1;
	this->tam = 100;
	pilha = new T[100];
}

template<class T> void stack<T>::pop(){
	if(empty()){
		std::cerr << "Stack underflow!" << std::endl;
		assert(topo != -1);
	}else{ 
		this->topo--;	
		N--;
	}
}

template<class T> bool stack<T>::empty(){
	return (topo == -1)?true:false;
}

template<class T> void stack<T>::push(T data){
	if(topo == tam-1){
		std::cerr << "Stack overflow!" << std::endl;
		assert(topo != tam-1);
	}	
	topo++;
	N++;
	pilha[topo] = data;
}

template<class T> T stack<T>::top(){
	return pilha[topo];	
}

/*template<class T> stack<T>::~stack(){
	N = 0;
	topo = -1;
	tam = 0;
	delete [] pilha;
}
*/
template class stack<int>;
template class stack<std::string>;
template class stack<bool>;
template class stack<double>;
template class stack<float>;
