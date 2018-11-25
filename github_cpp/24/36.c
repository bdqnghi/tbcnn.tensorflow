#include <iostream>


int binary_search(int my_array[], int length, int num_desired)
{
    int guess = length / 2, max = length, min = 0;

    while (guess > min && guess < max)
    {
        if (num_desired == my_array[guess])
        {
            return guess;
        }
        
        else if (my_array[guess] > num_desired)
        {
            max = guess;
            guess = (min + guess) / 2;
        }
        
        else 
        {
            min = guess;
            guess = (max + guess) / 2;
        }
    }

    return -1;
}


int main()
{
    int my_array[1000000];
    for (int i = 0; i < 1000000; ++i)
    {
        my_array[i] = i * 2;
    }
    std::cout << binary_search(my_array, 1000000, 234242) << std::endl;



}
