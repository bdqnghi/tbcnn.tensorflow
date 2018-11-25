#ifndef __INSERTIONSORT_H
#define __INSERTIONSORT_H
#include <vector>
#include <iostream>

template <class T>
class Insertionsort
{
public:
    Insertionsort(std::vector<T> v){this->data = v;}

    void sort();

    void printVec();

    ~Insertionsort(){}
private:
    std::vector<T> data;
};

template <class T>
void Insertionsort<T>::sort()
{
    int num = this->data.size();
    for (size_t i = 0; i < num; ++i) {
        for (size_t j = i;j>0 && data[j] < data[j-1] ; j--) {
            T tmp = this->data[j];
            this->data[j] = this->data[j-1];
            this->data[j-1] = tmp;
        }
        printVec();
    }
}

template <class T>
void Insertionsort<T>::printVec()
{
    int num = this->data.size();
    for(int i =0;i<num;i++)
    {
        std::cout<<this->data[i]<<" ";
    }
    std::cout<<std::endl;
}


#endif
