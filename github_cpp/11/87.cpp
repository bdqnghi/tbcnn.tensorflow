#include<iostream>

int arr[20] = {3, 423, 123, 234, 52, 21, 5, 857, 946, 1872, 63547, 9147, 372, 8, 17, 64, 12, 31, 2, 13};

void print(int* arr)
{
    int i;
    for(i = 0; i < 20; i++)
    {
        std::cout<<arr[i]<< " ";
    }
    std::cout<<std::endl;
}

void max_heapify(int* arr, int last_index, int root)
{
    int first_child, second_child;
    if(root == 0)
    {
        first_child = 1;
        second_child = 2;
    }
    else
    {
        first_child = 2*root+1;
        second_child = 2*root+2;
    }

    
    if(first_child > last_index) 
        return;

    if(second_child > last_index && arr[root] >= arr[first_child]) 
        return;

    if(arr[root] >= arr[first_child] && arr[root] >= arr[second_child] && second_child <= last_index) 
        return;
    else
    {
        int target_child;
        if(second_child > last_index) 
            target_child = first_child;
        else
            target_child = (arr[first_child] >= arr[second_child]) ? first_child : second_child;

        std::swap(arr[root], arr[target_child]);

        max_heapify(arr, last_index, target_child);
    }
}

void produce_max_heap(int* arr, int last_index)
{
    int i;
    for(i = ((last_index)+1)/2; i >= 0; i--)
    {
        max_heapify(arr, last_index, i);
    }
}

int main()
{
    print(arr);
    int i;
    for(i = 19; i >= 0; i--)
    {
        produce_max_heap(arr, i);
        std::swap(arr[0], arr[i]);
    }
    print(arr);
    return 0;
}
