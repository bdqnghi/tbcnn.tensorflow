#include "mysort.h"

using std::move;
BaseSort::BaseSort()
{
    arr = (int*)malloc(sizeof(int *) * DefaultLength);
    length = DefaultLength;
}
BaseSort::BaseSort(int len)
{
    if (len <= 0)
        len = DefaultLength;
    arr = (int *)malloc(sizeof(int *) * len);
    length = len;
}
void BaseSort::readData()
{
    int index = 0;
    while(std::cin.peek() != EOF && std::cin.peek() != '\n')
    {
        std::cin >> arr[index++];
        if (index == length)
            break;
    }
    if (index < length)
    {
        arr = (int *)realloc(arr, sizeof(int *) * index);
        length = index;
    }
    for (int i = 0; i < index; i++)
        std::cout << i << ": " << arr[i] << std::endl;
}
bool BaseSort::setArray(int * array, int len)
{
    if (len > 0 && array != nullptr)
    {
        free(arr);
        arr = array;
        length = len;
        return true;
    }
    return false;
}
void BaseSort::setRandomData()
{
    for(int i = 0; i < length; i++)
    {
        arr[i] = random(100);
    }
}
void BaseSort::printArr()
{
    for(int i = 0; i < length; i++)
        std::cout << "第" << i + 1 << "个数据为: " << arr[i] << "; " << std::endl;
}

void BaseSort::printOneLine()
{
    for(int i = 0; i < length; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}


BubbleSort::BubbleSort() : BaseSort()
{
}
void BubbleSort::sort()
{
    for(int i = 0; i < length; i++)
        for(int j = 0; j < length - i; j++)
            if(arr[j] > arr[j+1])
            {
                int tmp = move(arr[j+1]);
                arr[j+1] = move(arr[j]);
                arr[j] = move(tmp);
            }
}




InsertionSort::InsertionSort() : BaseSort()
{
}

void InsertionSort::sort()
{
    for(int i = 1; i < length; i++)
    {
        int tmp = move(arr[i]);
        int j = 0;
        for(j = i-1; j >= 0 && tmp < arr[i]; j++)
            arr[j + 1] = move(arr[j]);
        arr[j] = move(tmp);
    }
}




ShellSort::ShellSort() : BaseSort()
{
}

void ShellSort::sort()
{
    int quanshu = 0;
    for(int gap = length / 2; gap > 0; gap /= 2)
    {
        quanshu++;
        std::cout << "--------第" << quanshu << "圈---------- gap: " << gap << "-----------" << std::endl;
        for(int i = gap; i < length; ++i)
        {
            std::cout << "++++++    i    :   " << i << std::endl;
            int tmp = std::move(arr[i]);
            int j = i;

            for(; j >= gap && tmp < arr[j - gap]; j -= gap)
                arr[j] = std::move(arr[j - gap]);
            arr[j] = std::move(tmp);
            BaseSort::printOneLine();
        }
    }
}



int main()
{
    ShellSort * shell = new ShellSort();
    shell->setRandomData();
    shell->BaseSort::printArr();
    shell->sort();
    shell->BaseSort::printArr();
    return 0;
}
