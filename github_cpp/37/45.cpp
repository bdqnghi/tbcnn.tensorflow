// Dynamic Programming for rod-cutting problem
// Problem Definition:
//     Each rod piece has its unique price. A rod is of length i.
//     Find a way of cutting this rod so that the price sum of all
//     pieces reach the maximum. Return the optimal price and solution.
// Recurrent solution:
//     Consider the first cut of all. A rod with length i can be cut into
//     0 + i, 1 + (i-1), 2 + (i-2), ... Since it's the first cut, so the 
//     second piece can be further cut to smaller pieces, so the optimal 
//     price of the second piece is equivalent to a subproblem with smaller
//     length. Note the optimal price as r[i], then we have
//         r[i] = max(price[j] + r[i - j]) where j from 1 to i

#include <utility> // std::pair
#include <vector>

void rod_cutting_bottom_up(double* price, double* r, int* s, int length)
{
	// price[i]: the price of rod with length i
	// r[i]: the optimal price for length i
	// s[i]: when reaching optimal value, the length of first piece
	double max_price = -1;
	r[0] = 0; s[0] = 0;
	for (int i = 1; i <= length; i++)
	{
		max_price = -1;
		for (int j = 1; j <= i; j++)
		{
			if (price[j] + r[i - j] > max_price)
			{
				max_price = price[j] + r[i - j];
				s[i] = j;
			}
			r[i] = max_price;
		}
	}
}

std::vector<int> rod_cutting_solution(int *s, int length)
{
	std::vector<int> result;
	while (length > 0)
	{
		result.push_back(s[length]);
		length -= s[length];
	}
	return result;
}

std::pair<double, std::vector<int>> rod_cutting(double* price, int length)
{
	double *r = new double[length + 1];
	int *s = new int[length + 1];
	rod_cutting_bottom_up(price, r, s, length);
	std::vector<int> solution = rod_cutting_solution(s, length);
	auto result = std::make_pair(r[length], solution);
	delete[]r;
	delete[]s;
	return result;
}