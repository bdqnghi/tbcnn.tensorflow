//
// Created by jelle on 01.03.17.
//
#include "sorteermethode.h"

#ifndef LABO2_MERGESORT_H
#define LABO2_MERGESORT_H

template <typename T>
class Mergesort : public Sorteermethode<T>{
public:
    void operator()(vector<T> & v) const;
private:
    void mergesort(vector<T> &, vector<T> &v, int, int) const;
};

template <typename T>
void merge(vector<T> &, vector<T> &, int, int, int);

template <typename T>
void Mergesort<T>::mergesort(vector<T> &h, vector<T> &v, int l, int r) const{
    if(l+1 < r){
        int m = l+(r-l)/2;
        mergesort(v, h, l, m);
        mergesort(v, h, m, r);

        merge(h, v, l, m , r);
    }
}

template <typename T>
void Mergesort<T>::operator()(vector <T> &v) const {
    vector<T> other(v);  //de andere tabel, waarin we telkens de rechter deeltabel zullen in opslaan
    mergesort(other,v,0,v.size());
}

template <typename T>
void merge(vector<T> &from, vector<T> &to, int l, int m, int r){
    int i=l;
    int j=m;

    //je weet exact hoeveel keer je een element gaat plaatsen (dus tellertje k)
    for(int k=i; k<r; k++){
        if(i<m && (j>=r || from[i] <= from[j])){
            to[k]=from[i++];
        }else{
            to[k]=from[j++];
        }
    }
}

#endif //LABO2_MERGESORT_H
