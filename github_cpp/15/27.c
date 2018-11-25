












#define INF 2147483647
#include <iostream>
void matrix_multiplication_bottom_up(int* dim, int* m, int* pos, int length)
{
	for (int i = 0; i < length; i++)
		m[i * length + i] = 0;
	int min = INF, tmp_ops = 0;
	for (int i = 1; i < length; i++)
	{
		for (int j = 0; j < length - i; j++)
		{
			
			min = INF;
			for (int k = j; k < j + i; k++)
			{
				tmp_ops = m[j * length + k] + m[(k + 1) * length + j + i]
					+ dim[j] * dim[k + 1] * dim[j + i + 1];
				if (tmp_ops < min)
				{
					min = tmp_ops;
					pos[j * length + j + i] = k;
				}
			}
			m[j * length + j + i] = min;
		}
	}
}

void print_solution(int* pos, int i, int j, int length)
{
	if (i == j)
		std::cout << "A" << i;
	else
	{
		int k = pos[i * length + j];
		std::cout << "(";
		print_solution(pos, i, k, length);
		print_solution(pos, k + 1, j, length);
		std::cout << ")";
	}
}

void matrix_multiplication(int* dim, int length)
{
	int *m = new int[length * length];
	int *pos = new int[length * length];
	matrix_multiplication_bottom_up(dim, m, pos, length);
	std::cout << "Optimal Solution: " << std::endl;
	print_solution(pos, 0, length - 1, length);
	
	std::cout << std::endl << "Operations: " << m[length - 1] << std::endl;
	delete[]m;
	delete[]pos;
}
