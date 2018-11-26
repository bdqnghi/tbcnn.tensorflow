#include "selectionsort.h"
#include <QTime>
#include <cstdlib>

SelectionSort::SelectionSort(QObject *parent) : QObject(parent)
{

}

void SelectionSort::setSet(QBarSet *s){
    this->s = s;
}

void SelectionSort::selectionSort(int n){

    int i, j, menor, aux;

    for(i = 0; i < s->count() -1; i++){

        menor = i;

        for(j = i+1; j < s->count(); j++){

            if(++comp && s->at(j) < s->at(menor))
                menor = j;
            QTime *tmp = new QTime();
            tmp->start();
            while(tmp->elapsed() < 200){

            }


        }

        aux = s->at(i);
        s->replace(i, s->at(menor));
        s->replace(menor, aux);
        ++swap;
    }


}

void SelectionSort::doWork(){
    comp = 0; swap = 0;
    this->selectionSort(s->count());
    emit resultReady();
}
