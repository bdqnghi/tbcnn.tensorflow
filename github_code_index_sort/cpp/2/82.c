/*================================================================
 *   Copyright (C) 2018 He Hongyu(Ray). All rights reserved.
 *
 *   FileName   ：Merge-Sort.cpp
 *   Author     ：He Hongyu (Ray)
 *   Date       ：2018-02-10
 *   Description：)
 *   Email		: hongyu.he@hotmail.com
 *	 GitHub		: https://github.com/HongyuHe
 ================================================================*/
#include <iostream>
#include <string.h>
#include <vector>
#include <limits.h>

#define SIZE 1000

using namespace std;

void printArray (int *array, int total)
{
    for (int i = 0; i < total; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void merge_sort (int *sequence, int total)
{
    if (1 == total)
    {
        return;
    }

    int split = total / 2;
    int size1 = split;
    int size2 = total - split;
    int subsequence1[size1 + 1];
    int subsequence2[size2 + 1];
    memset (subsequence1, 0, sizeof(subsequence1));
    memset (subsequence2, 0, sizeof(subsequence2));
    subsequence1[size1] = INT_MAX;  //set sentinel !!!!!;
    subsequence2[size2] = INT_MAX;

    //divide and copy:
    for (int i = 0; i < split; i++)
    {
        subsequence1[i] = sequence[i];
    }
    for (int i = 0, j = split; i < size2 && j < total; i++, j++)
    {
        subsequence2[i] = sequence[j];
    }
    cout << "Orig Sub:" << endl;
    printArray (subsequence1, size1);
    printArray (subsequence2, size2);

    //recusive:
    merge_sort(subsequence1, size1);
    merge_sort(subsequence2, size2);

    cout << "Sorted Sub: " << endl;
    printArray (subsequence1, size1);
    printArray (subsequence2, size2);

    //merge:
    cout << "Orig Sequence: " << endl;
    printArray (sequence, total);

    int i = 0;
    int j = 0;
    int k = 0;
    while (k < total)
    {
	/**Becasuse of the sentinel, we do not need to specially handle
	the circumstance of termination;*/
        if (subsequence1[i] < subsequence2[j])
        {
            sequence[k] = subsequence1[i];
            i++;
        }else
        {
            sequence[k] = subsequence2[j];
            j++;
        }
        k++;
    }
    cout << "Sorted Sequence: " << endl;
    printArray (sequence, total);

    cout << "------------- [Sorted] ------------" << endl;
    return;

}

int main()
{
    int total = 0;
    int sequence[SIZE];
    memset (sequence, 0, sizeof(sequence));

    cin >> total;
    cout << "Input: " << endl;
    for (int i = 0; i < total; i++)
    {
        cin >> sequence[i];
    }

    merge_sort (sequence, total);

    cout << "Output: " << endl;
    for (int i = 0; i < total; i++)
    {
        cout << sequence[i];
    }
    cout << endl;

    return 0;
}
