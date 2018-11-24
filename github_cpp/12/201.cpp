#include <vector>
#include <algorithm>
#include <iostream>

#define INT_MAX 1000

auto FloydWarshall(std::vector < std::vector<int> > matrix) -> std::vector<std::vector<int>> {
	auto size = matrix.size();
	for (auto i = 1; i < size; ++i) {
		for (auto j = 1; j < size; ++j) {
			for (auto k = 1; k < size; ++k) {
				matrix.at(i).at(j) = std::min(matrix.at(i).at(j), matrix.at(i).at(k) + matrix.at(k).at(j));
			}
		}
	}

	return matrix;
}

auto PrintMatrix(std::vector<std::vector<int>> matrix) -> void {
	for each (auto list in matrix)
	{
		for (auto i = 0; i < list.size(); i++) {
			std::cout << list.at(i) << '\t';
		}
		std::cout << std::endl;
	}
}


int main()
{
	auto D = std::vector < std::vector<int> >{
		{0, 0, 0, 0, 0, 0 },
		{0, 0, 3, 8, INT_MAX, -4 },
		{0, INT_MAX, 0, INT_MAX, 1, 7 },
		{0, INT_MAX, 4, 0, INT_MAX, INT_MAX },
		{0, 2, INT_MAX, -5, 0, INT_MAX },
		{0, INT_MAX, INT_MAX, INT_MAX, 6, 0},
	};

	// auto p = std::vector<std::vector<int>>();
	// for (auto i = 0; i < 7; ++i) {
	// 	auto row = std::vector<int>(6, 0);
	// 	p.push_back(row);
	// }

	PrintMatrix(FloydWarshall(D));

    return 0;
}

