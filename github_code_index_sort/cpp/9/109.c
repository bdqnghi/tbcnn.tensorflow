#include "selectionsort.h"
#include "DATA_STRUCTURES/visualarray.h"

SelectionSort::SelectionSort( qreal x, qreal y, qreal width, qreal height,
              QObject * parent, const vector<double> &values)
    : VisualArray(x, y, width, height, parent, values)
{
}

SelectionSort::SelectionSort()
    :VisualArray()
{

}

void SelectionSort::initializeAnimation() {
    vector<double> varray= values();
    int n=varray.size();
//    Swaping i-th elementh with i-th minimum of array (last element is in place when others are done):
    for (int i=0; i < n-1; i++) {
        int min=i;
        for (int j=i+1; j < n; j++) {
//            Putting functions and indexes in vectors:
            m_operations.push_back([=,this](){operationCompareElements(j, min); highlightLine(13);});
            if (varray[j] < varray[min])
                min=j;
        }
//        Swaping logical array elements:
        double tmp=varray[i];
        varray[i]=varray[min];
        varray[min]=tmp;
//            Putting functions and indexes in vectors:
        m_operations.push_back([=,this](){operationSwapElements(i, min); highlightLine(16);});
        m_operations.push_back([=,this](){ sortedElementColor(i); });
    }
    m_operations.push_back([=,this](){ sortedElementColor(n-1); });
//    Initializing variables for animation control:
    m_animationInitialized= true;
    m_currentStepInAnimation= 0;
    m_numberOfStepsInAnimation= m_operations.size();
}
