#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <vector>
#include <algorithm>

#define MAX_DATA 100

#define mSwap(first, second) do { \
    int temp = *first;             \
    *first = *second;               \
    *second = temp;                \
} while (0)

using namespace std;

/* PROTOTYPES */
void ProcessInput();
void BucketSort();
void InsertionSort(vector<int> & elements);
void Print();

vector<int> buckets[MAX_DATA];

int numbers[MAX_DATA];
static int numbersCount;
static double maxElement = INT_MIN;

int main()
{
    ProcessInput();
    BucketSort();
    Print();

    return 0;
}

void BucketSort()
{
    for (int count = 0; count < numbersCount; count++)
    {
        int bucketIndex = ( ( numbers[count] / maxElement ) *
                            ( numbersCount - 1 ) ) ;

        buckets[bucketIndex].push_back(numbers[count]);
    }
    cout << endl;

    int numbersIndex = 0;
    for (int count = 0; count < numbersCount; count++)
    {
        InsertionSort(buckets[count]);

        int vectorCount = buckets[count].size();

        for (int vCount = 0; vCount < vectorCount; vCount++)
        {
            numbers[numbersIndex] = buckets[count].at(vCount);
            numbersIndex++;
        }
    }
}

void InsertionSort(vector<int> & elements)
{
    for (int count = 0; count < elements.size(); count++)
    {
        int element = elements.at(count);
        for (int insertCount = count; insertCount > 0; insertCount--)
        {
            if (elements.at(insertCount) < elements.at(insertCount - 1))
            {
                mSwap(&elements.at(insertCount),
                      &elements.at(insertCount - 1));
            }
        }
    }
}

void ProcessInput()
{
    cout << "Input the count of the numbers" << endl;
    cin >> numbersCount;

    for (int count = 0; count < numbersCount; count++)
    {
        cin >> numbers[count];
        if (numbers[count] > maxElement)
        {
            maxElement = (double)numbers[count];
        }
    }
}

void Print()
{
    cout << "Sorted: " << endl;

    for (int count = 0; count < numbersCount; count++)
    {
        cout << numbers[count] << " ";
    }

    cout << endl;
}
