#include "SelectionSort.h"


SelectionSort& SelectionSort::operator=(const BaseSorting& obj)
{
		(*this) = SelectionSort(obj);
		return (*this);
}

long long SelectionSort::sort(size_t percent)
{
		if (myArray.empty()) return 0;
		while (percent > 100) percent -= 100;
		size_t size = (size_t)((float)this->size / 100.0f * (float)percent);
		if (size <= 1) return 0;

		auto t1 = std::chrono::system_clock::now();
	
		int min;
		for (size_t i = 0; i < size - 1; i++)
		{
				min = i;
				for (size_t k = i + 1; k < size; k++)
				{
						min = (myArray[k] < myArray[min]) ? k : min;
				}
				std::swap(myArray[i], myArray[min]);
		}

		auto t2 = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
		return elapsed.count();
}
string SelectionSort::name() const
{
		return string("SelectionSort");
}
