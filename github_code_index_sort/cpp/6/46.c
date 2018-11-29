#include "radixsort.h"

RadixSort::RadixSort()
{
    this->name = "Radix sort";
}





void RadixSort::sort(float data[], int arraySize, int intDelay)
{
    static const int MAX_BYTES_RAM = 2100000000;

    if (MAX_BYTES_RAM / 4 < arraySize)
        return;
    
    /*
    4 * arraySize * combinations <= MAX_BYTES_RAM
    (MAX_BYTES_RAM / arraySize) / 4 <= combinations
    */

    int max_combinations = (MAX_BYTES_RAM / arraySize) / 4;
    int required_combinations = 1, BITS = 0;

    for (int c=2, b=1;  c<=max_combinations && c<=256;  c*=c, b*=2)
    {
        required_combinations = c;
        BITS = b;
    }

    std::cout << "Required combinations: " << required_combinations << " required bits: " << BITS << std::endl;


    int* intData = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        intData[i] = (int)(data[i] * 256);
    }

    const int SIZE = required_combinations;
    int** bukkets = new int*[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = new int[arraySize+1];
        // curr position
        bukkets[i][0] = 1;
    }

    int id;
    int max = (1 << 8) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<arraySize; i++)
        {
            id = intData[i] & bits;
            id >>= r;

            bukkets[id][bukkets[id][0]] = intData[i];
            bukkets[id][0] = bukkets[id][0] + 1;
        }

        for (int i = 0, j = 0; i<arraySize; j++)
        {
            int* &al = bukkets[j];
            int size = al[0];

            for (int x = 1; x<size; x++, i++)
            {
                intData[i] = al[x];
            }

            al[0] = 1;
        }

        for (int i = 0; i < arraySize; i++)
        {
            data[i] = (float)intData[i] / 256.0f;
        }
    }
}



void RadixSort::sort2(float data[], int arraySize, int intDelay)
{
	static const int BITS = 8;

    int* intData = new int[arraySize];
    for (int i = 0; i < arraySize; i++)
    {
        intData[i] = (int)(data[i] * 256);
    }

    const int SIZE = 1 << BITS;
    std::vector<int> bukkets[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = std::vector<int>();
        bukkets[i].push_back(0);
    }

    int id;
    int max = (1 << 8) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<arraySize; i++)
        {
            id = intData[i] & bits;
            id >>= r;

            bukkets[id].push_back(intData[i]);
            bukkets[id][0] = bukkets[id][0] + 1;
        }

        for (int i = 0, j = 0; i<arraySize; j++)
        {
            std::vector<int> &al = bukkets[j];
            int size = al[0] + 1;

            for (int x = 1; x<size; x++, i++)
            {
                intData[i] = al[x];
            }

            al.clear();
            al.push_back(0);
        }

        for (int i = 0; i < arraySize; i++)
        {
            data[i] = (float)intData[i] / 256;
        }
    }
}
