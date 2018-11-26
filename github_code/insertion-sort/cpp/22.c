#include "insertionsort.h"

InsertionSort * InsertionSort::insertionSort = nullptr;

/*
 * InsertionSort的构造函数
 * 核心思想：每一个待排序的数组对应一个processor，若数组更新则删掉旧的，换成新的processor
 * 每个processor有自己的scene、recordlist
 * widget作为公用参数，在main里面生成，在这里仅用指针指向它用于向scene里添加
 */
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

/*
 * handleArray：
 *      根据输入的数组初始化矩形和文本
 *      如果输入数组为空则根据numItem随机生成数组内容
 *
 *  数组处理：
 *      最大最小值归一化： 找到数组的最大值和最小值，（每个元素-最小值+1） / （最大值-最小值）
 *      得到的数字在（ 0， 1.几 ）之间， 作为长度的放缩比例
 */
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

// InsertionSort使用单例模式，此为获得类唯一实例的接口
InsertionSort * InsertionSort::getInstance()
{
    if(insertionSort == nullptr)
        insertionSort = new InsertionSort();
    return insertionSort;
}

// 用户重新设定数组或重新随机初始化之后要调用的函数
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

// 向scene里面添加item
// 要先加widget 即背景、按钮那些，再加矩形、文本等
// 不然widget会把它们覆盖掉
void InsertionSort::addItem()
{
    Event * event = Event::getEvent();
    for(int i=0; i<numItem; ++i){
        event->scene->addItem(itemList[i]->rect);
        event->scene->addItem(itemList[i]->text);
    }
}

// swap定时器触发之后调用
// 每次移动一小点，count记录当前移动小步的次数
// totalCount记录总共要移动小步的次数
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

// 实现排序算法的核心函数
// 核心思想：
//      额外开一个数组复制原本内容，使用排序算法对这个数组进行排序，同时记录中间步骤
//      在用户设定好数组后记录就生成了，剩下的演示只是读取生成的记录
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

// 演示的核心函数
/*      使用两个timer：
 *          wholeTimer记录上一步到下一步的时间
 *          swapTimer记录交换的时间
 * 记录：
 *      type 1 ： 交换模式
 *          attribute1、2：要交换的两个矩形的index
 *
 *      type 0 ： 上色模式
 *          attribute 0： 颜色模式
 *              0：恢复正常颜色
 *              1：此时矩形被选中，设为选中颜色，若前一个矩形不是最大的，则将前一个矩形恢复成普通颜色（为了去掉上一个矩形的被选中颜色）
 *              2：此时矩形是当前最小，设为最小颜色
 *              3：若矩形不是最小，则恢复成正常颜色
 *          attribute 1： 矩形的index
 */
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
    /*
     *  0: normal color
     *  1: compare color
     *  2: maxn color
     *  3: if not maxn, then normal color
    */
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
