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

    for (int i=0; i < n-1; i++) {
        int min=i;
        for (int j=i+1; j < n; j++) {

            m_operations.push_back([=,this](){operationCompareElements(j, min); highlightLine(13);});
            if (varray[j] < varray[min])
                min=j;
        }

        double tmp=varray[i];
        varray[i]=varray[min];
        varray[min]=tmp;

        m_operations.push_back([=,this](){operationSwapElements(i, min); highlightLine(16);});
        m_operations.push_back([=,this](){ sortedElementColor(i); });
    }
    m_operations.push_back([=,this](){ sortedElementColor(n-1); });

    m_animationInitialized= true;
    m_currentStepInAnimation= 0;
    m_numberOfStepsInAnimation= m_operations.size();
}
