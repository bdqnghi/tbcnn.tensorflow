/*heap.h*/  
/*ʹ��ָ�������ָ����ʵ��һ����*/  
/*�ѣ���һ����ȫ��������������Ͳ�֮�⣬ÿһ�㶼�����ģ���Ͳ�ڵ㿿��� 
 *        ����Ѵ������ԣ�ÿ��˫�׽ڵ㶼���ڻ��ߵ�����Ů�������� 
 *ע�⣺�ڶ�ʵ�ֵ��ڲ����飬�Ҵ�array[ 1 ]��ʼ������� 
 * 
 *ɾ�������ķ���:������ĵ�һ�����ݺ����һ�����ݽ��н����� 
 *                           ͬʱ�����鳤�ȼ�1����ʱ�򣬶Ѳ����Ǳ�׼�ѣ���Ҫ�����µ� 
 *���һ��������:��������ӵ������ĩβ����ʱ���ܲ����Ǳ�׼�ѣ���Ҫ�����ϵ� 
 */  
#ifndef HEAP_SORT_H  
#define HEAP_SORT_H 1  
#include <iostream>  
#include <cstdlib>  
template<typename T>  
class Heap  
{  
public:  
    //Ĭ�Ϲ��캯��  
    Heap(  ):m_array( 0 ),m_size( 0 ),m_lenght( 0 ) {}  
    //����length���ȵ�����  
    Heap( int length );  
    //��������  
    ~Heap(  )  
        { delete [  ] m_array;}  
    //����һ��������  
    bool insert( T item );  
    //�ж��Ƿ�Ϊ��  
    bool empty(  );  
    //����������ݣ�����ɾ��  
    T fetchMax(  );  
    //ɾ����������Ҳ��������ĵ�һ��������  
    void deleteMax(  );  
    //��ʾ�ѵ�����   
    void display(  );  
    //��һ������T������ת����һ����  
    void array_heapSort(T* array ,int size);  
    //�Զѽ��ж�����  
    //precondition:���Ѿ�����  
    void heapSort(  );  
      
        
      
private:  
    //�µ�����[star,end]����Ķ��������жѻ�  
    void locate_down(int start,int end );  
    //�ϵ�����[star,end]����Ķ��������жѻ�  
    void locate_up(int start,int end ) ;  
      
private:  
    T* m_array;      //ָ��һ�������ָ��  
    int m_size;       //�Ѿ���������ݵĸ���  
    int m_lenght;    //����Ŀռ�ĳ���  
      
};  
#include "heap.cpp"  
#endif  