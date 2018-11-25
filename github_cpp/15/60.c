#include "Stdafx.h"
#include "MatrixLib.h"

namespace MatrixLib{
	__declspec(dllexport) std::vector<std::vector<int>> matrixMultiply(std::vector<std::vector<int>> mat1, std::vector<std::vector<int>> mat2)
	{
		if (mat1.size() == 0 || mat2.size() == 0)
			return std::vector<std::vector<int>>();

		std::vector<std::vector<int>> result(mat1.size(), std::vector<int>(mat2[0].size(), 0));
		for (int i = 0; i < mat1.size(); i++)
		{
			for (int j = 0; j < mat2[0].size(); j++)
			{
				for (int k = 0; k < mat1[i].size(); k++)
				{
					result[i][j] += ( mat1[i][k] * mat2[k][j] );
				}
			}
		}
		return result;
	}
}