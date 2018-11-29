#include "stdafx.h"

void InsertionSortTestCases()
{
    int valid[] = { 5, 12, 2, 4, 4, 4, 3, -1 };
    int two[] = { 2, 1 };
    int one[] = { 2 };

    // Insertion sort
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

// Return the insertion point
int BinarySearchForInsertionSort(int searchValue, int* pList, int startIndex, int endIndex)
{
    // Indices have met or crossed - we're out of real estate to evaluate. 
    // Determine if the correct element is the current one, or the one to
    // the right. 
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

    // middle candidate is bigger than search value, so inspect the smaller side of the sorted list
    if (pList[middle] > searchValue)
    {
        return BinarySearchForInsertionSort(searchValue, pList, startIndex, middle - 1);
    }
    // middle candidate is smaller than the search value, so inspect the larger side of the sorted list
    else if (pList[middle] < searchValue)
    {
        return BinarySearchForInsertionSort(searchValue, pList, middle + 1, endIndex);
    }
    // middle candidate is the same as the search value, so return middle as the insertion point
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

        // Calculate insertion point

        while (j > 0 && prg[j - 1] > prg[i])
        {
            // // Linear O(n)
            //    j--;

            // Binary search O(log n)
            j = BinarySearchForInsertionSort(prg[i], prg, 0, i - 1);
        }

        if (i != j)
        {
            int temp = prg[i];

            // Make insertion point
            memcpy(&(prg[j + 1]), &(prg[j]), (i - j) * sizeof(*prg));

            // insert value at correct location
            prg[j] = temp;
        }
    }
}
