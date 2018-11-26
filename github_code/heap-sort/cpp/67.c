//
//  heapSort.cpp
//  
//
//  Created by Anubhav Shrivastava on 01/03/15.
//
//

#include<iostream>
#include "priority_queue.cpp"
using namespace std;


void heapify(int * a , int n){
    
}

void make_heap(int* a , priority_queue* q1 , int n){
    int i ;
    for(i = 0 ; i < n ; i++){
        insert(q1 , a[i]);
    }
}

void print_array(int *a , int n){
    for(int i = 0 ; i < n ; i++){
        cout << a[i] <<"\t";
    }
    cout <<endl;
}

void heapSort(int * a , int n){

    priority_queue* q ;
    init_queue(&q);
    make_heap(a , q , n);
    for(int i = 0 ; i < n ; i++){
        a[i] = get_minimum(q);
    }
 
}


int main(){

    int x[] = {6,43,7,8,2,20,22,33,11};
    print_array(x , 9);

    heapSort(x , 9);
    
    print_array(x , 9);

}