#include "insertionsort.h"

InsertionSort * InsertionSort::insertionSort = nullptr;


InsertionSort::InsertionSort( int num, int*array)
{
    numItem = (num==0)? qrand()%9+2 : num;
    count = 0;
    handleArray(array);
    if(recordList)
        delete recordList;
    recordList = new RecordList();
    getRecord();
    addItem();

    Event * event = Event::getEvent();
    connect(event->swapTimer,&QTimer::timeout, this,&InsertionSort::swap);
    connect(event->wholeTimer, &QTimer::timeout, this, &InsertionSort::handleRecord);

}


void InsertionSort::handleArray(int *array)
{
    int minx = 100;
    int maxn = 0;
    int * temarray;
    itemList = new Item* [numItem];
    if(array==nullptr)
    {
        temarray = new int[numItem];
        for(int i=0; i<numItem; i++){
            temarray[i] = qrand()%20+5;
        }
    }
    else
        temarray = array;

    for(int i=0; i<numItem; i++){
        minx = std::min(minx, temarray[i]);
        maxn = std::max(maxn, temarray[i]);

    }

    for(int i=0; i<numItem; i++){
        double aa = ((temarray[i]-minx+1)*1.0/(maxn-minx+1)*110);
        itemList[i] = new Item(temarray[i],i, aa);

    }
    delete []temarray;
}

void InsertionSort::remove()
{
    delete insertionSort;
    insertionSort = nullptr;
}


InsertionSort * InsertionSort::getInstance()
{
    if(insertionSort == nullptr)
        insertionSort = new InsertionSort();
    return insertionSort;
}


InsertionSort * InsertionSort::resetAlgorithm(int num, int * array)
{
    Event * event = Event::getEvent();
    if(itemList)
    for(int i=0; i<numItem; i++){
        event->scene->removeItem(itemList[i]->rect);
        event->scene->removeItem(itemList[i]->text);
        delete itemList[i];
    }
    delete [] itemList;
    recordList->clear();

    numItem = (num==0)? qrand()%9+2 : num;
    handleArray(array);
    getRecord();
    addItem();

    return insertionSort;
}




void InsertionSort::addItem()
{
    Event * event = Event::getEvent();
    for(int i=0; i<numItem; ++i){
        event->scene->addItem(itemList[i]->rect);
        event->scene->addItem(itemList[i]->text);
    }
}




void InsertionSort::swap()
{
    if(count==0){
        itemList[index1]->rect->setColorMode(Rect::SWAP);
        itemList[index2]->rect->setColorMode(Rect::SWAP);
    }
    count++;
    if(count<=totalCount){

        Item *item1 = itemList[index1];
        Item *item2 = itemList[index2];
        item1->move( (40*1.0*(index2-index1)*1.0)/totalCount, 0 );
        item2->move( (40*1.0*(index1-index2)*1.0)/totalCount, 0 );
    }
    else{
        count = 0;
        Event::getEvent()->swapTimer->stop();
        itemList[index1]->rect->setColorMode(Rect::SELECTED);
        itemList[index2]->rect->setColorMode(Rect::SELECTED);
        Item * tem = itemList[index1];
        itemList[index1] = itemList[index2];
        itemList[index2] = tem;
    }
}

void InsertionSort::restart()
{

    Record * current = recordList->move(1);
    Item * tem;
    int index1, index2;
    while(-1!=current->type){
        if(current->type==1){
            index1 = current->attribute1;
            index2 = current->attribute2;
            itemList[index1]->move((40*1.0*(index2-index1)*1.0), 0);
            itemList[index2]->move((40*1.0*(index1-index2)*1.0), 0);
            tem = itemList[index1];
            itemList[index1] = itemList[index2];
            itemList[index2] = tem;
        }
        current = recordList->move(1);
    }
    recordList->move();
    for(int i=0; i<numItem; i++)
        itemList[i]->rect->setColorMode(Rect::NORMAL);
}





void InsertionSort::getRecord()
{
    int * temarray = new int[numItem];

    for(int i=0; i<numItem ; i++)
        temarray[i] = itemList[i]->num;

    for(int i =1;i<numItem;i++){
            if(i==1) {
               recordList->addRecord(0,1,0);
               recordList->addRecord(0,1,i);
            }else{
               recordList->addRecord(0,1,i);
            }


          int val=temarray[i];
           int j=i-1;
           while(j>=0&&temarray[j]>val){
               recordList->addRecord(0,2,j+1);
               recordList->addRecord(0,2,j);
               if(temarray[j]>val){

                  temarray[j+1]=temarray[j];
                  recordList->addRecord(1,j,j+1);
               }
               j--;
            }
            temarray[j+1]=val;

        }
    delete []temarray;
}



void InsertionSort::handleRecord()
{

    Event * event = Event::getEvent();
    event->wholeTimer->stop();

    Record* record = recordList->current;
    if( !record || record->type==-1 ){

        return;
    }

    recordList->move();

    if(record->type==1){
        if(event->userMode==0)
            event->wholeTimer->start(1000);
        index1 = record->attribute1;
        index2 = record->attribute2;
        event->swapTimer->start(40);
    }
    
    else{
        if(event->userMode==0)
            event->wholeTimer->start(400);
        Rect * item = itemList[record->attribute2]->rect;
        switch(record->attribute1){
        case 0:
            item->setColorMode(Rect::NORMAL);
            break;
        case 1:
            item->setColorMode(Rect::SELECTED);

            break;
        case 2:
            item->setColorMode(Rect::MAXN);
            break;
        case 3:
            if(item->getColorMode()!=Rect::MAXN)
                item->setColorMode(Rect::NORMAL);
            break;
        }
    }
}

InsertionSort::~InsertionSort()
{
    if(itemList){
        Event * event = Event::getEvent();
        for(int i=0; i<numItem; i++){
            event->scene->removeItem(itemList[i]->rect);
            event->scene->removeItem(itemList[i]->text);
            delete itemList[i];
        }
        delete []itemList;
    }
    delete recordList;
}
