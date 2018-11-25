






#include <vector>
using namespace std;

class Solution_v1 {
public:
	
	
	
	
	
	
	
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