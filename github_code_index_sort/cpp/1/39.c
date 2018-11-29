//STUDENT NAME: Victor Fung
//CLASS:        Algorithms 22000

//This is the insertion sort with swap

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void insertion_sort(int sizeofarray, int length);

int main()
{
    cout << "This will use a random number generator to populate the array!" << endl;
    cout << "I will show the original array and the sorted array!" << endl;
    cout << endl;
    cout << "10 arrays with size n = 2" << endl;
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    insertion_sort(2,2);
    cout << endl;
    cout << "10 arrays with size n = 10 " << endl;
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    insertion_sort(10,10);
    cout << endl;
    cout << "10 arrays with size n = 20" << endl;
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    insertion_sort(20,20);
    cout << endl;
    cout << "10 arrays with size n = 100" << endl;
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    insertion_sort(100,100);
    cout << endl;
}

void insertion_sort(int sizeofarray, int length)
{
    int i, j, m, x;
    int NumberofSwaps = 0;

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //          POPULATING THE ARRAY WITH RNG
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    int random_numbers[sizeofarray];
    srand((unsigned)time(NULL));
    random_shuffle(random_numbers, random_numbers + sizeofarray);
    cout << "Original: ";
    if (sizeofarray < 50)
    {
        for (m = 0; m < sizeofarray; m++)
        {
            random_numbers[m] = (x%200) + (rand() % 200);
            cout << random_numbers[m] << " ";
            x++;
        }
        cout << endl;
    }
    else if (sizeofarray >= 50)
    {
        for (m = 0; m < sizeofarray; m++)
        {
            random_numbers[m] = (x%300) + (rand() % 300);
            cout << random_numbers[m] << " ";
            x++;
        }
        cout << endl;
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //                  INSERTION SORT
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    for (i = 1; i < length; i++)
    {
        j = i;
        NumberofSwaps++;
        while (j > 0 && random_numbers[j - 1] > random_numbers[j])
        {
            swap(random_numbers[j], random_numbers[j-1]);
            j = j-1;
            NumberofSwaps++;
        }
    }

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //           OUTPUT OF THE INSERTION SORT
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    cout << "Sorted: ";
    for (j = 0; j < length; j++)
    {
        cout << random_numbers[j] << " ";
    }
    cout << endl;
    cout << "Number of Steps: " << NumberofSwaps << endl;
    cout << "-----------------------------------------------" << endl;
}
