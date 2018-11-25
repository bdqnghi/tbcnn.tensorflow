#include "stdafx.h"

void InsertionSortTestCases()
{
    int valid[] = { 5, 12, 2, 4, 4, 4, 3, -1 };
    int two[] = { 2, 1 };
    int one[] = { 2 };

    
    cout << "------------------------------------" << endl;
    InsertionSort(valid, (sizeof(valid) / sizeof(*valid)));
    cout << "------------------------------------" << endl;
    InsertionSort(two, (sizeof(two) / sizeof(*two)));
    cout << "------------------------------------" << endl;
    InsertionSort(one, (sizeof(one) / sizeof(*one)));
}

void PrintArray(int* pList, int cElements)
{
    for (int i = 0; i < cElements; i++)
    {
        cout << "'" << *pList << "' ";
        pList++;
    }

    cout << endl;
}


int BinarySearchForInsertionSort(int searchValue, int* pList, int startIndex, int endIndex)
{
    
    
    
    if (endIndex <= startIndex)
    {
        if (searchValue > pList[startIndex])
        {
            return (startIndex + 1);
        }
        else
        {
            return startIndex;
        }
    }

    int middle = (endIndex - startIndex) / 2 + startIndex;

    
    if (pList[middle] > searchValue)
    {
        return BinarySearchForInsertionSort(searchValue, pList, startIndex, middle - 1);
    }
    
    else if (pList[middle] < searchValue)
    {
        return BinarySearchForInsertionSort(searchValue, pList, middle + 1, endIndex);
    }
    
    else
    {
        return middle;
    }
}

void InsertionSort(int* prg, int cElements)
{
    if (!prg || cElements < 2)
        return;

    for (int i = 1; i < cElements; i++)
    {
        int j = i;

        

        while (j > 0 && prg[j - 1] > prg[i])
        {
            
            

            
            j = BinarySearchForInsertionSort(prg[i], prg, 0, i - 1);
        }

        if (i != j)
        {
            int temp = prg[i];

            
            memcpy(&(prg[j + 1]), &(prg[j]), (i - j) * sizeof(*prg));

            
            prg[j] = temp;
        }
    }
}
