#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>

// ListType is an STL container
template <typename ValueType, typename IterType>
void display_list(IterType b, IterType e, const std::string& msg, std::ostream& os)
{
		os << msg;
		std::copy(b, e, std::ostream_iterator<ValueType>(os, " "));
		os << std::endl;
}

void selection_sort()
{
		int numbers[] = {13, 7, 88, 43, 7, 9, 95, 37, 16, 14};
		int length = sizeof(numbers) / sizeof(int);

		display_list<int, int*>(numbers, numbers + length, "Unsorted list: ", std::cout); 


		for (int j = 0; j < length; ++j)
		{
				int min = std::numeric_limits<int>::max();
				int idx = 0;
				for (int i = j; i < length; ++i)
				{
						if (numbers[i] < min)
						{
								min = numbers[i];
								idx = i;
						}
				}
				numbers[idx] = numbers[j];
				numbers[j] = min;
		}

		display_list<int, int*>(numbers, numbers + length, "Sorted list: ", std::cout);
}

int main(int, char*[])
{
		selection_sort();
		return 0;
}

