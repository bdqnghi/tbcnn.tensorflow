#include "stack.h"

using namespace std;

void stack :: push(const size_t& x) {
    if(top_of_stack == _size-1)
        throw overflow_error("Stack Full ! Unable to push ");
    data[++top_of_stack] = x;
    return;
}

void stack :: pop() {
    if(empty()) {
        throw underflow_error("Empty Stack ! Nothing to pop ");
    }
    --top_of_stack;
    return;
}

void stack :: print() {
    if(empty()) {
        cout<<"\nEmpty Stack ! "<<endl;
    }
    else {
        for(int i=top_of_stack; i!=UINT_MAX ;i--)
        {
            cout<<data[i]<<endl;
        }
    }
}
