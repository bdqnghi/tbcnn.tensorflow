#ifndef SELECTIONSORT_H
#define SELECTIONSORT_H


#include "sortalgorithm.h"
//#include <QWidget>


class SelectionSort : public QObject, public SortAlgorithm
{

public:
    static SelectionSort* getInstance();
    static const int totalCount = 20;
    virtual void remove();
    virtual SelectionSort* resetAlgorithm(int num=0, int * array = nullptr);
    ~SelectionSort();

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
    SelectionSort( int num=0, int*array=nullptr );
    static SelectionSort *selectionSort;
    class Cleaner{
    public:
        ~Cleaner() {
            if (SelectionSort::selectionSort){
                delete SelectionSort::selectionSort;
                SelectionSort::selectionSort = nullptr;
            }
        }
    };
    static Cleaner cn;

};

#endif
