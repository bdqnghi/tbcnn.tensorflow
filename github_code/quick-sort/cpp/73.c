// Luis Maya
/*  This program will implement Quicksort to sort numbers in descending order.
    There will also be functions that dynamically allocate memory to populate it with
    randomly generated values. */
// ***********************************************************************

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

class quickSort
{
public:
    quickSort();
    ~quickSort();
    void generateData(int);
    int getLength();
    short getItem(int);
    void printData();
    void quick_Sort();
private:
    int length;
    short *myArray;
    static const int LIMIT = 5000;
    void quick_Sort(int, int);
    int partition(int, int);
};

// Will initialize class variables
quickSort :: quickSort()
{
    length = 0;                         // Initialize length to 0
    myArray = NULL;                     // Initialize myArray to NULL
}

// Will deallocate appropriate data
quickSort :: ~quickSort()
{
    delete [] myArray;                  // Deallocate myArray
}

// Will dynamically allocate the array on given length
// And populate it with a random values
void quickSort :: generateData(int n)
{
    length = n;                         // Set length to n
    myArray = new short [length];       // Dynamically allocate array with given length

    for (int i = 0; i < length; i++)
        myArray[i] = rand() % LIMIT;    // Populate myArray with random values

}

// Will return length value
int quickSort :: getLength()
{
    return length;                      // Returns length value
}

// Will check if passed index is valid
// And return value located at the passed index
short quickSort :: getItem(int index)
{
    if (index <= length)                // Checks if index value is valid
        return myArray[index];          // Returns myArray[index] value

    else if (index > length)    {       // If index value is invalid, prints message and exits
        cout << "Invalid value!" << endl;
        return 0;                       // Return nothing
    }

    return 0;                           // Return nothing if done
}

// Will print out 10 items per line right justified with a width of 6
void quickSort :: printData()
{
    for (int i = 0; i < length; i++)
      {
        ((i % 10) == 9) ? cout << setw(6) << myArray[i] << '\n' : cout << setw(6) << myArray[i] << ' ';
      }
}

// Will call quickSort algorithm to sort values in descending order
void quickSort :: quick_Sort()
{
    return quick_Sort(0, length - 1);        // Calls private quickSort
}

// Will use quickSort algorithm to sort values in descending order
void quickSort :: quick_Sort(int low, int high)
{
    int p;

    if (low < high)
    {
        p = partition(low, high);           // Will call partition function
        quick_Sort(low, p);                 // Recursively call quickSort
        quick_Sort(p+1, high);              // Recursively call quickSort
    }
}

// partion implementation for quickSort algorithm to sort values
int quickSort :: partition(int low, int high)
{
    int pivot = myArray[low];               // Set pivot to myArray[low]
    int i = low - 1;                        // Set i counter to low - 1
    int j = high + 1;                       // Set j counter to high + 1
    while(true)
    {
        do {
            i++;                            // Update i counter
        } while (myArray[i] > pivot);       // If myArray[i] > pivot
        do {
            j--;                            // Update j counter, j--
        } while (myArray[j] < pivot);       // While myArray[j] < pivot
        if (i < j)                          // If i < j
        {
            swap(myArray[i], myArray[j]);   // Swap myArray[i] with myArray[j]
        }
        else
            return j;                       // Else return j
    }
}
