#ifndef OPERATOR_H
#define OPERATOR_H

#include "item.h"
#include "recordlist.h"
#include "widget.h"
#include "sortalgorithm.h"
//#include <QWidget>
#include "event.h"
#include <iostream>
#include <algorithm>
#include <QApplication>
#include <QtCore>
#include <QObject>
#include <QtWidgets>

class InsertionSort : public QObject, public SortAlgorithm
{

public:
    static InsertionSort* getInstance();
    static const int totalCount = 20;
    virtual void remove();
    virtual InsertionSort* resetAlgorithm(int num=0, int * array = nullptr);
    ~InsertionSort();

    Item ** itemList = NULL;
    int numItem;
    RecordList * recordList = NULL;

    int count;
    int index1,index2;

    void addItem();
    void handleArray(int *array);
    void swap();
    void restart();
    void getRecord();
    void handleRecord();

private:
    InsertionSort(int num=0, int*array=nullptr );
    static InsertionSort *insertionSort;


    class Cleaner{
    public:
        ~Cleaner() {
            if (InsertionSort::insertionSort){
                delete InsertionSort::insertionSort;
                InsertionSort::insertionSort = nullptr;
            }
        }
    };
    static Cleaner cn;

};

#endif // OPERATOR_H
