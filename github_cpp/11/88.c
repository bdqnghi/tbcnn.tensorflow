  
  
  
#ifndef HEAP_SORT_H  
#define HEAP_SORT_H 1  
#include <iostream>  
#include <cstdlib>  
template<typename T>  
class Heap  
{  
public:  
    
    Heap(  ):m_array( 0 ),m_size( 0 ),m_lenght( 0 ) {}  
    
    Heap( int length );  
    
    ~Heap(  )  
        { delete [  ] m_array;}  
    
    bool insert( T item );  
    
    bool empty(  );  
    
    T fetchMax(  );  
    
    void deleteMax(  );  
    
    void display(  );  
    
    void array_heapSort(T* array ,int size);  
    
    
    void heapSort(  );  
      
        
      
private:  
    
    void locate_down(int start,int end );  
    
    void locate_up(int start,int end ) ;  
      
private:  
    T* m_array;      
    int m_size;       
    int m_lenght;    
      
};  
#include "heap.cpp"  
#endif  