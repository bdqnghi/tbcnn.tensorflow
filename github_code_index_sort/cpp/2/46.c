// https://github.com/adkozlov/cpp-2014/blob/6f3c340ef6f9ca199b7a0840c24e96ec43a72247/first/cw_01/1/src/merge.cpp
// recursive MergeSort.cpp

// http://www.softwareandfinance.com/Visual_CPP/Merge_Sort_Iterative.html

#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

typedef std::vector<int> ints;

void mergeIterative(ints& a, size_t left, size_t mid, size_t right)
{
    size_t i = 0;
    size_t j = 0;
    int result[right - left];

    while (left + i < mid && mid + j < right)
    {
        if (a[left + i] < a[mid + j])
        {
            result[i + j] = a[left + i];
            i++;
        }
        else
        {
            result[i + j] = a[mid + j];
            j++;
        }
    }

    while (left + i < mid)
    {
        result[i + j] = a[left + i];
        i++;
    }

    while (mid + j < right)
    {
        result[i + j] = a[mid + j];
        j++;
    }

    for (size_t k = 0; k < i + j; k++)
    {
        a[left + k] = result[k];
    }
}


void mergeRecursive(ints& a, size_t left, size_t mid, size_t right)
{
    size_t i = 0;
    size_t j = 0;
    int result[right - left];

    while (left + i < mid && mid + j < right)
    {
        if (a[left + i] < a[mid + j])
        {
            result[i + j] = a[left + i];
            i++;
        }
        else
        {
            result[i + j] = a[mid + j];
            j++;
        }
    }

    while (left + i < mid)
    {
        result[i + j] = a[left + i];
        i++;
    }

    while (mid + j < right)
    {
        result[i + j] = a[mid + j];
        j++;
    }

    for (size_t k = 0; k < i + j; k++)
    {
        a[left + k] = result[k];
    }
}

void mergeSortRecursive(ints& a, size_t left, size_t right)
{
    if (left + 1 >= right)
    {
        return;
    }

    size_t mid = (left + right) / 2;
    mergeSortRecursive(a, left, mid);
    mergeSortRecursive(a, mid, right);

    mergeRecursive(a, left, mid, right);
}

void mergeSortRecursive(ints& a)
{
    mergeSortRecursive(a, 0, a.size());
}

int main()
{


	std::chrono::duration<long int, std::ratio<1l, 1000000l> > elapsed;

    int n;
    ints numbers;

	std::cout << "Running the recursive algorithm..." << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

    std::ifstream in("randomNumbers.txt");
    while (in >> n)
    {
        numbers.push_back(n);
    }

    mergeSortRecursive(numbers);

    std::ofstream out("randNumOutput.txt");
    for (size_t i = 0; i < numbers.size(); i++)
    {
        out << numbers[i] << " ";
    }
    out << std::endl;

	elapsed = std::chrono::high_resolution_clock::now() - start;

	long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    std::cout << "It took " << microseconds << " microseconds." << std::endl;

    return 0;
}

