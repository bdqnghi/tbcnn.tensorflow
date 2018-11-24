///@file	Sparse Matrix Multiplication
///@author	zhaowei
///@date	2016.03.19
///@version	1.0
///@version	1.1


#include <vector>
using namespace std;

class Solution_v1 {
public:
	///@brief	计算两个矩阵的乘法
	///@param	A	矩阵A
	///@param	B	矩阵B
	///@return	返回A*B的结果
	///@note	1. 迭代；
	//			2. 对于A[i][k]或者B[k][j]为0的情形，直接跳过，能够减少相乘和相加的次数；
	//			3. TLE.
	vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {
		vector<vector<int>> rslt;
		if (A.empty() || B.empty())	return rslt;
		for (int i = 0; i < A.size(); i++) {
			vector<int> row;
			for (int j = 0; j < B[0].size(); j++) {
				int sum = 0;
				for (int k = 0; k < B.size(); k++) {
					if (!A[i][k] || !B[k][j])	continue;
					sum += A[i][k] * B[k][j];		
				}
				row.push_back(sum);
			}
			rslt.push_back(row);
		}
		return rslt;
	}
};

class Solution {
public:
	///@brief	计算两个矩阵的乘法
	///@param	A	矩阵A
	///@param	B	矩阵B
	///@return	返回A*B的结果
	///@note	1. 迭代；
	//			2. 对于A[i][k]或者B[k][j]为0的情形，直接跳过，能够减少相乘和相加的次数；
	//			3. 在v1的基础上，对于整行或者整列为0的情况进行预处理标记，这样其所对应的元素直接都为0；
	vector<vector<int>> multiply(vector<vector<int>>& A, vector<vector<int>>& B) {		
		vector<vector<int>> rslt;
		if (A.empty() || B.empty())	return rslt;
		vector<bool> zero_A(A.size(), false), zero_B(B[0].size(), false);
		
		for (int i = 0; i != A.size(); i++) {
			int flg = 0;
			for (int j = 0; j != A[i].size(); j++)
				flg |= A[i][j];							
			if (!flg)	zero_A[i] = true;			
		}
		for (int i = 0; i != B[0].size(); i++) {
			int flg = 0;
			for (int j = 0; j != B.size(); j++)
				flg |= B[j][i];							
			if (!flg)	zero_B[i] = true;			
		}

		for (int i = 0; i < A.size(); i++) {
			vector<int> row;
			for (int j = 0; j < B[0].size(); j++) {
				int sum = 0;
				for (int k = 0; k < B.size(); k++) {
					if (zero_A[i] || zero_B[j])	break;
					if (!A[i][k] || !B[k][j])	continue;
					sum += A[i][k] * B[k][j];		
				}
				row.push_back(sum);
			}
			rslt.push_back(row);
		}
		return rslt;
	}
};

int main() {
	int nums1[2][3] = {{1, 0, 0}, {-1, 0, 3}}, nums2[3][4] = {{7, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 1, 1}};
	vector<vector<int>> A, B;
	for (int i = 0; i != 2; i++) {
		vector<int> tmp;
		for (int j = 0; j != 3; j++) {
			tmp.push_back(nums1[i][j]);
		}
		A.push_back(tmp);
	}
	for (int i = 0; i != 3; i++) {
		vector<int> tmp;
		for (int j = 0; j != 4; j++) {
			tmp.push_back(nums2[i][j]);
		}
		B.push_back(tmp);
	}
	Solution slt;
	vector<vector<int>> rslt = slt.multiply(A, B);
	return 0;
}