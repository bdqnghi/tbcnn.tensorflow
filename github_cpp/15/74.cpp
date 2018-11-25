#include <iostream>
#include <vector>
using namespace std;

vector<vector<int> > multiply(vector<vector<int> >& A, vector<vector<int> >& B);
vector<int> getColIn(vector<vector<int> >& B, int j);
int sumProduct(vector<int>& rowIinA, vector<int>& colJinB);
void print(vector<vector<int> >& matrix);
void print(vector<int>& vec);

int main() {
    vector<vector<int> > A;
    
    vector<int> row1forA;
    row1forA.push_back(1);
    row1forA.push_back(0);
    row1forA.push_back(0);
    A.push_back(row1forA);
    
    vector<int> row2forA;
    row2forA.push_back(-1);
    row2forA.push_back(0);
    row2forA.push_back(3);
    A.push_back(row2forA);
    
    cout << "A =" << endl;
    print(A);
    cout << endl << endl;
    
    vector<vector<int> > B;
    
    vector<int> row1forB;
    row1forB.push_back(7);
    row1forB.push_back(0);
    row1forB.push_back(0);
    B.push_back(row1forB);
    
    vector<int> row2forB;
    row2forB.push_back(0);
    row2forB.push_back(0);
    row2forB.push_back(0);
    B.push_back(row2forB);
    
    vector<int> row3forB;
    row3forB.push_back(0);
    row3forB.push_back(0);
    row3forB.push_back(1);
    B.push_back(row3forB);
    
    cout << "B =" << endl;
    print(B);
    cout << endl << endl;
    
    vector<vector<int> > result = multiply(A, B);
    cout << "A * B =" << endl;
    print(result);
    
    return 0;
}

vector<vector<int> > multiply(vector<vector<int> >& A, vector<vector<int> >& B) {
    if (A[0].size() != B.size()) throw "A's column number doesn't equal B's row number.";
    vector<vector<int> > result;
    for (int i = 0; i < A.size(); i++) {
        vector<int> rowIinA = A[i];
        vector<int> newRowInResult;
        for (int j = 0; j < B[0].size(); j++) {
            vector<int> colJinB = getColIn(B, j);
            newRowInResult.push_back(sumProduct(rowIinA, colJinB));
        }
        result.push_back(newRowInResult);
    }
    return result;
}

vector<int> getColIn(vector<vector<int> >& B, int j) {
    vector<int> result;
    for (int i = 0; i < B.size(); i++) {
        for (int k = 0; k < B[0].size(); k++) {
            if (k == j) result.push_back(B[i][k]);
        }
    }
    return result;
}

int sumProduct(vector<int>& rowIinA, vector<int>& colJinB) {
    int sumProduct = 0;
    for (int i = 0; i < rowIinA.size(); i++) {
        sumProduct += rowIinA[i] * colJinB[i];
    }
    return sumProduct;
}

void print(vector<vector<int> >& matrix) {
    cout << "[";
    for (int i = 0; i < matrix.size(); i++) {
        if (i > 0) cout << "," << endl;
        print(matrix[i]);
    }
    cout << "]";
}

void print(vector<int>& vec) {
    cout << "[";
    for (int i = 0; i < vec.size(); i++) {
        if (i > 0) cout << ", ";
        cout << vec[i];
    }
    cout << "]";
}
