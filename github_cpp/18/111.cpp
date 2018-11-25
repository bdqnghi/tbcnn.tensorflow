












#include <utility> 
#include <vector>

void rod_cutting_bottom_up(double* price, double* r, int* s, int length)
{
	
	
	
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