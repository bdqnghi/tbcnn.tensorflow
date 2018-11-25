#include "shellsort.h"
#include <QTime>
#include <cstdlib>

ShellSort::ShellSort(QObject *parent) : QObject(parent)
{

}

void ShellSort::setSet(QBarSet *s){
    this->s = s;
}

void ShellSort::shellsort(){
    int h = 1;
    int i, j, chave;

    do{
        h = 3*h + 1;
    }while(h < s->count());

    do{
        h /= 3;
        for(i = h; i < s->count(); i++){
            chave = s->at(i);
            j = i;
            while(++comp && j >= h && s->at(j -h) > chave){
                s->replace(j, s->at(j - h));
                j -= h;
                ++swap;

                QTime *tmp = new QTime();
                tmp->start();
                while(tmp->elapsed() < 200){

                }

                emit resultReady();
            }
            s->replace(j, chave);
            ++swap;
        }

    }while(h != 1);
}

void ShellSort::doWork(){
    comp = 0; swap = 0;
    this->shellsort();
    emit greenPeace(0);

}

